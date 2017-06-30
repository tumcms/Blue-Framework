/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2016-2017 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    BlueFramework is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    BlueFramework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <GL/glew.h> // !! GLEW always first !!
#include <GL/wglew.h>

#include <BlueFramework/GLRenderSystem/RenderSystem.h>
#include <BlueFramework/GLRenderSystem/namespace.h>
#include <BlueFramework/GLRenderSystem/EffectCore.h>
#include <BlueFramework/GLRenderSystem/Viewport.h>
#include <BlueFramework/GLRenderSystem/VertexBuffer.h>
#include <BlueFramework/GLRenderSystem/Sampler.h>
#include <BlueFramework/GLRenderSystem/Texture1D.h>
#include <BlueFramework/GLRenderSystem/ITexture2D.h>
#include <BlueFramework/GLRenderSystem/Texture2D.h>
#include <BlueFramework/GLRenderSystem/Utils.h>

#include <BlueFramework/Core/Diagnostics/log.h>
#include <BlueFramework/Core/Exception.h>
#include <BlueFramework/Core/string.h>
#include <BlueFramework/Core/memory.h>
#include <BlueFramework/Core/assert.h>

#include <string>
#include <sstream>
#include <cstring>
#include <cstddef>
#include <memory>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

// The OpenGL version we build upon.
#define _MIN_GL_MAJOR_VERSION 3
#define _MIN_GL_MINOR_VERSION 1

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

RenderSystem::RenderSystem(buw::renderSystemDescription const& rsd)
	: buw::IRenderSystem(rsd)
	, _hWND((HWND)rsd.windowId)
	, _hDC(nullptr)
	, _hGLRC(nullptr)
	, _bb()
{
	createRenderContext(rsd);

	// Configure MSAA. Read about this here: https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_multisample.txt
	if (rsd.enableMSAA)
	{
		glEnable(GL_MULTISAMPLE);
		glDisable(GL_SAMPLE_COVERAGE); // No static sample masking through glSampleCoverage().
		glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE); // Dynamic sample masking using the fragments alpha value.
		glDisable(GL_SAMPLE_ALPHA_TO_ONE); // Leave fragment alpha values untouched by the multisampling procedure.
	}
	else
		glDisable(GL_MULTISAMPLE); // Is enabled by default.

	// Configure depth testing.
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	BLUE_ASSERT(glGetError() == GL_NO_ERROR);
}

RenderSystem::~RenderSystem()
{
	wglMakeCurrent(nullptr, nullptr);
	if (_hGLRC != nullptr) wglDeleteContext(_hGLRC);
	if (_hDC != nullptr) ReleaseDC(_hWND, _hDC);
}

void RenderSystem::createRenderContext(buw::renderSystemDescription const& rsd)
{
	// There are two challenges when creating a modern OpenGL render context:
	// 1. The API for creating a strictly forward-compatible render context
	//    wglCreateContextAttribsARB() is itself a WGL extension, thus there
	//    needs to be some render context active already in order to load this
	//    extension. If MSAA is requested, then the same argument applies for
	//    wglChoosePixelFormatARB(), see below. Solution: Create a bootstrapping
	//    legacy render context and use it to load the extensions.
	// 2. If MSAA is requested, then we must find a suitable pixel format using
	//    wglChoosePixelFormatARB() and set it via SetPixelFormat(). Only after
	//    this a render context can be created. However because
	//    wglChoosePixelFormatARB() is a WGL extension, there must exist already
	//    a render context (the legacy render context) for which SetPixelFormat()
	//    must already have been called with a simple, non-multisample pixel format
	//    (found via ChoosePixelFormat()). Thus, we are required to call
	//    SetPixelFormat() twice. This is not allowed on a single object as is
	//    documented here:
	//    https://msdn.microsoft.com/en-us/library/windows/desktop/dd369049(v=vs.85).aspx
	//    Solution: Create and use an unmapped temporary window to create the
	//    legacy render context.

	// Define a routine for the tedious task of cleaning up on early exits.
	HWND hLegacyWnd = nullptr;
	HDC hLegacyDC = nullptr;
	HGLRC hLegacyGLRC = nullptr;
	auto cleanupAndThrow = [this, &hLegacyDC, &hLegacyWnd, &hLegacyGLRC](std::string const& sstrMsg,
		DWORD const nWinErrCode = ERROR_SUCCESS, GLenum const nGLErrCode = GL_NO_ERROR, GLenum const nGLEWErrCode = GLEW_OK) throw(...) ->void{
		wglMakeCurrent(nullptr, nullptr);
		if (this->_hGLRC != nullptr) wglDeleteContext(this->_hGLRC);
		if (hLegacyGLRC != nullptr) wglDeleteContext(hLegacyGLRC);
		if (this->_hDC != nullptr) ReleaseDC(this->_hWND, this->_hDC);
		if (hLegacyDC != nullptr) ReleaseDC(hLegacyWnd, hLegacyDC);
		if (hLegacyWnd != nullptr) DestroyWindow(hLegacyWnd);
		this->_hDC = nullptr;
		this->_hGLRC = nullptr;
		throwWithMessage(sstrMsg, nWinErrCode, nGLErrCode, nGLEWErrCode);
	};

	// Create a temporary window to use with the legacy render context.
	hLegacyWnd = CreateWindow(L"STATIC", nullptr, WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, 320, 240, nullptr, nullptr, nullptr, nullptr);
	if (hLegacyWnd == nullptr) cleanupAndThrow("Failed to create a temporary window for the legacy render context.", GetLastError());
	hLegacyDC = GetDC(hLegacyWnd);
	if (hLegacyDC == nullptr) cleanupAndThrow("Failed to retrieve a device context for the legacy render context window.", GetLastError());

	// Make the temporary window OpenGL compatible by setting a suitable pixel format.
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cAccumBits = 0;
	pfd.cAccumRedBits = 0;
	pfd.cAccumGreenBits = 0;
	pfd.cAccumBlueBits = 0;
	pfd.cAccumAlphaBits = 0;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.cAuxBuffers = 0;
	pfd.iLayerType = PFD_MAIN_PLANE;
	int nPF = ChoosePixelFormat(hLegacyDC, &pfd);
	if (nPF == 0) cleanupAndThrow("Failed to choose a suitable pixel format for the OpenGL "
		"render surface (ChoosePixelFormat() failed).", GetLastError());
	if (SetPixelFormat(hLegacyDC, nPF, &pfd) != TRUE) cleanupAndThrow("Failed to set a suitable pixel "
		"format for the OpenGL render surface (SetPixelFormat() failed).", GetLastError());

	// OpenGL 3.x bootstrapping: We have to create a legacy render context first.
	hLegacyGLRC = wglCreateContext(hLegacyDC);
	if (hLegacyGLRC == nullptr) cleanupAndThrow("Failed to create an OpenGL 2.x render context "
		"for the given window.", GetLastError());
	if (wglMakeCurrent(hLegacyDC, hLegacyGLRC) != TRUE) cleanupAndThrow("Failed to make the OpenGL 2.x "
		"render context current.", GetLastError());

	// Check and log OpenGL version. This looks quite complicated but GL_MAJOR_VERSION
	// and GL_MINOR_VERSION are not available before OpenGL 3.0.
	GLubyte const* cstrOGLString = glGetString(GL_VENDOR);
	BLUE_LOG(info) << "OpenGL vendor: " << cstrOGLString;
	cstrOGLString = glGetString(GL_RENDERER);
	BLUE_LOG(info) << "OpenGL renderer: " << cstrOGLString;
	cstrOGLString = glGetString(GL_VERSION);
	BLUE_LOG(info) << "OpenGL version: " << cstrOGLString;
	int nGLMajor = 0, nGLMinor = 0;
	(std::istringstream((char const*)cstrOGLString) >> nGLMajor).ignore(1, '.') >> nGLMinor;
	if (nGLMajor < _MIN_GL_MAJOR_VERSION || (nGLMajor == _MIN_GL_MAJOR_VERSION && nGLMinor < _MIN_GL_MINOR_VERSION))
	{
		// We rely on OpenGL 3.1 at least. Be permissive: Don't abort at this point even if it looks bad.
		BLUE_LOG(warning) << "OpenGL version " << _MIN_GL_MAJOR_VERSION << "." << _MIN_GL_MINOR_VERSION <<
			" or higher required. Trying to continue anyway.";
	}

	// Initialize OpenGL API entry points (core and extensions).
	GLenum const result = glewInit();
	if (result != GLEW_OK) cleanupAndThrow("GLEW init failed.", GetLastError(), GL_NO_ERROR, result);
	BLUE_LOG(info) << "OpenGL API successfully initialized. Using GLEW " << glewGetString(GLEW_VERSION);

	// Ensure mandatory extensions. At this point we still assume an unknown OpenGL version
	// because we don't have the 3.1 strictly forward-compatible context yet.
	if (!WGLEW_ARB_pixel_format || // for wglChoosePixelFormatARB(), wglGetPixelFormatAttribivARB()
		!WGLEW_ARB_create_context) // for wglCreateContextAttribsARB()
		cleanupAndThrow("Mandatory OpenGL extension is missing.");

	// Find a suitable pixel format for the target widget.
	_hDC = GetDC(_hWND);
	if (_hDC == nullptr) cleanupAndThrow("Failed to retrieve a device context for the given window.", GetLastError());
	if (rsd.enableMSAA && WGLEW_ARB_multisample)
	{
		int const attribs[] = {
			WGL_DRAW_TO_WINDOW_ARB,		(pfd.dwFlags & PFD_DRAW_TO_WINDOW) ? TRUE : FALSE,
			WGL_SUPPORT_OPENGL_ARB,		(pfd.dwFlags & PFD_SUPPORT_OPENGL) ? TRUE : FALSE,
			WGL_DOUBLE_BUFFER_ARB,		(pfd.dwFlags & PFD_DOUBLEBUFFER) ? TRUE : FALSE,
			//WGL_STEREO_ARB,			(pfd.dwFlags & PFD_STEREO) ? TRUE : FALSE,
			//WGL_ACCELERATION_ARB,		WGL_FULL_ACCELERATION_ARB, // Don't restrict to HW accel only. We'll get the fastest option by wglChoosePixelFormatARB() anyway (for sure by documentation).
			//WGL_SWAP_METHOD_ARB,		WGL_SWAP_UNDEFINED_ARB, // Better don't specify as it's not clear what is fastest and we are fine with all options. Other options: WGL_SWAP_EXCHANGE_ARB, WGL_SWAP_COPY_ARB
			WGL_PIXEL_TYPE_ARB,			(pfd.iPixelType == PFD_TYPE_RGBA) ? WGL_TYPE_RGBA_ARB : WGL_TYPE_COLORINDEX_ARB,
			WGL_COLOR_BITS_ARB,			pfd.cColorBits,
			WGL_RED_BITS_ARB,			pfd.cRedBits,
			WGL_GREEN_BITS_ARB,			pfd.cGreenBits,
			WGL_BLUE_BITS_ARB,			pfd.cBlueBits,
			WGL_ALPHA_BITS_ARB,			pfd.cAlphaBits,
			WGL_ACCUM_BITS_ARB,			pfd.cAccumBits,
			WGL_ACCUM_RED_BITS_ARB,		pfd.cAccumRedBits,
			WGL_ACCUM_GREEN_BITS_ARB,	pfd.cAccumGreenBits,
			WGL_ACCUM_BLUE_BITS_ARB,	pfd.cAccumBlueBits,
			WGL_ACCUM_ALPHA_BITS_ARB,	pfd.cAccumAlphaBits,
			WGL_DEPTH_BITS_ARB,			pfd.cDepthBits,
			WGL_STENCIL_BITS_ARB,		pfd.cStencilBits,
			WGL_AUX_BUFFERS_ARB,		pfd.cAuxBuffers,
			////////////////////////////////////////////////////////////////////////////////
			// Added by WGL_ARB_multisample:
			////////////////////////////////////////////////////////////////////////////////
			WGL_SAMPLE_BUFFERS_ARB,		1,
			WGL_SAMPLES_ARB,			8, // or 4
			0};
		UINT unNumMatches = 0;
		if (wglChoosePixelFormatARB(_hDC, attribs, nullptr, 1, &nPF, &unNumMatches) != TRUE)
			cleanupAndThrow("Failed to choose a suitable multisample pixel format for the OpenGL "
				"render surface (wglChoosePixelFormatARB() failed).", GetLastError(), glGetError());
		if (unNumMatches <= 0) cleanupAndThrow("Failed to find a suitable multisample pixel format "
			"for the OpenGL render surface.");
		BLUE_ASSERT(nPF != 0, "a valid PF index is >0");
	}
	else
	{
		nPF = ChoosePixelFormat(_hDC, &pfd);
		if (nPF == 0) cleanupAndThrow("Failed to choose a suitable pixel format for the OpenGL "
			"render surface (ChoosePixelFormat() failed).", GetLastError());
	}

	// Set the final pixel format for the given target widget.
	if (SetPixelFormat(_hDC, nPF, &pfd) != TRUE) cleanupAndThrow("Failed to set a suitable pixel "
		"format for the OpenGL render surface (SetPixelFormat() failed).", GetLastError());

	// Create 3.1 forward-compatible (i.e. no deprecated features) context.
	// Note about profiles in OpenGL 3.1:
	// 1. Even though the OpenGL 3.1 specification already mentions profiles, it also states that
	//    for this version (actually already for 3.0) there only exists exactly one profile. See
	//    appendix E.1 of https://khronos.org/registry/OpenGL/specs/gl/glspec31.pdf
	//    At that time profiles seemed to be intended for things like "workstation, gaming, and
	//    embedded". In order to create a strictly forward-compatible context, the
	//    CONTEXT_FORWARD_COMPATIBLE_BIT should be used during creation.
	// 2. Not before OpenGL 3.2 there were introduced the "core" and the "compatibility" profiles
	//    whereby only the core profile must always be available. Thus creating a forward-compatible
	//    context is no longer intended to be done by setting the CONTEXT_FORWARD_COMPATIBLE_BIT
	//    anymore but by choosing the core profile instead. See (poorly written)
	//    https://www.khronos.org/opengl/wiki/Core_And_Compatibility_in_Contexts and also
	//    https://khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_create_context.txt
	//    The last reference states "These extensions add a new context creation routine with
	//    attributes specifying the GL version and context properties requested for the context,
	//    and additionally add an attribute specifying the GL profile requested for a context of
	//    OpenGL 3.2 or later." which just supports that one should not request the core profile
	//    (or any other profile) when creating a 3.1 context.
	//
	// To summarize, in order to create a strictly forward-compatible context for
	// * 3.0/3.1: Set CONTEXT_FORWARD_COMPATIBLE_BIT, but no profile.
	// * >3.1: Don't set CONTEXT_FORWARD_COMPATIBLE_BIT, but choose the core profile.
	int const attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, _MIN_GL_MAJOR_VERSION,
		WGL_CONTEXT_MINOR_VERSION_ARB, _MIN_GL_MINOR_VERSION,
#ifdef _DEBUG
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | WGL_CONTEXT_DEBUG_BIT_ARB,
#else
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
#endif
		WGL_CONTEXT_LAYER_PLANE_ARB, 0,
		0};
	_hGLRC = wglCreateContextAttribsARB(_hDC, nullptr, attribs);
	if (_hGLRC == nullptr) cleanupAndThrow("Failed to create an OpenGL 3.x render context for the given window.",
		GetLastError(), glGetError());
	if (wglMakeCurrent(_hDC, _hGLRC) != TRUE) cleanupAndThrow("Failed to make the OpenGL 3.x render context current.",
		GetLastError());

	// Cleanup.
	wglDeleteContext(hLegacyGLRC); hLegacyGLRC = nullptr;
	ReleaseDC(hLegacyWnd, hLegacyDC); hLegacyDC = nullptr;
	DestroyWindow(hLegacyWnd); hLegacyWnd = nullptr;

	BLUE_ASSERT(glGetError() == GL_NO_ERROR);
}

buw::ReferenceCounted<buw::IEffectCore> RenderSystem::createEffectCore()
{
	return buw::makeReferenceCounted<EffectCore>(this);
}

buw::ReferenceCounted<buw::IVertexBuffer> RenderSystem::createVertexBuffer(buw::vertexBufferDescription const& vbd)
{
	return buw::makeReferenceCounted<VertexBuffer>(this, vbd);
}

buw::ReferenceCounted<buw::IIndexBuffer> RenderSystem::createIndexBuffer(buw::indexBufferDescription const& /*ibd*/)
{
	// FGI TODO
	return nullptr;
}

buw::ReferenceCounted<buw::IConstantBuffer> RenderSystem::createConstantBuffer(buw::constantBufferDescription const& /*cbd*/)
{
	// FGI TODO
	return nullptr;
}

buw::ReferenceCounted<buw::ITexture1D> RenderSystem::createTexture1D(buw::texture1DDescription const& td, buw::eTextureBindType /*bindType*/)
{
	return buw::makeReferenceCounted<Texture1D>(td);
}

buw::ReferenceCounted<buw::ITexture2D> RenderSystem::createTexture2D(buw::texture2DDescription const& td, buw::eTextureBindType /*bindType*/)
{
	return buw::makeReferenceCounted<Texture2D>(td);
}

buw::ReferenceCounted<buw::ITextureCube> RenderSystem::createTextureCube(buw::textureCubeDescription const& /*td*/, buw::eTextureBindType /*bindType*/)
{
	// FGI TODO
	return nullptr;
}

buw::ReferenceCounted<buw::ISampler> RenderSystem::createSampler(buw::samplerStateDescription const& ssd)
{
	return buw::makeReferenceCounted<Sampler>(this, ssd);
}

buw::ReferenceCounted<buw::IBlender> RenderSystem::createBlender(buw::blendStateDescription const& /*bsd*/)
{
	// FGI TODO
	return nullptr;
}

buw::ReferenceCounted<buw::IViewport> RenderSystem::createViewport(buw::viewportDescription const& vpd)
{
	return buw::makeReferenceCounted<Viewport>(vpd);
}

buw::ReferenceCounted<buw::ITexture2D> RenderSystem::getBackBufferTarget()
{
	return buw::ReferenceCounted<buw::ITexture2D>(&_bb, [](buw::ITexture2D*){}); // No-op deleter, since we return statically allocated memory.
}

void RenderSystem::clearRenderTarget(buw::ReferenceCounted<buw::ITexture2D> renderTarget, float const color[4])
{
	clearRenderTargets({ renderTarget }, color);
}

void RenderSystem::clearRenderTargets(std::vector<buw::ReferenceCounted<buw::ITexture2D>> renderTargets, float const color[4])
{
	for (auto it : renderTargets)
		std::static_pointer_cast<ITexture2D>(it)->clear(color);
}

void RenderSystem::clearDepthStencilView(buw::ReferenceCounted<buw::ITexture2D> depthStencil)
{
	_bb.clearDepthBuffer();
	_bb.clearStencilBuffer();
}

void RenderSystem::present()
{
	SwapBuffers(_hDC);
}

void RenderSystem::resize(int width, int height)
{
	buw::texture2DDescription td;
	memset(&td, 0, sizeof(buw::texture2DDescription));
	td.width = width;
	td.height = height;
	_bb.resize(td);
}

char const* RenderSystem::getName() const
{
	return "OpenGL " BLUE_STRINGIFY_VALUE(_MIN_GL_MAJOR_VERSION) "." BLUE_STRINGIFY_VALUE(_MIN_GL_MINOR_VERSION);
}

bool const RenderSystem::getMSAAEnabled() const
{
	return glIsEnabled(GL_MULTISAMPLE) && hasMultiSampleBuffer();
}

bool RenderSystem::hasMultiSampleBuffer() const
{
	int const attrib[] = {WGL_SAMPLE_BUFFERS_ARB};
	int nNumSampleBuffers = 0;
	if (wglGetPixelFormatAttribivARB(_hDC, GetPixelFormat(_hDC), 0, 1, attrib, &nNumSampleBuffers) != TRUE)
		throwWithMessage("wglGetPixelFormatAttribivARB() failed.", GetLastError(), glGetError());
	return nNumSampleBuffers > 0;
}

size_t RenderSystem::getNumAASamplesPerPixel() const
{
	int const attrib[] = {WGL_SAMPLES_ARB};
	int nNumSamplesPerPixel = 0;
	if (wglGetPixelFormatAttribivARB(_hDC, GetPixelFormat(_hDC), 0, 1, attrib, &nNumSamplesPerPixel) != TRUE)
		throwWithMessage("wglGetPixelFormatAttribivARB() failed.", GetLastError(), glGetError());
	BLUE_ASSERT(nNumSamplesPerPixel >= 0);
	return nNumSamplesPerPixel;
}

void RenderSystem::downloadTexture(buw::ReferenceCounted<buw::ITexture2D> itexture, buw::Image4b& /*dest*/, const int /*x = 0*/, const int /*y = 0*/)
{
	throw buw::NotImplementedYetException("The method or operation is not implemented.");
}

void RenderSystem::uploadTexture(buw::ReferenceCounted<buw::ITexture2D> itexture, buw::Image4b& /*dest*/, const int /*x = 0*/, const int /*y = 0*/)
{
	throw buw::NotImplementedYetException("The method or operation is not implemented.");
}

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END

extern "C" buw::IRenderSystem* createRenderSystem(buw::renderSystemDescription const& rsd)
{
	BLUE_LOG(trace) << "Enter createRenderSystem...";

	return new BlueFramework::GLRenderSystem::RenderSystem(rsd);
}
