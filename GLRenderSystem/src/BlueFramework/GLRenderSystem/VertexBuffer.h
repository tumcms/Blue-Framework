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

#ifndef __VERTEXBUFFER_H_CC654FA4D1D848F48D3464088ED6496C__
#define __VERTEXBUFFER_H_CC654FA4D1D848F48D3464088ED6496C__

#include <GL/glew.h> // !! GLEW always first !!

#include <BlueFramework/GLRenderSystem/namespace.h>

#include <BlueFramework/Rasterizer/Resources/IVertexBuffer.h>
#include <BlueFramework/Core/memory.h>

#include <vector>
#include <memory>

namespace buw
{
	struct vertexBufferDescription;
}

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

class RenderSystem;

class VertexBuffer : public buw::IVertexBuffer, public std::enable_shared_from_this<VertexBuffer>
{
public:
	explicit VertexBuffer(RenderSystem* rs, buw::vertexBufferDescription const& vbd);
	virtual ~VertexBuffer();

	size_t getVertexCount() const override;
	size_t getVertexSize() const override;
	void uploadData(buw::vertexBufferDescription const& vbd) override;
	void setActive();
	static buw::ReferenceCounted<VertexBuffer> getActive();
	void draw(unsigned int const numVertices);

private:
	static std::weak_ptr<VertexBuffer> _active;
	GLuint _vao;
	GLuint _vbo;
	size_t _numVertices;
	size_t _bytesPerVertex;
};

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END

#endif // __VERTEXBUFFER_H_CC654FA4D1D848F48D3464088ED6496C__
