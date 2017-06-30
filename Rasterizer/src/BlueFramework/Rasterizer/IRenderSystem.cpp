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

#include "BlueFramework/Rasterizer/IRenderSystem.h"
#include "BlueFramework/Core/assert.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

buw::ReferenceCounted<IRenderSystem> createRenderSystem(const buw::renderSystemDescription& rsd) {
	wchar_t* filename = nullptr;

	switch(rsd.renderAPI)
	{
#ifdef _DEBUG
	case eRenderAPI::Direct3D11:
		filename = L"BlueFramework.D3D11RenderSystemd.dll";
		BLUE_LOG(trace) << "Try to load BlueFramework.D3D11RenderSystemd.dll";
		break;
	case eRenderAPI::Direct3D12:
		filename = L"BlueFramework.D3D12RenderSystemd.dll";
		break;
	case eRenderAPI::OpenGL:
		filename = L"BlueFramework.GLRenderSystemd.dll";
		break;
	case eRenderAPI::Vulkan:
		filename = L"BlueFramework.VulkanRenderSystemd.dll";
		break;
#else
	case eRenderAPI::Direct3D11:
		filename = L"BlueFramework.D3D11RenderSystem.dll";
		BLUE_LOG(trace) << "Try to load BlueFramework.D3D11RenderSystem.dll";
		break;
	case eRenderAPI::Direct3D12:
		filename = L"BlueFramework.D3D12RenderSystem.dll";
		break;
	case eRenderAPI::OpenGL:
		filename = L"BlueFramework.GLRenderSystem.dll";
		break;
	case eRenderAPI::Vulkan:
		filename = L"BlueFramework.VulkanRenderSystem.dll";
		break;
#endif
	default:
		throw buw::Exception("Render system is not supported.");
	}

	HMODULE hDLL = nullptr;
	hDLL = LoadLibraryEx(filename, nullptr, 0);
	BLUE_ASSERT(hDLL != nullptr, "Load library failed.");

	if (hDLL == nullptr) {
		throw buw::Exception("Render system not found.");
	}

	void* symbolPtr = GetProcAddress((HMODULE)hDLL, "createRenderSystem");
	BLUE_ASSERT(symbolPtr != nullptr, "GetProcAddress failed.");

	if (symbolPtr == nullptr) {
		throw buw::Exception("createRenderSystem function not found.");
	}

	typedef IRenderSystem* (*LPCREATERENDERER)(const buw::renderSystemDescription&);
	LPCREATERENDERER lpCreateRenderSystem = reinterpret_cast<LPCREATERENDERER>(symbolPtr);

	IRenderSystem* renderSystem = lpCreateRenderSystem(rsd);

	return buw::ReferenceCounted<IRenderSystem>(renderSystem);
}

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END
