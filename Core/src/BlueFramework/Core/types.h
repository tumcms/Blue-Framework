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
#ifndef BlueFramework_type_type_0f87ae96_1279_4925_b3f4_89e854dad4c6_h
#define BlueFramework_type_type_0f87ae96_1279_4925_b3f4_89e854dad4c6_h

#include "BlueFramework/Core/namespace.h"
#include <cstdint>

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

typedef unsigned char uint8;

typedef float float32;
typedef double float64;

typedef std::uint8_t uint8;
typedef std::uint16_t uint16;
typedef std::uint32_t uint32;
typedef std::uint64_t uint64;
typedef unsigned int uint;

typedef std::int8_t int8;
typedef std::int16_t int16;
typedef std::int32_t int32;
typedef std::int64_t int64;

typedef uint8 byte;
typedef uint16 word;
typedef uint32 doubleword;
typedef uint32 dword;
typedef uint64 quadword;
typedef uint64 qword;

typedef char char8;
typedef uint16 char16;
typedef uint32 char32;

BLUEFRAMEWORK_CORE_NAMESPACE_END

BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(uint8);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(uint16);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(uint32);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(uint64);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(uint);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(int8);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(int16);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(int32);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(int64);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(byte);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(word);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(doubleword);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(dword);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(quadword);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(qword);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(char8);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(char16);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(char32);

#endif // end define BlueFramework_type_type_0f87ae96_1279_4925_b3f4_89e854dad4c6_h