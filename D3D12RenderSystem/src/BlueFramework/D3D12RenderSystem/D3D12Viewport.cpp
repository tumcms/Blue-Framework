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