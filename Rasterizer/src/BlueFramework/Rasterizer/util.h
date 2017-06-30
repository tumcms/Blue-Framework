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

#include "BlueFramework/Rasterizer/namespace.h"
#include "BlueFramework/Rasterizer/renderDescriptors.h"

#include <memory>

#pragma once
#ifndef BlueFramework_Rasterizer_util_e829b782_cfc2_463a_b3ed_91f834624e00_h
#define BlueFramework_Rasterizer_util_e829b782_cfc2_463a_b3ed_91f834624e00_h

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

inline void convertD24ToF32(void* d24, float &f32) {
    char d32[4];
    std::memcpy(d32, d24, 3);
    d32[3] = 0;
    int* d32_unorm_uint = reinterpret_cast<int*>(d32);
    f32 = float(*d32_unorm_uint) / float(0xffffff);    
}

inline void convertR32ToUINT32(void* r32, UINT &u32) {
	char r32b[4];
	std::memcpy(r32b, r32, 3);
	r32b[3] = 0;
	UINT* r32_unorm_uint = reinterpret_cast<UINT*>(r32b);
	u32 = *r32_unorm_uint;
}

bool loadRenderSystemSettings(const std::string& filename, eRenderAPI& renderAPI, bool& warp, bool& msaa);

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END


BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(convertD24ToF32)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(convertR32ToUINT32)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(loadRenderSystemSettings)

#endif // end define BlueFramework_BlueFramework_Rasterizer_util_e829b782_cfc2_463a_b3ed_91f834624e00_h
