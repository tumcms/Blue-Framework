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
#ifndef BlueFramework_Engine_namespace_dc167d4b_1ed2_47ca_8143_eb5b06085ed2_h
#define BlueFramework_Engine_namespace_dc167d4b_1ed2_47ca_8143_eb5b06085ed2_h

#define BLUEFRAMEWORK_ENGINE_NAMESPACE_BEGIN                              \
    namespace BlueFramework {                                                  \
    namespace Engine {
#define BLUEFRAMEWORK_ENGINE_NAMESPACE_END                                \
    }                                                                          \
    }

#define BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(X)                  \
    \
namespace buw {                                                                \
        using BlueFramework::Engine::X;                                        \
    \
}

#endif // end define
       // BlueFramework_Engine_namespace_dc167d4b_1ed2_47ca_8143_eb5b06085ed2_h
