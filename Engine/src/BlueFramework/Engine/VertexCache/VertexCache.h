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
#ifndef BlueFramework_Engine_VertexCache_04a16cbc_cdb8_4b63_b9d3_592dbf1ccf24_h
#define BlueFramework_Engine_VertexCache_04a16cbc_cdb8_4b63_b9d3_592dbf1ccf24_h

#include "BlueFramework/Engine/namespace.h"
#include "BlueFramework/Rasterizer/IRenderSystem.h"
#include "BlueFramework/Rasterizer/Resources/IVertexBuffer.h"

BLUEFRAMEWORK_ENGINE_NAMESPACE_BEGIN

class VertexCache {
public:
	VertexCache(buw::IRenderSystem* renderSystem, const buw::ePrimitiveTopology& topology, const buw::VertexLayout& vertexLayout, const int maxVertices = 10000)
	    : renderSystem_(renderSystem), topology_(topology), vertexLayout_(vertexLayout), maxSize_(maxVertices), size_(0) {
	}

	virtual buw::ePrimitiveTopology topology() const {
		return topology_;
	}
	virtual const buw::VertexLayout& vertexLayout() const {
		return vertexLayout_;
	};
	buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer() const {
		return vertexBuffer_;
	}

	unsigned int getSize() const {
		return size_;
	}
	unsigned int getMaxSize() const {
		return maxSize_;
	}

	virtual void flush() = 0;

protected:
	buw::ePrimitiveTopology topology_;
	buw::VertexLayout vertexLayout_;
	buw::IRenderSystem* renderSystem_;
	buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer_;

	unsigned int size_, maxSize_;
};

template <typename T>
class VertexCachePointT : public VertexCache {
	typedef T VertexType;
public:
	VertexCachePointT(buw::IRenderSystem* renderSystem, const int maxVertices = 10000)
		: VertexCache(renderSystem, buw::ePrimitiveTopology::PointList, VertexType::getVertexLayout(), maxVertices) {
		dirty_ = true;

		vertices_.resize(maxSize_);

		buw::vertexBufferDescription vbd;
		vbd.data = &vertices_[0];
		vbd.vertexCount = maxSize_;
		vbd.vertexLayout = vertexLayout_;
		vertexBuffer_ = renderSystem_->createVertexBuffer(vbd);
	}
	virtual ~VertexCachePointT() {
	}

	void clear() {
		dirty_ = true;
		size_ = 0;
	}

	void drawPoint(const VertexType& v1) {
		BLUE_ASSERT(maxSize_ > size_, "Vertex buffer too small.");

		dirty_ = true;

		vertices_[size_++] = v1;
	}

	void flush() {
		if (dirty_ && size_ > 0) {
			buw::vertexBufferDescription vbd;
			vbd.data = &vertices_[0];
			vbd.vertexCount = size_;
			vbd.vertexLayout = vertexLayout_;
			vertexBuffer_->uploadData(vbd);
		}
		dirty_ = false;
	}

public:
	bool dirty_;
	std::vector<VertexType> vertices_;
};

template <typename T>
class VertexCacheLineT : public VertexCache {
	typedef T VertexType;

public:
	VertexCacheLineT(buw::IRenderSystem* renderSystem, const int maxVertices = 10000)
	    : VertexCache(renderSystem, buw::ePrimitiveTopology::LineList, VertexType::getVertexLayout(), maxVertices) {
		renderSystem_ = renderSystem;

		dirty_ = true;

		vertices_.resize(maxSize_);

		buw::vertexBufferDescription vbd;
		vbd.data = &vertices_[0];
		vbd.vertexCount = maxSize_;
		vbd.vertexLayout = vertexLayout_;
		vertexBuffer_ = renderSystem_->createVertexBuffer(vbd);
	}

	virtual ~VertexCacheLineT() {
	}

	void clear() {
		dirty_ = true;
		size_ = 0;
	}

	void drawLine(const VertexType& v1, const VertexType& v2) {
		BLUE_ASSERT(maxSize_ > size_ + 3, "Vertex buffer too small.");

		dirty_ = true;

		vertices_[size_++] = v1;
		vertices_[size_++] = v2;
	}

	void flush() {
		if (dirty_ && size_ > 0) {
			buw::vertexBufferDescription vbd;
			vbd.data = &vertices_[0];
			vbd.vertexCount = size_;
			vbd.vertexLayout = vertexLayout_;
			vertexBuffer_->uploadData(vbd);
		}
		dirty_ = false;
	}

public:
	bool dirty_;
	std::vector<VertexType> vertices_;
};

template <typename T>
class VertexCacheTriangleT : public VertexCache {
	typedef T VertexType;

public:
	VertexCacheTriangleT(buw::IRenderSystem* renderSystem, const int maxVertices = 10000)
	    : VertexCache(renderSystem, buw::ePrimitiveTopology::TriangleList, VertexType::getVertexLayout(), maxVertices) {
		dirty_ = true;

		vertices_.resize(maxSize_);

		buw::vertexBufferDescription vbd;
		vbd.data = &vertices_[0];
		vbd.vertexCount = maxSize_;
		vbd.vertexLayout = vertexLayout_;
		vertexBuffer_ = renderSystem_->createVertexBuffer(vbd);
	}

	virtual ~VertexCacheTriangleT() {
	}

	void clear() {
		dirty_ = true;
		size_ = 0;
	}

	void drawTriangle(const VertexType& v1, const VertexType& v2, const VertexType& v3) {
		BLUE_ASSERT(maxSize_ > size_ + 3, "Vertex buffer too small.");

		dirty_ = true;

		vertices_[size_++] = v1;
		vertices_[size_++] = v2;
		vertices_[size_++] = v3;
	}

	void flush() {
		if (dirty_ && size_ > 0) {
			buw::vertexBufferDescription vbd;
			vbd.data = &vertices_[0];
			vbd.vertexCount = size_;
			vbd.vertexLayout = vertexLayout_;
			vertexBuffer_->uploadData(vbd);
		}
		dirty_ = false;
	}

public:
	bool dirty_;
	std::vector<VertexType> vertices_;
};

BLUEFRAMEWORK_ENGINE_NAMESPACE_END

namespace buw {
	typedef BlueFramework::Engine::VertexCache VertexCache;	
	template <typename T>
	using VertexCachePointT = BlueFramework::Engine::VertexCachePointT<T>;
	template <typename T>
	using VertexCacheLineT = BlueFramework::Engine::VertexCacheLineT<T>;
	template <typename T>
	using VertexCacheTriangleT = BlueFramework::Engine::VertexCacheTriangleT<T>;

}

#endif // end define BlueFramework_Rasterizer_VertexCacheTriangle_acedfe91_d6de_4232_9e2e_540cb9e4295e_h
