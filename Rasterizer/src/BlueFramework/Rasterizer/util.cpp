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