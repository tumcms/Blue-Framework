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

#ifndef __NAMESPACE_H_63DA257C4F6A4B51B073A296E1D637FE__
#define __NAMESPACE_H_63DA257C4F6A4B51B073A296E1D637FE__

#define BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN namespace BlueFramework { namespace GLRenderSystem {
#define BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END }}

#define BLUE_BLUEFRAMEWORK_GLRENDERSYSTEM_EMBED_INTO_BUW_NAMESPACE(X)	\
namespace buw {																\
	using BlueFramework::GLRenderSystem::X;							    \
}

#endif // __NAMESPACE_H_63DA257C4F6A4B51B073A296E1D637FE__
