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
#ifndef BlueFramework_Engine_geometryGeneration_f5837c95_3f02_435a_b246_459e48cefdff_h
#define BlueFramework_Engine_geometryGeneration_f5837c95_3f02_435a_b246_459e48cefdff_h

#include "BlueFramework/Rasterizer/vertex.h"
#include "BlueFramework/Engine/namespace.h"
#include <string>
#include <vector>

BLUEFRAMEWORK_ENGINE_NAMESPACE_BEGIN

void createIndexedCube(
	std::vector<buw::VertexPosition3Normal3Texture2>& o_vertexBuffer, 
	std::vector<unsigned int>& o_indices);

//! Creates a vertex and index buffer for a Cube - front facing triangles are 
//! counterclockwise-wounded.
/*
	\param[out]		o_vertexBuffer	Vertex buffer used to store the vertices of the generated cube.
	\param[out]		o_indices		Index buffer used to store the gernated indices of the cube.
	\param[in]		sizeX			Width of cube.
	\param[in]		sizeY			Height of cube.
	\param[in]		sizeZ			Depth of cube.
*/
void createIndexedCube(
	std::vector<buw::VertexPosition3Texture2>& o_vertexBuffer, 
	std::vector<unsigned int>& o_indices,
	const float sizeX, const float sizeY, const float sizeZ);

// create a vertex and index buffer for a sphere - front facing triangles are 
// counterclockwise-wounded
void createIndexedSphere(
	const float radius, const int latitudeBands, const int longitudeBands,
	std::vector<buw::VertexPosition3Normal3Texture2>& o_vertexBuffer, 
	std::vector<unsigned int>& o_indices );

void createIndexedMesh(
	const std::string& filename,
	std::vector<buw::VertexPosition3Normal3Texture2>& o_vertexBuffer, 
	std::vector<unsigned int>& o_indices );

// create a grid
void createGrid(
	int gridLength, 
	int gridStartX, 
	int gridStartY, 
	int stepSize,
	std::vector<buw::VertexPosition3Normal3Texture2>& o_vertexBuffer);

void createIndexedPlane(
	const int width,
	const int height,
	std::vector<buw::VertexPosition3Normal3Texture2>& o_vertices, 
	std::vector<std::uint32_t>& o_indices,
	const int repationsX = 1,
	const int repationY = 1);

BLUEFRAMEWORK_ENGINE_NAMESPACE_END

BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(createIndexedCube);
BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(createIndexedSphere);
BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(createIndexedMesh);
BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(createGrid);
BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(createIndexedPlane);

#endif // end define BlueFramework_Engine_geometryGeneration_f5837c95_3f02_435a_b246_459e48cefdff_h
