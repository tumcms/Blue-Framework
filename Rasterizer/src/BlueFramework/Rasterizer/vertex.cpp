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

#include "vertex.h"

#include "BlueFramework/Core/assert.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

//---------------------------------------------------------------------------//
// Compare
//---------------------------------------------------------------------------//

bool operator==(const VertexPosition3Texture2& lhs, const VertexPosition3Texture2& rhs) {
	return (lhs.position == rhs.position) && (rhs.uv == lhs.uv);
}

bool operator==(const VertexPosition3Normal3Texture2& lhs, const VertexPosition3Normal3Texture2& rhs) {
	return (lhs.position == rhs.position) && (lhs.normal == rhs.normal) && (rhs.uv == lhs.uv);
}

bool operator==(const VertexPosition3Color3Texture2& lhs, const VertexPosition3Color3Texture2& rhs) {
    return (lhs.position == rhs.position) && (rhs.color == lhs.color) && (rhs.uv == lhs.uv);
}

bool operator==(const VertexPosition3Color3Normal3& lhs, const VertexPosition3Color3Normal3& rhs) {
	return (lhs.position == rhs.position) && (rhs.color == lhs.color) && (lhs.normal == rhs.normal);
}

bool operator==(const VertexPosition3Id3& lhs, const VertexPosition3Id3& rhs) {
    return (lhs.position == rhs.position) && (rhs.id == lhs.id);
}

bool operator==(const VertexPosition3Texture2PickId1FaceId1RegionId1& lhs, const VertexPosition3Texture2PickId1FaceId1RegionId1& rhs) {
    return (lhs.position == rhs.position) && (rhs.uv == lhs.uv) && (rhs.pickid == lhs.pickid) && (rhs.faceid == lhs.faceid) && (rhs.regionid == lhs.regionid);
}

//---------------------------------------------------------------------------//
// Less than
//---------------------------------------------------------------------------//

bool operator<(const VertexPosition3Normal3Texture2& lhs, const VertexPosition3Normal3Texture2& rhs) {
	// alphabetic sorting abc < dfe
	for (int i = 0; i < 3; i++)	{
		if (lhs.position[i] != rhs.position[i])	{
			return lhs.position[i] < rhs.position[i];
		}
	}

	for (int i = 0; i < 3; i++)	{
		if (lhs.normal[i] != rhs.normal[i])	{
			return lhs.normal[i] < rhs.normal[i];
		}
	}

	for (int i = 0; i < 2; i++)	{
		if (lhs.uv[i] != rhs.uv[i])	{
			return lhs.uv[i] < rhs.uv[i];
		}
	}

	BLUE_ASSERT(lhs == rhs, "Not equal.");
	return false; // must be equal
}

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END
