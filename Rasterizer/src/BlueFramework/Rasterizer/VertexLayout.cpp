// Copied and modified code from "Oryol" library.
// This library is available under the MIT license. Original copyright notice:

/*
	The MIT License (MIT)

	Copyright (c) 2013 Andre Weissflog

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
	the Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
	FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
	COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// More details can be found in README.md file in the root directory.

#include "VertexLayout.h"

#include "BlueFramework/Rasterizer/namespace.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

/// get the byte size of a vertex format code
int ByteSize(eVertexAttributeFormat c) {
	switch (c) {
	case eVertexAttributeFormat::Float:
		return 4;
	case eVertexAttributeFormat::Float2:
		return 8;
	case eVertexAttributeFormat::Float3:
		return 12;
	case eVertexAttributeFormat::Float4:
		return 16;
	case eVertexAttributeFormat::Byte4:
	case eVertexAttributeFormat::Byte4N:
	case eVertexAttributeFormat::UByte4:
	case eVertexAttributeFormat::UByte4N:
	case eVertexAttributeFormat::Short2:
	case eVertexAttributeFormat::Short2N:
		return 4;
	case eVertexAttributeFormat::Short4:
	case eVertexAttributeFormat::Short4N:
		return 8;
    case eVertexAttributeFormat::Int:
    case eVertexAttributeFormat::UInt:
        return 4;
    case eVertexAttributeFormat::UInt3:
        return 12;
	default:
		BLUE_LOG(error) << "eVertexFormat ByteSize() called with invalid format!\n";
		return 0;
	}
}

const char *toString(const eVertexAttributeSemantic vas) {
	switch (vas) {
	case eVertexAttributeSemantic::Position:  return "position";
    case eVertexAttributeSemantic::Uv:        return "uv";
    case eVertexAttributeSemantic::Uvw:       return "uvw";
    case eVertexAttributeSemantic::Normal:    return "normal";
	case eVertexAttributeSemantic::Tangent:   return "tangent";
	case eVertexAttributeSemantic::Binormal:  return "binormal";
	case eVertexAttributeSemantic::Weights:   return "weights";
	case eVertexAttributeSemantic::Indices:   return "indices";
	case eVertexAttributeSemantic::Color:     return "color";
	case eVertexAttributeSemantic::Instance:  return "instance";
    case eVertexAttributeSemantic::PickId:    return "pickid";
    case eVertexAttributeSemantic::FaceId:    return "faceid";
    case eVertexAttributeSemantic::RegionId:  return "regionid";
	case eVertexAttributeSemantic::Size:      return "size";
    case eVertexAttributeSemantic::Id:        return "id";
	default:
		BLUE_LOG(error) << "VertexAttr::ToString(): invalid value!\n";
		throw std::runtime_error("Semantic does not exist.");
		//  return nullptr; // unreachable code
	}
}

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END
