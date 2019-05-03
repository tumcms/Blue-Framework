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

#include <GL/glew.h> // !! GLEW always first !!

#include <BlueFramework/GLRenderSystem/VertexBuffer.h>
#include <BlueFramework/GLRenderSystem/namespace.h>
#include <BlueFramework/GLRenderSystem/RenderSystem.h>
#include <BlueFramework/GLRenderSystem/PipelineState.h>

#include <BlueFramework/Core/Exception.h>
#include <BlueFramework/Rasterizer/VertexLayout.h>
#include <BlueFramework/Core/assert.h>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

std::weak_ptr<VertexBuffer> VertexBuffer::_active;

VertexBuffer::VertexBuffer(RenderSystem* rs, buw::vertexBufferDescription const& vbd)
	: buw::IVertexBuffer(rs, vbd)
	, std::enable_shared_from_this<VertexBuffer>()
	, _vao(0)
	, _vbo(0)
	, _numVertices(0)
	, _bytesPerVertex(0)
{
	// Create VAO and VBO.
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	BLUE_ASSERT(glGetError() == GL_NO_ERROR);

	if (vbd.data) uploadData(vbd);
}

VertexBuffer::~VertexBuffer()
{
	if (_active.lock().get() == this) _active.reset(); // Actually not needed because we use a weak pointer.
	GLint currentVAO = 0;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO);
	if ((GLuint)currentVAO == _vao) glBindVertexArray(0);
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	BLUE_ASSERT(glGetError() == GL_NO_ERROR);
}

size_t VertexBuffer::getVertexCount() const
{
	return _numVertices;
}

size_t VertexBuffer::getVertexSize() const
{
	return _bytesPerVertex;
}

void VertexBuffer::uploadData(buw::vertexBufferDescription const& vbd)
{
	buw::VertexLayout const& vl = vbd.vertexLayout;
	if (vbd.data == nullptr || vbd.vertexCount == 0 || vl.componentCount() == 0)
		throw buw::Exception("Empty data.");
	_numVertices = vbd.vertexCount;
	_bytesPerVertex = vl.getVertexByteSize();

	// Data is interleaved. Create a single VBO for all data components
	// and copy the vertex attribute data to it.
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _numVertices * _bytesPerVertex, vbd.data, GL_STATIC_DRAW);

	// Disable all possibly enabled vertex attribute arrays.
	GLint vaoRestore = 0;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vaoRestore);
	glBindVertexArray(_vao);
	GLint maxVA = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVA);
	for (GLuint va = 0; va < (GLuint)maxVA; ++va)
		glDisableVertexAttribArray(va);

	// Make associations between vertex attribute indices and the VBO.
	size_t offset = 0;
	for (size_t vAttrIndex = 0; vAttrIndex < vl.componentCount(); ++vAttrIndex)
	{
		buw::VertexAttribute const& va = vl.componentAt(vAttrIndex);

		// Set the VBO into the VAO.
		glEnableVertexAttribArray((GLuint)vAttrIndex);
		GLint const nNumComponents =
			(((int)va.format & (int)buw::eVertexAttributeFormat::_1Components) != 0) * 1 +
			(((int)va.format & (int)buw::eVertexAttributeFormat::_2Components) != 0) * 2 +
			(((int)va.format & (int)buw::eVertexAttributeFormat::_3Components) != 0) * 3 +
			(((int)va.format & (int)buw::eVertexAttributeFormat::_4Components) != 0) * 4;
		if (nNumComponents == 0) throw buw::Exception("Incompatible number of vertex components.");
		bool const bFloatType = ((int)va.format & (int)buw::eVertexAttributeFormat::FloatType) != 0;
		bool const bByteType = ((int)va.format & (int)buw::eVertexAttributeFormat::ByteType) != 0;
		bool const bShortType = ((int)va.format & (int)buw::eVertexAttributeFormat::ShortType) != 0;
		bool const bIntType = ((int)va.format & (int)buw::eVertexAttributeFormat::IntType) != 0;
		bool const bSignedType = ((int)va.format & (int)buw::eVertexAttributeFormat::SignedType) != 0;
		bool const bNormalizeType = ((int)va.format & (int)buw::eVertexAttributeFormat::NormalizeType) != 0;
		GLenum const eGLType =
			bFloatType * GL_FLOAT +
			(bByteType && bSignedType) * GL_BYTE +
			(bByteType && !bSignedType) * GL_UNSIGNED_BYTE +
			(bShortType && bSignedType) * GL_SHORT +
			(bShortType && !bSignedType) * GL_UNSIGNED_SHORT +
			(bIntType && bSignedType) * GL_INT +
			(bIntType && !bSignedType) * GL_UNSIGNED_INT;
		if (eGLType == 0) throw buw::Exception("Incompatible vertex attribute type.");
		if (bFloatType || bNormalizeType)
			glVertexAttribPointer((GLuint)vAttrIndex, nNumComponents, eGLType, bFloatType ? GL_FALSE : bNormalizeType, (GLsizei)_bytesPerVertex, reinterpret_cast<void*>(offset));
		else
			glVertexAttribIPointer((GLuint)vAttrIndex, nNumComponents, eGLType, (GLsizei)_bytesPerVertex, reinterpret_cast<void*>(offset));

		offset += va.ByteSize();
		BLUE_ASSERT(glGetError() == GL_NO_ERROR);
	}

	// Cleanup.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(vaoRestore);
	BLUE_ASSERT(glGetError() == GL_NO_ERROR);
}

void VertexBuffer::setActive()
{
	if (_active.lock().get() == this) return;
	glBindVertexArray(_vao);
	_active = shared_from_this();
}

buw::ReferenceCounted<VertexBuffer> VertexBuffer::getActive()
{
	return _active.lock();
}

void VertexBuffer::draw(unsigned int const numVertices)
{
	setActive();

	GLenum ePrimitiveType = GL_TRIANGLES;
	buw::ReferenceCounted<PipelineState> ps = PipelineState::getActive();
	if (ps) ePrimitiveType = ps->getPrimitiveType();

	glDrawArrays(ePrimitiveType, 0, numVertices);
}

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END
