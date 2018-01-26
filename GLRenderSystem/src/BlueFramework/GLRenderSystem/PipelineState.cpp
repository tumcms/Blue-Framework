/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2018 Technical University of Munich
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

#include <BlueFramework/GLRenderSystem/PipelineState.h>
#include <BlueFramework/GLRenderSystem/namespace.h>
#include <BlueFramework/GLRenderSystem/RenderSystem.h>
#include <BlueFramework/GLRenderSystem/Utils.h>

#include <BlueFramework/Rasterizer/VertexLayout.h>
#include <BlueFramework/Core/assert.h>

#include <tinyxml2.h>
#include <boost/filesystem.hpp>

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iterator>
#include <functional>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

namespace
{
	// Returns the shader compilation error message.
	std::string getShaderCompileErrMsg(GLuint const hShader)
	{
		GLint nStrLen = 0;
		glGetShaderiv(hShader, GL_INFO_LOG_LENGTH, &nStrLen);
		if (nStrLen <= 0) return std::string();
		std::vector<GLchar> buff(nStrLen);
		glGetShaderInfoLog(hShader, (GLsizei)buff.size(), nullptr, &buff.front());
		return std::string(&buff.front());
	}

	// Returns the shader link error message.
	std::string getShaderLinkErrMsg(GLuint const hProg)
	{
		GLint nStrLen = 0;
		glGetProgramiv(hProg, GL_INFO_LOG_LENGTH, &nStrLen);
		if (nStrLen <= 0) return std::string();
		std::vector<GLchar> buff(nStrLen);
		glGetProgramInfoLog(hProg, (GLsizei)buff.size(), nullptr, &buff.front());
		return std::string(&buff.front());
	}

	// Reads and compiles a shader from a source file.
	void getShader(
		std::string const& sstrFilePath,
		GLenum const shaderType,
		GLuint& hShaderOut,
		std::function<void(std::string const&, DWORD const, GLenum const)> const& onError)
	{
		// Read in shader source from file.
		std::ifstream shaderFile(sstrFilePath, std::ifstream::in | std::ifstream::binary);
		if (shaderFile.fail()) onError("Failed to open file: " + sstrFilePath, ERROR_SUCCESS, GL_NO_ERROR);
		std::string const sstrShader((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());

		// Create and compile shader.
		hShaderOut = glCreateShader(shaderType);
		if (!hShaderOut) onError("Failed to create shader.", GetLastError(), glGetError());
		GLchar const* const cstrShader[] = { sstrShader.c_str() };
		glShaderSource(hShaderOut, 1, cstrShader, nullptr);
		glCompileShader(hShaderOut);
		GLint nCompileStatus = GL_FALSE;
		glGetShaderiv(hShaderOut, GL_COMPILE_STATUS, &nCompileStatus);
		if (nCompileStatus == GL_FALSE) onError(::getShaderCompileErrMsg(hShaderOut), GetLastError(), glGetError());
	}

	void parsePipelineState(
		std::string const& sstrFileName,
		std::string const& sstrPsName,
		std::string& sstrVertShaderOut,
		std::string& sstrFragShaderOut,
		std::string& sstrGeoShaderOut)
	{
		tinyxml2::XMLDocument doc;
		if (doc.LoadFile(sstrFileName.c_str()) != tinyxml2::XML_SUCCESS)
			throw buw::Exception(("Error reading file " + sstrFileName).c_str());

		tinyxml2::XMLElement const* xml = doc.FirstChildElement("effect");
		if (xml == nullptr)
			throw buw::Exception("Invalid effect file");
		xml = xml->FirstChildElement("pipelinestate");
		if (!sstrPsName.empty())
		{
			for (; xml != nullptr; xml = xml->NextSiblingElement("pipelinestate"))
			{
				auto const nameAttr = xml->FindAttribute("name");
				if (nameAttr != nullptr && nameAttr->Value() == sstrPsName)
					break;
			}
			if (xml == nullptr)
				throw buw::Exception(("No pipelinestate with name \"" + sstrPsName + "\" found in file: " + sstrFileName).c_str());
		}
		if (xml == nullptr)
			throw buw::Exception("Invalid effect file");
		xml = xml->FirstChildElement("OGL");
		if (xml == nullptr)
			throw buw::Exception("Invalid effect file");
		auto xmlShader = xml->FirstChildElement("VertexShader");
		if (xmlShader != nullptr)
			sstrVertShaderOut = xmlShader->Attribute("filename");
		xmlShader = xml->FirstChildElement("PixelShader");
		if (xmlShader != nullptr)
			sstrFragShaderOut = xmlShader->Attribute("filename");
		xmlShader = xml->FirstChildElement("GeometryShader");
		if (xmlShader != nullptr)
			sstrGeoShaderOut = xmlShader->Attribute("filename");

		// Make paths absolute.
		auto baseDir = boost::filesystem::path(sstrFileName).parent_path();
		auto vertShaderPath = boost::filesystem::path(sstrVertShaderOut);
		auto fragShaderPath = boost::filesystem::path(sstrFragShaderOut);
		if (!vertShaderPath.empty() && vertShaderPath.is_relative())
			sstrVertShaderOut = (baseDir / vertShaderPath).string();
		if (!fragShaderPath.empty() && fragShaderPath.is_relative())
			sstrFragShaderOut = (baseDir / fragShaderPath).string();
	}
}

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

std::weak_ptr<PipelineState> PipelineState::_active;

PipelineState::PipelineState(RenderSystem* rs, buw::pipelineStateDescription const& psd)
	: buw::IPipelineState(rs, psd)
	, std::enable_shared_from_this<PipelineState>()
	, _bAdjacency(psd.useAdjacency)
	, _hProg(0)
	, _ePrimitiveType(
		(psd.primitiveTopology == buw::ePrimitiveTopology::PointList) * GL_POINTS +
		(psd.primitiveTopology == buw::ePrimitiveTopology::LineList) * GL_LINES +
		(psd.primitiveTopology == buw::ePrimitiveTopology::LineStrip) * GL_LINE_STRIP +
		(psd.primitiveTopology == buw::ePrimitiveTopology::TriangleList) * GL_TRIANGLES +
		(psd.primitiveTopology == buw::ePrimitiveTopology::TriangleStrip) * GL_TRIANGLE_STRIP)
	, _bMSAA(psd.useMSAA)
	, _bDepthTest(psd.useDepth)
{
	BLUE_ASSERT(psd.vertexLayout.componentCount() != 0, "missing vertex attributes");
	BLUE_ASSERT(_ePrimitiveType != 0, "unsupported primitive type");

	// Find paths to shader files.
	std::string sstrVertShader, sstrFragShader, sstrGeoShader;
	parsePipelineState(psd.effectFilename, psd.pipelineStateName, sstrVertShader, sstrFragShader, sstrGeoShader);
	BLUE_ASSERT(!sstrVertShader.empty() && !sstrFragShader.empty(), "useless render pipeline requested");

	GLuint hVert = 0, hFrag = 0, hGeo = 0;

	// Define a routine for the tedious task of cleaning up on early exits.
	auto cleanupAndThrow = [this, &hVert, &hFrag, &hGeo](std::string const& sstrMsg,
		DWORD const nWinErrCode = ERROR_SUCCESS, GLenum const nGLErrCode = GL_NO_ERROR) throw(...) ->void{
		if (this->_hProg)
		{
			GLint nNumAttachedShaders = 0;
			glGetProgramiv(this->_hProg, GL_ATTACHED_SHADERS, &nNumAttachedShaders);
			if (nNumAttachedShaders > 0)
			{
				std::vector<GLuint> attachedShaders(nNumAttachedShaders);
				glGetAttachedShaders(this->_hProg, (GLsizei)attachedShaders.size(), nullptr, &attachedShaders.front());
				for (auto hShader : attachedShaders)
					glDetachShader(this->_hProg, hShader);
			}
		}
		if (hVert) glDeleteShader(hVert);
		if (hFrag) glDeleteShader(hFrag);
		if (hGeo) glDeleteShader(hGeo);
		if (this->_hProg) glDeleteProgram(this->_hProg);
		this->_hProg = 0;
		throwWithMessage(sstrMsg, nWinErrCode, nGLErrCode, GLEW_OK);
	};

	// Vertex shader.
	if (!sstrVertShader.empty())
	{
		::getShader(sstrVertShader, GL_VERTEX_SHADER, hVert, cleanupAndThrow);
		BLUE_ASSERT(hVert != 0);
	}

	// Fragment shader.
	if (!sstrFragShader.empty())
	{
		::getShader(sstrFragShader, GL_FRAGMENT_SHADER, hFrag, cleanupAndThrow);
		BLUE_ASSERT(hFrag != 0);
	}

	// Geometry shader.
	if (!sstrGeoShader.empty())
	{
		if (!GLEW_ARB_geometry_shader4) cleanupAndThrow("Geometry shader required but not available.");
		::getShader(sstrGeoShader, GL_GEOMETRY_SHADER_ARB, hGeo, cleanupAndThrow);
		BLUE_ASSERT(hGeo != 0);
	}

	// Create shader program. Bind attribute indices to generic shader variable names.
	_hProg = glCreateProgram();
	if (!_hProg) cleanupAndThrow("Failed to create a shader program.", GetLastError(), glGetError());
	for (int i = 0; i < psd.vertexLayout.componentCount(); ++i)
	{
		// These default attribute variable names can be overridden within
		// the vertex shader using the "location" qualifier.
		std::ostringstream oss;
		oss << buw::toString(psd.vertexLayout.componentAt(i).semantic) << i;
		glBindAttribLocation(_hProg, (GLuint)i, oss.str().c_str());
	}
	if (hVert) glAttachShader(_hProg, hVert);
	if (hFrag) glAttachShader(_hProg, hFrag);
	if (hGeo) glAttachShader(_hProg, hGeo);
	glLinkProgram(_hProg);
	GLint nLinkStatus = GL_FALSE;
	glGetProgramiv(_hProg, GL_LINK_STATUS, &nLinkStatus);
	if (nLinkStatus == GL_FALSE) cleanupAndThrow(::getShaderLinkErrMsg(_hProg), GetLastError(), glGetError());

	// Cleanup.
	if (hVert)
	{
		glDetachShader(_hProg, hVert);
		glDeleteShader(hVert);
		hVert = 0;
	}
	if (hFrag)
	{
		glDetachShader(_hProg, hFrag);
		glDeleteShader(hFrag);
		hFrag = 0;
	}
	if (hGeo)
	{
		glDetachShader(_hProg, hGeo);
		glDeleteShader(hGeo);
		hGeo = 0;
	}

	BLUE_ASSERT(glGetError() == GL_NO_ERROR);
}

PipelineState::~PipelineState()
{
	if (_active.lock().get() == this) _active.reset(); // Actually not needed because we use a weak pointer.
	if (_hProg)
	{
		GLint currentProg = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM, &currentProg);
		if ((GLuint)currentProg == _hProg) glUseProgram(0);
		glDeleteProgram(_hProg);
	}
}

void PipelineState::setActive()
{
	if (_active.lock().get() == this) return;
	glUseProgram(_hProg);
	if ((glIsEnabled(GL_MULTISAMPLE) != GL_FALSE) ^ _bMSAA) _bMSAA ? glEnable(GL_MULTISAMPLE) : glDisable(GL_MULTISAMPLE);
	if ((glIsEnabled(GL_DEPTH_TEST) != GL_FALSE) ^ _bDepthTest) _bDepthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	_active = shared_from_this();
}

buw::ReferenceCounted<PipelineState> PipelineState::getActive()
{
	return _active.lock();
}

bool PipelineState::useAdjacency() const
{
	// FGI TODO
	return _bAdjacency;
}

GLenum PipelineState::getPrimitiveType() const
{
	return _ePrimitiveType;
}

GLuint PipelineState::getShaderProgram() const
{
	return _hProg;
}

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END
