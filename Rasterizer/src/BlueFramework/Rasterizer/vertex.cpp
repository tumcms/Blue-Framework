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

bool operator==(const VertexPosition3Color3Normal3Id1& lhs, const VertexPosition3Color3Normal3Id1& rhs) 
{
	return (lhs.position == rhs.position) && (lhs.color == rhs.color) && (lhs.normal == rhs.normal) && (lhs.id == rhs.id);
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
