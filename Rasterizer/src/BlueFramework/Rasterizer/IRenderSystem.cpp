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

#include "BlueFramework/Rasterizer/IRenderSystem.h"
#include "BlueFramework/Core/assert.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

buw::ReferenceCounted<IRenderSystem> createRenderSystem(const buw::renderSystemDescription& rsd) {
	const wchar_t* filename = nullptr;

	switch (rsd.renderAPI) {
#ifdef _DEBUG
	case eRenderAPI::Direct3D11:
		filename = L"BlueFramework.D3D11RenderSystemd.dll";
		BLUE_LOG(trace) << "Try to load BlueFramework.D3D11RenderSystemd.dll";
		break;
	case eRenderAPI::Direct3D12: filename = L"BlueFramework.D3D12RenderSystemd.dll"; break;
	case eRenderAPI::OpenGL: filename = L"BlueFramework.GLRenderSystemd.dll"; break;
	case eRenderAPI::Vulkan: filename = L"BlueFramework.VulkanRenderSystemd.dll"; break;
#else
	case eRenderAPI::Direct3D11:
		filename = L"BlueFramework.D3D11RenderSystem.dll";
		BLUE_LOG(trace) << "Try to load BlueFramework.D3D11RenderSystem.dll";
		break;
	case eRenderAPI::Direct3D12: filename = L"BlueFramework.D3D12RenderSystem.dll"; break;
	case eRenderAPI::OpenGL: filename = L"BlueFramework.GLRenderSystem.dll"; break;
	case eRenderAPI::Vulkan: filename = L"BlueFramework.VulkanRenderSystem.dll"; break;
#endif
	default: throw buw::Exception("Render system is not supported.");
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
