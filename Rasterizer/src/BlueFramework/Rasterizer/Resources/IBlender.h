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

#pragma once
#ifndef BlueFramework_Rasterizer_IBlender_cc3760d2_ed0b_4aef_9412_eb5f698ba671_h
#define BlueFramework_Rasterizer_IBlender_cc3760d2_ed0b_4aef_9412_eb5f698ba671_h

#include "BlueFramework/Core/memory.h"
#include "BlueFramework/Core/NonCopyable.h"
#include "BlueFramework/Rasterizer/namespace.h"
#include "BlueFramework/Rasterizer/renderDescriptors.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN


class IBlender : public buw::NonCopyable {
public:
    IBlender(buw::blendStateDescription) {}
    virtual ~IBlender() {}
};

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END

BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(IBlender)

#endif // end define BlueFramework_Rasterizer_IBlender_cc3760d2_ed0b_4aef_9412_eb5f698ba671_h
