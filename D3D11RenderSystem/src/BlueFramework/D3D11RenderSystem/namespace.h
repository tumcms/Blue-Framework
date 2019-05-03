/*
    This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2019 Technical University of Munich
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

#pragma once
#ifndef BlueFramework_D3D11RenderSystem_namespace_046c902d_8594_4544_bf59_23c76b1d1e69_h
#define BlueFramework_D3D11RenderSystem_namespace_046c902d_8594_4544_bf59_23c76b1d1e69_h

#define BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN namespace BlueFramework { namespace D3D11RenderSystem {
#define BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END }}

#define BLUEFRAMEWORK_D3D11RENDERSYSTEM_EMBED_INTO_BUW_NAMESPACE(X)	\
namespace buw {																\
	using BlueFramework::D3D11RenderSystem::X;							    \
}

#endif // end define BlueFramework_D3D11RenderSystem_namespace_046c902d_8594_4544_bf59_23c76b1d1e69_h
