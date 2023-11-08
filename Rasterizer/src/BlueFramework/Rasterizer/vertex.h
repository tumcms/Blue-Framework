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

#ifndef BlueFramework_Rasterizer_vertex_96687421_3eaf_4769_80fe_fb2fc11c93da_h
#define BlueFramework_Rasterizer_vertex_96687421_3eaf_4769_80fe_fb2fc11c93da_h

#include "BlueFramework/Core/Math/vector.h"
#include "BlueFramework/Rasterizer/VertexLayout.h"
#include "BlueFramework/Rasterizer/namespace.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

template <typename T, int Dim, int ByteAlignment>
struct VertexAttributeType {
public:
	VertexAttributeType() {
		for (int i = 0; i < Dim; i++)
			data[i] = T();
	}
	VertexAttributeType(const buw::Vector<T, Dim>& v) {
		for (int i = 0; i < Dim; i++)
			data[i] = v(i);
	}
	VertexAttributeType(const T& v) : VertexAttributeType(buw::Vector<T, Dim>().setConstant(v)) {
	}

	const T& operator[](int i) const {
		return data[i];
	}

	T& operator[](int i) {
		return data[i];
	}

	bool operator==(const VertexAttributeType& rhs) const {
		for (int i = 0; i < Dim; i++)
			if (data[i] != rhs.data[i])
				return false;
		return true;
	}

	bool operator!=(const VertexAttributeType& rhs) const {
		for (int i = 0; i < Dim; i++)
			if (data[i] != rhs.data[i])
				return true;
		return false;
	}

	alignas(ByteAlignment)T data[Dim];
};

namespace Unaligned {
	// introduced to fix Eigen alignment issues
	typedef VertexAttributeType<bool, 1, 0> Bool;

	typedef VertexAttributeType<float, 1, 0> Float;
	typedef VertexAttributeType<float, 2, 0> Float2;
	typedef VertexAttributeType<float, 3, 0> Float3;
	typedef VertexAttributeType<float, 4, 0> Float4;

	typedef VertexAttributeType<int, 1, 0> Int;
	typedef VertexAttributeType<int, 2, 0> Int2;
	typedef VertexAttributeType<int, 3, 0> Int3;
	typedef VertexAttributeType<int, 4, 0> Int4;

	typedef VertexAttributeType<unsigned int, 1, 0> UInt;
	typedef VertexAttributeType<unsigned int, 2, 0> UInt2;
	typedef VertexAttributeType<unsigned int, 3, 0> UInt3;
	typedef VertexAttributeType<unsigned int, 4, 0> UInt4;
}

namespace AlignedTo16Byte {
	typedef VertexAttributeType<bool, 1, 16> Bool;

	typedef VertexAttributeType<float, 1, 16> Float;
	typedef VertexAttributeType<float, 2, 16> Float2;
	typedef VertexAttributeType<float, 3, 16> Float3;
	typedef VertexAttributeType<float, 4, 16> Float4;

	typedef VertexAttributeType<int, 1, 16> Int;
	typedef VertexAttributeType<int, 2, 16> Int2;
	typedef VertexAttributeType<int, 3, 16> Int3;
	typedef VertexAttributeType<int, 4, 16> Int4;

	typedef VertexAttributeType<unsigned int, 1, 16> UInt;
	typedef VertexAttributeType<unsigned int, 2, 16> UInt2;
	typedef VertexAttributeType<unsigned int, 3, 16> UInt3;
	typedef VertexAttributeType<unsigned int, 4, 16> UInt4;
}

struct VertexPosition3 {
public:
	VertexPosition3() {
	}

	VertexPosition3(const buw::Vector3f& position) : position(position) {
	}

	Unaligned::Float3 position;

public:
	static VertexLayout getVertexLayout() {
		buw::VertexLayout vertexLayout;
		vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);

		return vertexLayout;
	}
};

struct VertexPosition3Texture2 {
public:
	VertexPosition3Texture2() {
	}

	VertexPosition3Texture2(const buw::Vector3f& position, const buw::Vector2f& uv) : position(position), uv(uv) {
	}

	Unaligned::Float3 position;
	Unaligned::Float2 uv;

public:
	static VertexLayout getVertexLayout() {
		buw::VertexLayout vertexLayout;
		vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Uv, buw::eVertexAttributeFormat::Float2);

		return vertexLayout;
	}
};

struct VertexPosition3Texture3 {
public:
    VertexPosition3Texture3() {
    }

    VertexPosition3Texture3(const buw::Vector3f& position, const buw::Vector3f& uvw) : position(position), uvw(uvw) {
    }

    Unaligned::Float3 position;
    Unaligned::Float3 uvw;

public:
    static VertexLayout getVertexLayout() {
        buw::VertexLayout vertexLayout;
        vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
        vertexLayout.add(buw::eVertexAttributeSemantic::Uvw, buw::eVertexAttributeFormat::Float3);

        return vertexLayout;
    }
};

struct VertexPosition4Texture2 {
public:
	VertexPosition4Texture2() {
	}

	VertexPosition4Texture2(const buw::Vector4f& position, const buw::Vector2f& uv) : position(position), uv(uv) {
	}

	Unaligned::Float4 position;
	Unaligned::Float2 uv;

public:
	static VertexLayout getVertexLayout() {
		buw::VertexLayout vertexLayout;
		vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float4);
		vertexLayout.add(buw::eVertexAttributeSemantic::Uv, buw::eVertexAttributeFormat::Float2);

		return vertexLayout;
	}
};

struct VertexPosition3Color3Size1 {
public:
	VertexPosition3Color3Size1() {
	}

	VertexPosition3Color3Size1(const buw::Vector3f& position, const buw::Vector3f& color, const float size) : position(position), color(color), size(size) {
	}

	Unaligned::Float3 position;
	Unaligned::Float3 color;
	Unaligned::Float size;

public:
	static VertexLayout getVertexLayout() {
		buw::VertexLayout vertexLayout;
		vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Color, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Size, buw::eVertexAttributeFormat::Float);

		return vertexLayout;
	}
};

struct VertexPosition3Color4 {
public:
	VertexPosition3Color4() {
	}

	VertexPosition3Color4(const buw::Vector3f& position, const buw::Vector4f& color) : position(position), color(color) {
	}

	Unaligned::Float3 position;
	Unaligned::Float4 color;

public:
	static VertexLayout getVertexLayout() {
		buw::VertexLayout vertexLayout;
		vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Color, buw::eVertexAttributeFormat::Float4);

		return vertexLayout;
	}
};

struct VertexPosition3Normal3Texture2 {
public:
	VertexPosition3Normal3Texture2() {
	}

	VertexPosition3Normal3Texture2(const buw::Vector3f& position, const buw::Vector3f& normal, const buw::Vector2f& uv) : position(position), normal(normal), uv(uv) {
	}

	Unaligned::Float3 position;
	Unaligned::Float3 normal;
	Unaligned::Float2 uv;

public:
	static VertexLayout getVertexLayout() {
		buw::VertexLayout vertexLayout;
		vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Normal, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Uv, buw::eVertexAttributeFormat::Float2);

		return vertexLayout;
	}
};

struct VertexPosition3Color3Normal3 {
public:
	VertexPosition3Color3Normal3() {
	}

	VertexPosition3Color3Normal3(const buw::Vector3f position, const buw::Vector3f& color, const buw::Vector3f& normal) : position(position), color(color), normal(normal) {
	}

	Unaligned::Float3 position;
	Unaligned::Float3 color;
	Unaligned::Float3 normal;

public:
	static VertexLayout getVertexLayout() {
		buw::VertexLayout vertexLayout;
		vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Color, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Normal, buw::eVertexAttributeFormat::Float3);

		return vertexLayout;
	}
};

struct VertexPosition3Color3Normal3Id1 {
public:
	VertexPosition3Color3Normal3Id1() {
	}

	VertexPosition3Color3Normal3Id1(
		const buw::Vector3f position,
		const buw::Vector3f& color,
		const buw::Vector3f& normal,
		const uint32_t& id)
	:
	position(position),
	color(color),
	normal(normal),
	id(id)
	{	}

	Unaligned::Float3 position;
	Unaligned::Float3 color;
	Unaligned::Float3 normal;
	Unaligned::UInt id;

public:
	static VertexLayout getVertexLayout() {
		buw::VertexLayout vertexLayout;
		vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Color, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Normal, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::PickId, buw::eVertexAttributeFormat::UInt);

		return vertexLayout;
	}
};

struct VertexPosition3Color3Texture2 {
public:
	VertexPosition3Color3Texture2() {
	}

	VertexPosition3Color3Texture2(const buw::Vector3f position, const buw::Vector3f& color, const buw::Vector2f& uv) : position(position), color(color), uv(uv) {
	}

	Unaligned::Float3 position;
	Unaligned::Float3 color;
	Unaligned::Float2 uv;

public:
	static VertexLayout getVertexLayout() {
		buw::VertexLayout vertexLayout;
		vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Color, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Uv, buw::eVertexAttributeFormat::Float2);

		return vertexLayout;
	}
};

struct VertexPosition3Texture2PickId1FaceId1RegionId1 {
	VertexPosition3Texture2PickId1FaceId1RegionId1() {
	}

	VertexPosition3Texture2PickId1FaceId1RegionId1(const buw::Vector3f& position, const buw::Vector2f& uv, const UINT& pickid, const int& faceid, const int& regionid)
	    : position(position), uv(uv), pickid(pickid), faceid(faceid), regionid(regionid) {
	}

	Unaligned::Float3 position;
	Unaligned::Float2 uv;
	Unaligned::UInt pickid;
	Unaligned::Int faceid;
	Unaligned::Int regionid;

public:
	static VertexLayout getVertexLayout() {
		buw::VertexLayout vertexLayout;
		vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Uv, buw::eVertexAttributeFormat::Float2);
		vertexLayout.add(buw::eVertexAttributeSemantic::PickId, buw::eVertexAttributeFormat::UInt);
		vertexLayout.add(buw::eVertexAttributeSemantic::FaceId, buw::eVertexAttributeFormat::Int);
		vertexLayout.add(buw::eVertexAttributeSemantic::RegionId, buw::eVertexAttributeFormat::Int);
		return vertexLayout;
	}
};

struct VertexPosition3Id3 {
    VertexPosition3Id3() {}

    VertexPosition3Id3(const buw::Vector3f& position, const UINT& id0, const UINT& id1, const UINT& id2)
        : position(position), id({ id0, id1, id2 }) {

    }

    Unaligned::Float3 position;
    Unaligned::UInt3 id;

public:
    static VertexLayout getVertexLayout() {
        buw::VertexLayout vertexLayout;
        vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
        vertexLayout.add(buw::eVertexAttributeSemantic::Id, buw::eVertexAttributeFormat::UInt3);
        return vertexLayout;
    }
};

struct VertexPosition3Id3Texture2 {
    VertexPosition3Id3Texture2() {}

    VertexPosition3Id3Texture2(const buw::Vector3f& position, const UINT& id0, const UINT& id1, const UINT& id2, const buw::Vector2f &uv)
        : position(position), id({ id0, id1, id2 }), uv(uv) {

    }

    Unaligned::Float3 position;
    Unaligned::UInt3 id;
    Unaligned::Float2 uv;

public:
    static VertexLayout getVertexLayout() {
        buw::VertexLayout vertexLayout;
        vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
        vertexLayout.add(buw::eVertexAttributeSemantic::Id, buw::eVertexAttributeFormat::UInt3);
        vertexLayout.add(buw::eVertexAttributeSemantic::Uv, buw::eVertexAttributeFormat::Float2);
        return vertexLayout;
    }
};

struct VertexPosition3Normal3Id3Texture2 {
	VertexPosition3Normal3Id3Texture2() {}

	VertexPosition3Normal3Id3Texture2(const buw::Vector3f& position, const buw::Vector3f& normal, const UINT& id0, const UINT& id1, const UINT& id2, const buw::Vector2f &uv)
		: position(position), normal(normal), id({ id0, id1, id2 }), uv(uv) {

	}

	Unaligned::Float3 position;
	Unaligned::Float3 normal;
	Unaligned::UInt3 id;
	Unaligned::Float2 uv;

public:
	static VertexLayout getVertexLayout() {
		buw::VertexLayout vertexLayout;
		vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Normal, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Id, buw::eVertexAttributeFormat::UInt3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Uv, buw::eVertexAttributeFormat::Float2);
		return vertexLayout;
	}
};

struct VertexPosition3Normal3 {
	VertexPosition3Normal3() {}

	VertexPosition3Normal3(buw::Vector3f const& position, buw::Vector3f const& normal)
		: position(position), normal(normal) {}

	Unaligned::Float3 position;
	Unaligned::Float3 normal;

public:
	static VertexLayout getVertexLayout() {
		buw::VertexLayout vertexLayout;
		vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Normal, buw::eVertexAttributeFormat::Float3);
		return vertexLayout;
	}
};

struct VertexPosition4 {
public:
	VertexPosition4() {
	}

	VertexPosition4(const buw::Vector4f& position) : position(position) {
	}

	Unaligned::Float4 position;

public:
	static VertexLayout getVertexLayout() {
		buw::VertexLayout vertexLayout;
		vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float4);

		return vertexLayout;
	}
};

//---------------------------------------------------------------------------//
// Compare
//---------------------------------------------------------------------------//

bool operator==(const VertexPosition3Texture2& lhs, const VertexPosition3Texture2& rhs);
bool operator==(const VertexPosition3Color3Normal3& lhs, const VertexPosition3Color3Normal3& rhs);
bool operator==(const VertexPosition3Normal3Texture2& lhs, const VertexPosition3Normal3Texture2& rhs);
bool operator==(const VertexPosition3Color3Texture2& lhs, const VertexPosition3Color3Texture2& rhs);
bool operator==(const VertexPosition3Texture2PickId1FaceId1RegionId1& lhs, const VertexPosition3Texture2PickId1FaceId1RegionId1& rhs);
bool operator==(const VertexPosition3Color3Normal3Id1& lhs, const VertexPosition3Color3Normal3Id1& rhs);

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END

BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(operator==)

BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexPosition3)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexPosition3Color3Normal3)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexPosition3Color3Size1)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexPosition3Color3Texture2)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexPosition3Color4)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexPosition3Id3)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexPosition3Id3Texture2)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexPosition3Normal3Id3Texture2)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexPosition3Normal3)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexPosition3Normal3Texture2)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexPosition3Texture2)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexPosition3Texture3)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexPosition3Texture2PickId1FaceId1RegionId1)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexPosition4)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexPosition4Texture2)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(VertexPosition3Color3Normal3Id1)

#endif // end define BlueFramework_Rasterizer_vertex_96687421_3eaf_4769_80fe_fb2fc11c93da_h
