/*
    This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2018 Technical University of Munich
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

#include "geometryGeneration.h"

#include "BlueFramework/Core/Math/constants.h"
#include "BlueFramework/Core/assert.h"
#include <boost/filesystem.hpp> 
#include <algorithm>

#define add_triangle(i0, i1, i2) { o_indices.push_back(i0); o_indices.push_back(i1); o_indices.push_back(i2); }

BLUEFRAMEWORK_ENGINE_NAMESPACE_BEGIN

// Winding Order: CCW, 
// IndexType: std::uint32_t, 
// VertexFormat: VertexPosition3fNormal3fTexture2f, 
// Indexed: yes
// Output Geometry Type: Triangle Strip
// Coordinate Sytem: OpenGL like
// creates a plane that resides in the x,z Plane. The normal vector points upward
void createIndexedPlane(
	const int width,
	const int height,
	std::vector<buw::VertexPosition3Normal3Texture2>& o_vertices, 
	std::vector<std::uint32_t>& o_indices,
	const int repationsX,
	const int repationY) {
	// create local vertices
	o_vertices.resize(width*height);

	for (int z = 0; z < height; z++) 
	{
		for (int x = 0; x < width; x++) 
		{
			float heightValue = 0;
			// center x,z on origin
			float offset = 0;;
			float scale = 1;

			int index = x + (z * width);
			o_vertices[index].position = buw::Vector3f(
				(scale*(float)x) - offset, 
				heightValue, 
				(scale*(float)z) - offset);
			o_vertices[index].normal = buw::Vector3f(0.0f,1.0f,0.0f);
			o_vertices[index].uv = buw::Vector2f( (static_cast<float>(x)/width) * repationsX , (static_cast<float>(z)/height) * repationY );
			//vertices[index].Color = Color.White;
		}
	}

	// create local indices
	for (int z = 0; z < height - 1; z++) {
		// degenerate index on non-first row
		if (z != 0) o_indices.push_back(z * width);

		// main strip
		for (int x = 0; x < width; x++) {
			o_indices.push_back(z * width + x);
			o_indices.push_back((z + 1) * width + x);
		}

		// degenerate index on non-last row
		if (z != (width-2)) 
			o_indices.push_back((z + 1) * width + (height - 1));
	}
}

void createIndexedCube(
	std::vector<buw::VertexPosition3Texture2>& o_vertexBuffer, 
	std::vector<unsigned int>& o_indices,
	const float sizeX, const float sizeY, const float sizeZ)
{
	class VertexBufferBuilder
	{
	public:
		VertexBufferBuilder()
		{

		}

		void addPosition(buw::Vector3f position)
		{
			positions.push_back(position);
		}

		void addTextureCoordinate(buw::Vector2f textureCoordinate)
		{
			textureCoordinates.push_back(textureCoordinate);
		}

		int createVertexAndGetIndex(int positionIndex, int textureIndex)
		{
			buw::VertexPosition3Texture2 vertex = buw::VertexPosition3Texture2(positions[positionIndex], textureCoordinates[textureIndex]);
			std::vector<buw::VertexPosition3Texture2>::iterator iter = std::find(vertices.begin(), vertices.end(), vertex);

			size_t o_indices = std::distance(vertices.begin(), iter);

			if(o_indices == vertices.size())
			{
				// create vertex
				vertices.push_back(vertex);
			}

			return static_cast<int>(o_indices);
		}

		std::vector<buw::VertexPosition3Texture2> getVertices()
		{
			return vertices;
		}

	private:
		std::vector<buw::Vector3f> positions;
		std::vector<buw::Vector2f> textureCoordinates;

		std::vector<buw::VertexPosition3Texture2> vertices;
	};

	VertexBufferBuilder vbb;

	vbb.addPosition( buw::Vector3f( -sizeX/2, -sizeY/2,  sizeZ/2) ); // 0
	vbb.addPosition( buw::Vector3f(  sizeX/2, -sizeY/2,  sizeZ/2) ); // 1
	vbb.addPosition( buw::Vector3f(  sizeX/2, -sizeY/2, -sizeZ/2) ); // 2
	vbb.addPosition( buw::Vector3f( -sizeX/2, -sizeY/2, -sizeZ/2) ); // 3
	vbb.addPosition( buw::Vector3f( -sizeX/2,  sizeY/2,  sizeZ/2) ); // 4
	vbb.addPosition( buw::Vector3f(  sizeX/2,  sizeY/2,  sizeZ/2) ); // 5
	vbb.addPosition( buw::Vector3f(  sizeX/2,  sizeY/2, -sizeZ/2) ); // 6
	vbb.addPosition( buw::Vector3f( -sizeX/2,  sizeY/2, -sizeZ/2) ); // 7
							
	vbb.addTextureCoordinate( buw::Vector2f(0,0) ); // 0
	vbb.addTextureCoordinate( buw::Vector2f(1,0) ); // 1
	vbb.addTextureCoordinate( buw::Vector2f(0,1) ); // 2
	vbb.addTextureCoordinate( buw::Vector2f(1,1) ); // 3

	class IndexBufferBuilder
	{
	public:
		void addTringleIndices(int v1, int v2, int v3)
		{
			indices.push_back(v1);
			indices.push_back(v2);
			indices.push_back(v3);
		}

		void addQuadIndices(int v1, int v2, int v3, int v4)
		{
			indices.push_back(v1);
			indices.push_back(v2);
			indices.push_back(v3);

			indices.push_back(v3);
			indices.push_back(v4);
			indices.push_back(v1);
		}

		std::vector<unsigned int> indices;
	};
				
	IndexBufferBuilder ibb;
				
	// Front z+
	int a = vbb.createVertexAndGetIndex(0, 0);
	int b = vbb.createVertexAndGetIndex(1, 1);
	int c = vbb.createVertexAndGetIndex(5, 3);
	int d = vbb.createVertexAndGetIndex(4, 2);

	ibb.addQuadIndices( 
		a,b,c,d
		);

	// Back z-
	ibb.addQuadIndices( 
		vbb.createVertexAndGetIndex(2, 0),
		vbb.createVertexAndGetIndex(3, 1),
		vbb.createVertexAndGetIndex(7, 3),
		vbb.createVertexAndGetIndex(6, 2)
		);

	// Right x+
	ibb.addQuadIndices( 
		vbb.createVertexAndGetIndex(1, 0),
		vbb.createVertexAndGetIndex(2, 1),
		vbb.createVertexAndGetIndex(6, 3),
		vbb.createVertexAndGetIndex(5, 2)
		);

	// Left x-
	ibb.addQuadIndices( 
		vbb.createVertexAndGetIndex(3, 0),
		vbb.createVertexAndGetIndex(0, 1),
		vbb.createVertexAndGetIndex(4, 3),
		vbb.createVertexAndGetIndex(7, 2)
		);

	// Top y+
	ibb.addQuadIndices( 
		vbb.createVertexAndGetIndex(4, 0),
		vbb.createVertexAndGetIndex(5, 1),
		vbb.createVertexAndGetIndex(6, 3),
		vbb.createVertexAndGetIndex(7, 2)
		);

	// Bottom y-
	ibb.addQuadIndices( 
		vbb.createVertexAndGetIndex(3, 0),
		vbb.createVertexAndGetIndex(2, 1),
		vbb.createVertexAndGetIndex(1, 3),
		vbb.createVertexAndGetIndex(0, 2)
		);
				
	o_vertexBuffer = vbb.getVertices();
	o_indices = ibb.indices;
}

void createBoundingBox(std::vector<buw::VertexPosition3>& o_vertexBuffer, std::vector<unsigned int>& o_indices, const float centerX, const float centerY, const float centerZ, const float sizeX, const float sizeY, const float sizeZ)
{
	size_t startIndex = o_vertexBuffer.size();

	o_vertexBuffer.push_back(buw::VertexPosition3(buw::Vector3f(centerX + sizeX, centerY + sizeY, centerZ + sizeZ)));
	o_vertexBuffer.push_back(buw::VertexPosition3(buw::Vector3f(centerX - sizeX, centerY + sizeY, centerZ + sizeZ)));
	o_vertexBuffer.push_back(buw::VertexPosition3(buw::Vector3f(centerX + sizeX, centerY - sizeY, centerZ + sizeZ)));	
	o_vertexBuffer.push_back(buw::VertexPosition3(buw::Vector3f(centerX + sizeX, centerY + sizeY, centerZ - sizeZ)));
	o_vertexBuffer.push_back(buw::VertexPosition3(buw::Vector3f(centerX - sizeX, centerY - sizeY, centerZ + sizeZ)));
	o_vertexBuffer.push_back(buw::VertexPosition3(buw::Vector3f(centerX + sizeX, centerY - sizeY, centerZ - sizeZ)));
	o_vertexBuffer.push_back(buw::VertexPosition3(buw::Vector3f(centerX - sizeX, centerY + sizeY, centerZ - sizeZ)));
	o_vertexBuffer.push_back(buw::VertexPosition3(buw::Vector3f(centerX - sizeX, centerY - sizeY, centerZ - sizeZ)));

	// Connect all points which differ in only 1 dimension.
	o_indices.push_back(startIndex);
	o_indices.push_back(startIndex + 1);

	o_indices.push_back(startIndex);
	o_indices.push_back(startIndex + 2);

	o_indices.push_back(startIndex);
	o_indices.push_back(startIndex + 3);

	o_indices.push_back(startIndex + 1);
	o_indices.push_back(startIndex + 4);

	o_indices.push_back(startIndex + 1);
	o_indices.push_back(startIndex + 6);

	o_indices.push_back(startIndex + 2);
	o_indices.push_back(startIndex + 4);

	o_indices.push_back(startIndex + 2);
	o_indices.push_back(startIndex + 5);

	o_indices.push_back(startIndex + 3);
	o_indices.push_back(startIndex + 6);

	o_indices.push_back(startIndex + 3);
	o_indices.push_back(startIndex + 5);

	o_indices.push_back(startIndex + 4);
	o_indices.push_back(startIndex + 7);

	o_indices.push_back(startIndex + 5);
	o_indices.push_back(startIndex + 7);

	o_indices.push_back(startIndex + 6);
	o_indices.push_back(startIndex + 7);
}

void createIndexedCube(
	std::vector<buw::VertexPosition3Normal3Texture2>& o_vertexBuffer, 
	std::vector<unsigned int>& o_indices/*,
	const float sizeX, const float sizeY, const float sizeZ*/)
{
	assert(o_vertexBuffer.size() == 0);
	BLUE_ASSERT(o_indices.size() == 0, "Output indices is expected to be zero");

	// VertexPositionNormalTexture
	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(0.5f,-0.5f,0.5f),	buw::Vector3f(0.408248f,-0.816497f,0.408248f),		buw::Vector2f(0,0) ));
	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(-0.5f,-0.5f,-0.5f),buw::Vector3f(-0.408248f,-0.816497f,-0.408248f),	buw::Vector2f(1,1) ));
	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(0.5f,-0.5f,-0.5f),	buw::Vector3f(0.666667f,-0.333333f,-0.666667f),	buw::Vector2f(0,1) ));
	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(-0.5f,-0.5f,0.5f),	buw::Vector3f(-0.666667f,-0.333333f,0.666667f),	buw::Vector2f(1,0) ));

	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(0.5f,0.5f,0.5f),	buw::Vector3f(0.666667f,0.333333f,0.666667f),		buw::Vector2f(0,0) ));
	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(-0.5f,-0.5f,0.5f),	buw::Vector3f(-0.666667f,-0.333333f,0.666667f),	buw::Vector2f(1,1) ));
	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(0.5f,-0.5f,0.5f),	buw::Vector3f(0.408248f,-0.816497f,0.408248f),		buw::Vector2f(0,1) ));
	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(-0.5f,0.5f,0.5f),	buw::Vector3f(-0.408248f,0.816497f,0.408248f),		buw::Vector2f(1,0) ));

	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(-0.5f,0.5f,-0.5f),	buw::Vector3f(-0.666667f,0.333333f,-0.666667f),	buw::Vector2f(1,1) ));
	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(-0.5f,-0.5f,-0.5f),	buw::Vector3f(-0.408248f,-0.816497f,-0.408248f),	buw::Vector2f(0,1) ));
	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(-0.5f,-0.5f,0.5f),	buw::Vector3f(-0.666667f,-0.333333f,0.666667f),	buw::Vector2f(0,0) ));
	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(0.5f,-0.5f,-0.5f),	buw::Vector3f(0.666667f,-0.333333f,-0.666667f),	buw::Vector2f(1,1) ));

	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(0.5f,0.5f,-0.5f),	buw::Vector3f(0.408248f,0.816497f,-0.408248f),		buw::Vector2f(0,1) ));
	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(0.5f,-0.5f,0.5f),	buw::Vector3f(0.408248f,-0.816497f,0.408248f),		buw::Vector2f(1,0) ));
	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(0.5f,-0.5f,-0.5f),	buw::Vector3f(0.666667f,-0.333333f,-0.666667f),	buw::Vector2f(0,0) ));
	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(-0.5f,-0.5f,-0.5f),buw::Vector3f(-0.408248f,-0.816497f,-0.408248f),	buw::Vector2f(1,0) ));

	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(-0.5f, 0.5f,  0.5f), buw::Vector3f(-0.408248f,0.816497f,0.408248f),	buw::Vector2f(1,1) ));
	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f( 0.5f, 0.5f, -0.5f), buw::Vector3f(0.408248f,0.816497f,-0.408248f),	buw::Vector2f(0,0) ));
	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f(-0.5f, 0.5f, -0.5f), buw::Vector3f(-0.666667f,0.333333f,-0.666667f),	buw::Vector2f(1,0) ));
	o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2( buw::Vector3f( 0.5f, 0.5f,  0.5f), buw::Vector3f(0.666667f,0.333333f,0.666667f),	buw::Vector2f(0,1) ));

    o_vertexBuffer.push_back(buw::VertexPosition3Normal3Texture2(buw::Vector3f(-0.5f, 0.5f, 0.5f), buw::Vector3f(-0.408248f, 0.816497f, 0.408248f), buw::Vector2f(1, 1)));
    o_vertexBuffer.push_back(buw::VertexPosition3Normal3Texture2(buw::Vector3f(0.5f, 0.5f, -0.5f), buw::Vector3f(0.408248f, 0.816497f, -0.408248f), buw::Vector2f(0, 0)));
    o_vertexBuffer.push_back(buw::VertexPosition3Normal3Texture2(buw::Vector3f(-0.5f, 0.5f, -0.5f), buw::Vector3f(-0.666667f, 0.333333f, -0.666667f), buw::Vector2f(1, 0)));
    o_vertexBuffer.push_back(buw::VertexPosition3Normal3Texture2(buw::Vector3f(0.5f, 0.5f, 0.5f), buw::Vector3f(0.666667f, 0.333333f, 0.666667f), buw::Vector2f(0, 1)));

	add_triangle(0,1,2);		
    add_triangle(3,1,0);
	add_triangle(4,5,6);		
    add_triangle(4,7,5);
	add_triangle(8,9,10);		
    add_triangle(10,7,8);
	add_triangle(4,11,12);		
    add_triangle(4,13,11);
	add_triangle(14,8,12);		
    add_triangle(14,15,8);
	add_triangle(16,17,18);		
    add_triangle(16,19,17);

	//return;

	// First try
	/*              y+
					^Top
					|  /Back
					| /
					|/
		Left --------+---------------> x+ Right
					/|
			Front / |
					z+ |
					|Bottom
	*/		

	//o_vertexBuffer.resize(24);

	// Location/Normals
	const int X_POS = 0;
	const int Y_POS = 1;
	const int Z_POS = 2;

	// Texture Coordinates
	const int U_POS = 0;
	const int V_POS = 1;

	// Colours
	//#define R_POS 0
	//#define G_POS 1
	//#define B_POS 2
	//#define A_POS 3

	// Top
	o_vertexBuffer[0].position[X_POS]	= 1;	o_vertexBuffer[0].position[Y_POS]	= 1;	o_vertexBuffer[0].position[Z_POS]	= -1;
	o_vertexBuffer[0].normal[X_POS]		= 0;	o_vertexBuffer[0].normal[Y_POS]		= 1;	o_vertexBuffer[0].normal[Z_POS]		= 0;
	o_vertexBuffer[0].uv[U_POS]			= 0;	o_vertexBuffer[0].uv[V_POS]			= 0; 

	o_vertexBuffer[1].position[X_POS]	= -1;	o_vertexBuffer[1].position[Y_POS]	= 1;	o_vertexBuffer[1].position[Z_POS]	= -1;
	o_vertexBuffer[1].normal[X_POS]		= 0;	o_vertexBuffer[1].normal[Y_POS]		= 1;	o_vertexBuffer[1].normal[Z_POS]		= 0;
	o_vertexBuffer[1].uv[U_POS]			= 0;	o_vertexBuffer[1].uv[V_POS]			= 1; 

	o_vertexBuffer[2].position[X_POS]	= -1;	o_vertexBuffer[2].position[Y_POS]	= 1;	o_vertexBuffer[2].position[Z_POS]	= 1;
	o_vertexBuffer[2].normal[X_POS]		= 0;	o_vertexBuffer[2].normal[Y_POS]		= 1;	o_vertexBuffer[2].normal[Z_POS]		= 0;
	o_vertexBuffer[2].uv[U_POS]			= 1;	o_vertexBuffer[2].uv[V_POS]			= 1; 

	o_vertexBuffer[3].position[X_POS]	= 1;	o_vertexBuffer[3].position[Y_POS]	= 1;	o_vertexBuffer[3].position[Z_POS]	= 1;
	o_vertexBuffer[3].normal[X_POS]		= 0;	o_vertexBuffer[3].normal[Y_POS]		= 1;	o_vertexBuffer[3].normal[Z_POS]		= 0;
	o_vertexBuffer[3].uv[U_POS]			= 1;	o_vertexBuffer[3].uv[V_POS]			= 0;

	// Bottom
	o_vertexBuffer[4].position[X_POS]	= 1;	o_vertexBuffer[4].position[Y_POS]	= -1;	o_vertexBuffer[4].position[Z_POS]	= 1;
	o_vertexBuffer[4].normal[X_POS]		= 0;	o_vertexBuffer[4].normal[Y_POS]		= -1;	o_vertexBuffer[4].normal[Z_POS]		= 0;
	o_vertexBuffer[4].uv[U_POS]			= 0;	o_vertexBuffer[4].uv[V_POS]			= 0; 

	o_vertexBuffer[5].position[X_POS]	= -1;	o_vertexBuffer[5].position[Y_POS]	= -1;	o_vertexBuffer[5].position[Z_POS]	= 1;
	o_vertexBuffer[5].normal[X_POS]		= 0;	o_vertexBuffer[5].normal[Y_POS]		= -1;	o_vertexBuffer[5].normal[Z_POS]		= 0;
	o_vertexBuffer[5].uv[U_POS]			= 0;	o_vertexBuffer[5].uv[V_POS]			= 1; 

	o_vertexBuffer[6].position[X_POS]	= -1;	o_vertexBuffer[6].position[Y_POS]	= -1;	o_vertexBuffer[6].position[Z_POS]	= -1;
	o_vertexBuffer[6].normal[X_POS]		= 0;	o_vertexBuffer[6].normal[Y_POS]		= -1;	o_vertexBuffer[6].normal[Z_POS]		= 0;
	o_vertexBuffer[6].uv[U_POS]			= 1;	o_vertexBuffer[6].uv[V_POS]			= 1; 

	o_vertexBuffer[7].position[X_POS]	= 1;	o_vertexBuffer[7].position[Y_POS]	= -1;	o_vertexBuffer[7].position[Z_POS]	= -1;
	o_vertexBuffer[7].normal[X_POS]		= 0;	o_vertexBuffer[7].normal[Y_POS]		= -1;	o_vertexBuffer[7].normal[Z_POS]		= 0;
	o_vertexBuffer[7].uv[U_POS]			= 1;	o_vertexBuffer[7].uv[V_POS]			= 0;

	// Front
	o_vertexBuffer[8].position[X_POS]	= 1;	o_vertexBuffer[8].position[Y_POS]	= 1;	o_vertexBuffer[8].position[Z_POS]	= 1;
	o_vertexBuffer[8].normal[X_POS]		= 0;	o_vertexBuffer[8].normal[Y_POS]		= 0;	o_vertexBuffer[8].normal[Z_POS]		= 1;
	o_vertexBuffer[8].uv[U_POS]			= 0;	o_vertexBuffer[8].uv[V_POS]			= 0; 

	o_vertexBuffer[9].position[X_POS]	= -1;	o_vertexBuffer[9].position[Y_POS]	= 1;	o_vertexBuffer[9].position[Z_POS]	= 1;
	o_vertexBuffer[9].normal[X_POS]		= 0;	o_vertexBuffer[9].normal[Y_POS]		= 0;	o_vertexBuffer[9].normal[Z_POS]		= 1;
	o_vertexBuffer[9].uv[U_POS]			= 0;	o_vertexBuffer[9].uv[V_POS]			= 1; 

	o_vertexBuffer[10].position[X_POS]	= -1;	o_vertexBuffer[10].position[Y_POS]	= -1;	o_vertexBuffer[10].position[Z_POS]	= 1;
	o_vertexBuffer[10].normal[X_POS]		= 0;	o_vertexBuffer[10].normal[Y_POS]		= 0;	o_vertexBuffer[10].normal[Z_POS]		= 1;
	o_vertexBuffer[10].uv[U_POS]		= 1;	o_vertexBuffer[10].uv[V_POS]		= 1; 

	o_vertexBuffer[11].position[X_POS]	= 1;	o_vertexBuffer[11].position[Y_POS]	= -1;	o_vertexBuffer[11].position[Z_POS]	= 1;
	o_vertexBuffer[11].normal[X_POS]		= 0;	o_vertexBuffer[11].normal[Y_POS]		= 0;	o_vertexBuffer[11].normal[Z_POS]		= 1;
	o_vertexBuffer[11].uv[U_POS]		= 1;	o_vertexBuffer[11].uv[V_POS]		= 0;

	// Back
	o_vertexBuffer[12].position[X_POS]	= 1;	o_vertexBuffer[12].position[Y_POS]	= -1;	o_vertexBuffer[12].position[Z_POS]	= -1;
	o_vertexBuffer[12].normal[X_POS]		= 0;	o_vertexBuffer[12].normal[Y_POS]		= 0;	o_vertexBuffer[12].normal[Z_POS]		= -1;
	o_vertexBuffer[12].uv[U_POS]		= 0;	o_vertexBuffer[12].uv[V_POS]		= 0; 

	o_vertexBuffer[13].position[X_POS]	= -1;	o_vertexBuffer[13].position[Y_POS]	= -1;	o_vertexBuffer[13].position[Z_POS]	= -1;
	o_vertexBuffer[13].normal[X_POS]		= 0;	o_vertexBuffer[13].normal[Y_POS]		= 0;	o_vertexBuffer[13].normal[Z_POS]		= -1;
	o_vertexBuffer[13].uv[U_POS]		= 0;	o_vertexBuffer[13].uv[V_POS]		= 1; 

	o_vertexBuffer[14].position[X_POS]	= -1;	o_vertexBuffer[14].position[Y_POS]	= 1;	o_vertexBuffer[14].position[Z_POS]	= -1;
	o_vertexBuffer[14].normal[X_POS]		= 0;	o_vertexBuffer[14].normal[Y_POS]		= 0;	o_vertexBuffer[14].normal[Z_POS]		= -1;
	o_vertexBuffer[14].uv[U_POS]		= 1;	o_vertexBuffer[14].uv[V_POS]		= 1; 

	o_vertexBuffer[15].position[X_POS]	= 1;	o_vertexBuffer[15].position[Y_POS]	= 1;	o_vertexBuffer[15].position[Z_POS]	= -1;
	o_vertexBuffer[15].normal[X_POS]		= 0;	o_vertexBuffer[15].normal[Y_POS]		= 0;	o_vertexBuffer[15].normal[Z_POS]		= -1;
	o_vertexBuffer[15].uv[U_POS]		= 1;	o_vertexBuffer[15].uv[V_POS]		= 0;

	// Left
	o_vertexBuffer[16].position[X_POS]	= -1;	o_vertexBuffer[16].position[Y_POS]	= 1;	o_vertexBuffer[16].position[Z_POS]	= 1;
	o_vertexBuffer[16].normal[X_POS]		= -1;	o_vertexBuffer[16].normal[Y_POS]		= 0;	o_vertexBuffer[16].normal[Z_POS]		= 0;
	o_vertexBuffer[16].uv[U_POS]		= 0;	o_vertexBuffer[16].uv[V_POS]		= 0; 

	o_vertexBuffer[17].position[X_POS]	= -1;	o_vertexBuffer[17].position[Y_POS]	= 1;	o_vertexBuffer[17].position[Z_POS]	= -1;
	o_vertexBuffer[17].normal[X_POS]		= -1;	o_vertexBuffer[17].normal[Y_POS]		= 0;	o_vertexBuffer[17].normal[Z_POS]		= 0;
	o_vertexBuffer[17].uv[U_POS]		= 0;	o_vertexBuffer[17].uv[V_POS]		= 1; 

	o_vertexBuffer[18].position[X_POS]	= -1;	o_vertexBuffer[18].position[Y_POS]	= -1;	o_vertexBuffer[18].position[Z_POS]	= -1;
	o_vertexBuffer[18].normal[X_POS]		= -1;	o_vertexBuffer[18].normal[Y_POS]		= 0;	o_vertexBuffer[18].normal[Z_POS]		= 0;
	o_vertexBuffer[18].uv[U_POS]		= 1;	o_vertexBuffer[18].uv[V_POS]		= 1; 

	o_vertexBuffer[19].position[X_POS]	= -1;	o_vertexBuffer[19].position[Y_POS]	= -1;	o_vertexBuffer[19].position[Z_POS]	= 1;
	o_vertexBuffer[19].normal[X_POS]		= -1;	o_vertexBuffer[19].normal[Y_POS]		= 0;	o_vertexBuffer[19].normal[Z_POS]		= 0;
	o_vertexBuffer[19].uv[U_POS]		= 1;	o_vertexBuffer[19].uv[V_POS]		= 0;

	// Right
	o_vertexBuffer[20].position[X_POS]	= 1;	o_vertexBuffer[20].position[Y_POS]	= 1;	o_vertexBuffer[20].position[Z_POS]	= -1;
	o_vertexBuffer[20].normal[X_POS]		= 1;	o_vertexBuffer[20].normal[Y_POS]		= 0;	o_vertexBuffer[20].normal[Z_POS]		= 0;
	o_vertexBuffer[20].uv[U_POS]		= 0;	o_vertexBuffer[20].uv[V_POS]		= 0; 

	o_vertexBuffer[21].position[X_POS]	= 1;	o_vertexBuffer[21].position[Y_POS]	= 1;	o_vertexBuffer[21].position[Z_POS]	= 1;
	o_vertexBuffer[21].normal[X_POS]		= 1;	o_vertexBuffer[21].normal[Y_POS]		= 0;	o_vertexBuffer[21].normal[Z_POS]		= 0;
	o_vertexBuffer[21].uv[U_POS]		= 0;	o_vertexBuffer[21].uv[V_POS]		= 1; 

	o_vertexBuffer[22].position[X_POS]	= 1;	o_vertexBuffer[22].position[Y_POS]	= -1;	o_vertexBuffer[22].position[Z_POS]	= 1;
	o_vertexBuffer[22].normal[X_POS]		= 1;	o_vertexBuffer[22].normal[Y_POS]		= 0;	o_vertexBuffer[22].normal[Z_POS]		= 0;
	o_vertexBuffer[22].uv[U_POS]		= 1;	o_vertexBuffer[22].uv[V_POS]		= 1; 

	o_vertexBuffer[23].position[X_POS]	= 1;	o_vertexBuffer[23].position[Y_POS]	= -1;	o_vertexBuffer[23].position[Z_POS]	= -1;
	o_vertexBuffer[23].normal[X_POS]		= 1;	o_vertexBuffer[23].normal[Y_POS]		= 0;	o_vertexBuffer[23].normal[Z_POS]		= 0;
	o_vertexBuffer[23].uv[U_POS]		= 1;	o_vertexBuffer[23].uv[V_POS]		= 0;

	//o_indices.resize(36);

	// Index Array (define our triangles)
	// A Face looks like (numbers are the array o_indices number of the vertex)
	// 1      2
	// +------+
	// |      |
	// |      |
	// +------+
	// 0      3
	o_indices[0] = 0;	o_indices[1] = 1;	o_indices[2] = 2;
	o_indices[3] = 2;	o_indices[4] = 3;	o_indices[5] = 0;

	o_indices[6] = 4;	o_indices[7] = 5;	o_indices[8] = 6;
	o_indices[9] = 6;	o_indices[10] = 7;	o_indices[11] = 4;

	o_indices[12] = 8;	o_indices[13] = 9;	o_indices[14] = 10; // Frontface
	o_indices[15] = 10;	o_indices[16] = 11;	o_indices[17] = 8;

	o_indices[18] = 12;	o_indices[19] = 13;	o_indices[20] = 14;
	o_indices[21] = 14;	o_indices[22] = 15;	o_indices[23] = 12;

	o_indices[24] = 16;	o_indices[25] = 17;	o_indices[26] = 18;
	o_indices[27] = 18;	o_indices[28] = 19;	o_indices[29] = 16;

	o_indices[30] = 20;	o_indices[31] = 21;	o_indices[32] = 22;
	o_indices[33] = 22;	o_indices[34] = 23;	o_indices[35] = 20;
}

void createIndexedSphere(
	const float radius,  const int widthSegments, const int heightSegments,
	std::vector<buw::VertexPosition3Normal3Texture2>& o_vertexBuffer, 
	std::vector<std::uint32_t>& o_indices )
{
	assert(o_vertexBuffer.size() == 0);
	assert(o_indices.size() == 0);

	// create vertices
	for (int latNumber = 0; latNumber <= heightSegments; latNumber++) {
		float theta = latNumber * buw::constants<float>::pi() / heightSegments;
		float sinTheta = sin(theta);
		float cosTheta = cos(theta);

		for (int longNumber = 0; longNumber <= widthSegments; longNumber++) 
		{
			auto phi = longNumber * 2 * buw::constants<float>::pi() / widthSegments;
			auto sinPhi = sin(phi);
			auto cosPhi = cos(phi);

			auto x = cosPhi * sinTheta;
			auto y = cosTheta;
			auto z = sinPhi * sinTheta;
			auto u = 1 - (static_cast<float>(longNumber) / widthSegments);
			auto v = 1 - (static_cast<float>(latNumber) / heightSegments);

			o_vertexBuffer.push_back( buw::VertexPosition3Normal3Texture2(
				buw::Vector3f(radius * x, radius * y, radius * z ), 
				buw::Vector3f(x,y,z).normalized(), 
				buw::Vector2f(u, v)));
		}
	}

	// create indices
	for (int latNumber = 0; latNumber < heightSegments; latNumber++) 
	{
		for (int longNumber = 0; longNumber < widthSegments; longNumber++)
		{
			int first = (latNumber * (widthSegments + 1)) + longNumber;
			int second = first + widthSegments + 1;

			bool ccw = true;

			if (ccw)
			{
				o_indices.push_back(first);
				o_indices.push_back(first + 1);
				o_indices.push_back(second);
							
				o_indices.push_back(second);
				o_indices.push_back(first + 1);
				o_indices.push_back(second + 1);
			}
			else
			{
				o_indices.push_back(first);
				o_indices.push_back(second);
				o_indices.push_back(first + 1);

				o_indices.push_back(second);
				o_indices.push_back(second + 1);
				o_indices.push_back(first + 1);
			}
		}
	}
}

void createGrid(
	int gridLength, 
	int gridStartX, 
	int gridStartY, 
	int stepSize,
	std::vector<buw::VertexPosition3Normal3Texture2>& o_vertexBuffer)
{
	int numberOfVertices	= (gridLength - 1) * (gridLength - 1) * 2 * 3;

	buw::Vector4f* positions	= new buw::Vector4f[numberOfVertices];
	buw::Vector4f* colors		= new buw::Vector4f[numberOfVertices];
	buw::Vector2f* texCoords	= new buw::Vector2f[numberOfVertices];

	//int positionSize = numberOfVertices * sizeof(positions[0]);
	//int colorSize	= numberOfVertices * sizeof(colors[0]);
	//int texCoordSize	= numberOfVertices * sizeof(texCoords[0]);

	int counter = 0;
	for(int i=0; i < (gridLength - 1); i++)
	{
		for(int j=0; j < (gridLength - 1); j++)
		{
			positions[counter]	= buw::Vector4f( 
				gridStartX + j + (j*(stepSize-1.0f)), 
				gridStartY - i - (i*(stepSize-1.0f)), 
				0.0f, 
				1.0f);
			colors[counter]		= buw::Vector4f( 1.0f, 1.0f, 1.0f, 1.0f);
			texCoords[counter]	= buw::Vector2f( 
				0.0f + (j * (1.0f / ((float)gridLength  - 1.0f))), 
				1.0f - (i * (1.0f / ((float)gridLength - 1.0f))));
			counter++;

			positions[counter]	= buw::Vector4f( 
				gridStartX + j + stepSize + (j*(stepSize-1.0f)), 
				gridStartY - i - (i*(stepSize-1.0f)), 
				0.0f, 
				1.0f);
			colors[counter]		= buw::Vector4f( 1.0f, 1.0f, 1.0f, 1.0f);
			texCoords[counter]	= buw::Vector2f( 
				0.0f + ((j + 1.0f) * (1.0f / ((float)gridLength  - 1.0f))), 
				1.0f - (i * (1.0f / ((float)gridLength - 1.0f))));
			counter++;

			positions[counter]	= buw::Vector4f( 
				gridStartX + j + (j*(stepSize-1.0f)), 
				gridStartY - stepSize - i - (i*(stepSize-1.0f)), 
				0.0f, 
				1.0f);
			colors[counter]		= buw::Vector4f( 1.0f, 1.0f, 1.0f, 1.0f);
			texCoords[counter]	= buw::Vector2f( 
				0.0f + (j * (1.0f / ((float)gridLength  - 1.0f))), 
				1.0f - ((i + 1) * (1.0f / ((float)gridLength - 1.0f))));
			counter++;

			positions[counter]	= buw::Vector4f( 
				gridStartX + j + stepSize + (j*(stepSize-1.0f)), 
				gridStartY - i - (i*(stepSize-1.0f)), 0.0f, 1.0f);
			colors[counter]		= buw::Vector4f( 1.0f, 1.0f, 1.0f, 1.0f);
			texCoords[counter]	= buw::Vector2f( 
				0.0f + ((j + 1.0f) * (1.0f / ((float)gridLength  - 1.0f))), 
				1.0f - (i * (1.0f / ((float)gridLength - 1.0f))));
			counter++;

			positions[counter]	= buw::Vector4f( 
				gridStartX + j + stepSize + (j*(stepSize-1.0f)), 
				gridStartY - stepSize - i - (i*(stepSize-1.0f)), 
				0.0f, 
				1.0f);
			colors[counter]		= buw::Vector4f( 1.0f, 1.0f, 1.0f, 1.0f);
			texCoords[counter]	= buw::Vector2f( 
				0.0f + ((j + 1.0f) * (1.0f / ((float)gridLength  - 1.0f))), 
				1.0f - ((i + 1) * (1.0f / ((float)gridLength - 1.0f))));
			counter++;

			positions[counter]	= buw::Vector4f( 
				gridStartX + j + (j*(stepSize-1.0f)), 
				gridStartY - stepSize - i - (i*(stepSize-1.0f)), 
				0.0f, 
				1.0f);
			colors[counter]		= buw::Vector4f( 1.0f, 1.0f, 1.0f, 1.0f);
			texCoords[counter]	= buw::Vector2f( 
				0.0f + (j * (1.0f / ((float)gridLength  - 1.0f))), 
				1.0f - ((i + 1) * (1.0f / ((float)gridLength - 1.0f))));
			counter++;
		}
	}

	for (int i = 0; i < counter; i++)
	{
		buw::VertexPosition3Normal3Texture2 v;
		v.position = buw::Vector3f(positions[i].x(), positions[i].y(), positions[i].z());
		v.normal = buw::Vector3f(0,1,0);
		v.uv = texCoords[i];
		o_vertexBuffer.push_back(v);
	}
				
	delete [] positions;
	delete [] colors;
	delete [] texCoords;

	positions	= nullptr;
	colors		= nullptr; 
	texCoords	= nullptr; 
} // end function createGrid

BLUEFRAMEWORK_ENGINE_NAMESPACE_END

