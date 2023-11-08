/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2023 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <GL/glew.h>

#include <BlueFramework/GLRenderSystem/BackBufferRenderTarget.h>
#include <BlueFramework/GLRenderSystem/namespace.h>

#include <BlueFramework/Rasterizer/renderDescriptors.h>
#include <BlueFramework/Core/Exception.h>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

BackBufferRenderTarget::BackBufferRenderTarget()
: ITexture2D()
{
	// OpenGL not yet available at this point.
}

BackBufferRenderTarget::~BackBufferRenderTarget()
{
	// OpenGL not available anymore at this point.
}

int BackBufferRenderTarget::width() const
{
	GLint vp[4] = {0};
	glGetIntegerv(GL_VIEWPORT, vp);
	return vp[2];
}

int BackBufferRenderTarget::height() const
{
	GLint vp[4] = {0};
	glGetIntegerv(GL_VIEWPORT, vp);
	return vp[3];
}

bool BackBufferRenderTarget::hasShaderResourceView() const
{
	return false; // FGI TODO
}

bool BackBufferRenderTarget::hasRenderTargetView() const
{
	return true; // FGI TODO
}

bool BackBufferRenderTarget::hasDepthStencilView() const
{
	return true; // FGI TODO
}

bool BackBufferRenderTarget::isCPUReadable() const
{
	return true; // FGI TODO
}

void BackBufferRenderTarget::makeCPUReadable()
{
	// Is always readable by the CPU, resp. we defer the GPU -> CPU transfer
	// by using glReadPixels() or alike.
}

const buw::eTextureBindType BackBufferRenderTarget::getBindType() const
{
	return buw::eTextureBindType::RTV; // FGI TODO
}

const buw::eTextureFormat BackBufferRenderTarget::getFormat() const
{
	return buw::eTextureFormat::Undefined; // FGI TODO
}

void BackBufferRenderTarget::resize(const buw::texture2DDescription& td)
{
	glViewport(0, 0, td.width, td.height);
}

void BackBufferRenderTarget::clear(float const color[4])
{
	if(color == nullptr)
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	else
		glClearColor(color[0], color[1], color[2], color[3]);

	glClear(GL_COLOR_BUFFER_BIT);
}

void BackBufferRenderTarget::clearDepthBuffer()
{
	glClearDepth(1.0);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void BackBufferRenderTarget::clearStencilBuffer()
{
	glClearStencil(0);
	glClear(GL_STENCIL_BUFFER_BIT);
}

bool BackBufferRenderTarget::isCPUWriteable() const
{
	throw buw::NotImplementedYetException("The method or operation is not implemented.");
	//return false;
}

void BackBufferRenderTarget::makeCPUWriteable()
{
	throw buw::NotImplementedYetException("The method or operation is not implemented.");
}

bool BackBufferRenderTarget::isMultisampled() const {
	throw buw::NotImplementedYetException("The method or operation is not implemented.");
}

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END
