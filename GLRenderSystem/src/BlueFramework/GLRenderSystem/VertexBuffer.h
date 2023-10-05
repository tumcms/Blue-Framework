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
