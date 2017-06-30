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

#ifndef BlueFramework_Core_VertexLayout_791ddb4f_7c49_49c2_a1d8_f16497e0f3d4_h
#define BlueFramework_Core_VertexLayout_791ddb4f_7c49_49c2_a1d8_f16497e0f3d4_h

#include "BlueFramework/Rasterizer/namespace.h"
#include "BlueFramework/Core/Diagnostics/log.h"
#include "BlueFramework/Core/Exception.h"
#include <cstdint>
#include <vector>

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

enum class eVertexAttributeSemantic : std::uint8_t {
	Position = 0,   ///< "position"
	Normal,         ///< "normal"
    Uv,				///< "uv"
    Uvw,			///< "uvw"
    Tangent,        ///< "tangent
	Binormal,       ///< "binormal"
	Weights,        ///< "weights" (skin weights)
	Indices,        ///< "indices" (skin indices)
	Color,         ///< "color0"
	Instance,      ///< "instance0"
    PickId,         ///< "pickid"
    FaceId,         ///< "faceid"
    RegionId,       ///< "regionid"
    Id,             ///< "arbitrary id"
	Size,
	NumVertexAttrs,
	InvalidVertexAttr
};

const char *toString(const eVertexAttributeSemantic vas);

enum class eVertexAttributeFormat {
    InvalidVertexFormat		= 0,     ///< the invalid vertex format value
    Float					= 1<<0,  ///< single component float, expanded to (x, 0, 0, 1)
    Float2					= 1<<1,  ///< 2-component float, expanded to (x, y, 0, 1)
    Float3					= 1<<2,  ///< 3-component float, expanded to (x, y, z, 1)
    Float4					= 1<<3,  ///< 4-component float
    Byte4					= 1<<4,  ///< 4-component float (-128.0f..+127.0f) mapped to byte (-128..+127)
    Byte4N					= 1<<5,  ///< 4-component float (-1.0f..+1.0f) mapped to byte (-128..+127)
    UByte4					= 1<<6,  ///< 4-component float (0.0f..255.0f) mapped to byte (0..255)
    UByte4N					= 1<<7,  ///< 4-component float (0.0f..+1.0) mapped to byte (0..255)
    Short2					= 1<<8,  ///< 2-component float (-32768.0f..+32767.0f) mapped to short (-32768..+32768)
    Short2N					= 1<<9,  ///< 2-component float (-1.0f..+1.0f) mapped to short (-32768..+32768)
    Short4					= 1<<10, ///< 4-component float (-32768.0f..+32767.0f) mapped to short (-32768..+32768)
    Short4N					= 1<<11, ///< 4-component float (-1.0f..+1.0f) mapped to short (-32768..+32768)
	Int						= 1<<12, ///< 1-component integer
    UInt					= 1<<13, ///< 1-component unsigned integer
    UInt3					= 1<<14, ///< 3-component unsigned integer
    //NumVertexFormats		= 1<<15, ///< number of vertex formats // FIXME: used nowhere. remove?
	////////////////////////////////////////////////////////////////////////////////
	FloatType				= Float | Float2 | Float3 | Float4,
	ByteType				= Byte4 | Byte4N | UByte4 | UByte4N,
	ShortType				= Short2 | Short2N | Short4 | Short4N,
	IntType					= Int | UInt | UInt3,
	SignedType				= FloatType | Byte4 | Byte4N | Short2 | Short2N | Short4 | Short4N | Int,
	NormalizeType			= Byte4N | UByte4N | Short2N | Short4N,
	_1Components			= Float | Int | UInt,
	_2Components			= Float2 | Short2 | Short2N,
	_3Components			= Float3 | UInt3,
	_4Components			= Float4 | Byte4 | Byte4N | UByte4 | UByte4N | Short4 | Short4N
};

class VertexAttribute {
public:
	/// default constructor
	VertexAttribute() {
		semanticIndex = 0;
	};
	/// construct from vertex attr and format
	VertexAttribute(eVertexAttributeSemantic attr, eVertexAttributeFormat format) :
	semantic(attr), format(format) {
		semanticIndex = 0;
	};
	
	/// get byte size of component
	int ByteSize() const {
		if (format == eVertexAttributeFormat::Float4)
		{
			return 16;
		}
		if (format == eVertexAttributeFormat::Float3 || format == eVertexAttributeFormat::UInt3)
		{
			return 12;
		}
		if (format == eVertexAttributeFormat::Float2)
		{
			return 8;
		}
		if (format == eVertexAttributeFormat::Float)
		{
			return 4;
		}
        if (format == eVertexAttributeFormat::Int || format == eVertexAttributeFormat::UInt)
        {
            return 4;
        }
		throw buw::Exception("Unknown bytes size.");
	}

	unsigned int             semanticIndex;
	eVertexAttributeSemantic semantic;
	eVertexAttributeFormat   format;
};

enum class eVertexLayoutStepFunction : int {
	PerVertex = 0,
    PerInstance = 1
};

class VertexLayout {
public:
	VertexLayout() {
		stepFunction = eVertexLayoutStepFunction::PerVertex;
		stepRate = 1;
	};
	virtual ~VertexLayout() {};

	/// clear the vertex layout, chainable
	VertexLayout& clear() {
		components.clear();
	}
	/// return true if layout is empty
	bool empty() const {
		return components.empty();
	}

	/// add a component
	VertexLayout& add(const VertexAttribute& comp) {
		components.push_back(comp);
	}
	/// add component by name and format
	VertexLayout& add(const eVertexAttributeSemantic semantic, const eVertexAttributeFormat format) {
		components.push_back(VertexAttribute(semantic, format));
		return *this;
	}
	/// enable layout for instancing, set StepFunction to PerInstance and StepRate to 1
	VertexLayout& enableInstancing() {
		stepFunction = eVertexLayoutStepFunction::PerInstance;
		stepRate = 1;
		return *this;
	}

	/// get number of components
	int componentCount() const {
		return static_cast<int>(components.size());
	}
	/// get component at index
	const VertexAttribute& componentAt(size_t const index) const {
		return components[index];
	}

	int getVertexByteSize() const {
		int size = 0;
		for (int i = 0; i < componentCount(); i++) {
			size += componentAt(i).ByteSize();
		}
		return size;
	}

public:
	/// the vertex step function, used for instancing, default is 'PerVertex'
	eVertexLayoutStepFunction stepFunction;

	// the vertex step rate, used for instancing
	uint8_t stepRate;

	std::vector<VertexAttribute> components;
};

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END

BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(toString)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(eVertexAttributeSemantic)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(eVertexAttributeFormat)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(eVertexLayoutStepFunction)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexAttribute)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexLayout)

#endif // end define BlueFramework_Core_NAME_791ddb4f_7c49_49c2_a1d8_f16497e0f3d4_h
