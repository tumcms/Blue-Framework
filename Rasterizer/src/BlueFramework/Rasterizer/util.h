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
