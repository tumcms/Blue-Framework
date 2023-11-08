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

#include "util.h"
#include <tinyxml2.h>

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

bool loadRenderSystemSettings(const std::string& filename, eRenderAPI& renderAPI, bool& warp, bool& msaa)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename.c_str());

	auto xmlSettings = doc.FirstChildElement("settings");
	if (xmlSettings == nullptr)
	{
		throw buw::Exception("Invalid settings file");
		return false;
	}

	auto xmlRenderSystem = xmlSettings->FirstChildElement("renderSystemDescription");
	if (xmlRenderSystem == nullptr)
	{
		throw buw::Exception("Invalid settings file");
		return false;
	}

	auto xmlRenderAPI = xmlRenderSystem->FirstChildElement("renderAPI");
	if (xmlRenderAPI == nullptr)
	{
		throw buw::Exception("Invalid settings file");
		return false;
	}

	auto xmlWarpDevice = xmlRenderSystem->FirstChildElement("forceWarpDevice");
	if (xmlWarpDevice == nullptr)
	{
		throw buw::Exception("Invalid settings file");
		return false;
	}

	auto xmlMSAA = xmlRenderSystem->FirstChildElement("enableMSAA");
	if (xmlMSAA == nullptr)
	{
		throw buw::Exception("Invalid settings file");
		return false;
	}

	std::string renderAPIStr = xmlRenderAPI->GetText();
	if (renderAPIStr == "Direct3D11")
		renderAPI = eRenderAPI::Direct3D11;
	else if (renderAPIStr == "Direct3D12")
		renderAPI = eRenderAPI::Direct3D12;
	else if (renderAPIStr == "OpenGL")
		renderAPI = eRenderAPI::OpenGL;

	warp = std::string(xmlWarpDevice->GetText()) == "true";
	msaa = std::string(xmlMSAA->GetText()) == "true";

	return true;
}

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END