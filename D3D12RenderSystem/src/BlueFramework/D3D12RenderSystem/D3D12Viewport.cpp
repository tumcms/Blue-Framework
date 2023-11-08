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

#include "BlueFramework/D3D12RenderSystem/D3D12Viewport.h"
#include "BlueFramework/D3D12RenderSystem/D3D12RenderSystem.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

D3D12Viewport::D3D12Viewport(const buw::viewportDescription& vpd) : IViewport(vpd) {
	viewport_ = new D3D12_VIEWPORT();
	scissorRect_ = new D3D12_RECT();
	resize(vpd);
}

D3D12Viewport::~D3D12Viewport() {
	if (viewport_)
		delete viewport_;

	if (scissorRect_)
		delete scissorRect_;
}

void D3D12Viewport::resize(const buw::viewportDescription& vpd) {
	if (viewport_) {
		viewport_->TopLeftX = static_cast<float>(vpd.left);
		viewport_->TopLeftY = static_cast<float>(vpd.top);
		viewport_->Width = static_cast<float>(vpd.width);
		viewport_->Height = static_cast<float>(vpd.height);
		viewport_->MinDepth = static_cast<float>(vpd.minDepth);
		viewport_->MaxDepth = static_cast<float>(vpd.maxDepth);
	}

	if (scissorRect_) {
		scissorRect_->left = vpd.left;
		scissorRect_->top = vpd.top;
		scissorRect_->right = vpd.width + vpd.left;
		scissorRect_->bottom = vpd.height + vpd.top;
	}
}

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END