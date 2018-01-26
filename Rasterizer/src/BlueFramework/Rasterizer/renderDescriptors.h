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

#pragma once
#ifndef BlueFramework_Rasterizer_renderDescriptors_e34da666_d358_48f3_a1fa_e7a4caa91140_h
#define BlueFramework_Rasterizer_renderDescriptors_e34da666_d358_48f3_a1fa_e7a4caa91140_h

#include "BlueFramework/Rasterizer/VertexLayout.h"
#include "BlueFramework/Rasterizer/namespace.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

class IVertexBuffer;
class IIndexBuffer;

enum class eRenderAPI { Direct3D12, Direct3D11, Vulkan, OpenGL };

struct renderSystemDescription {
	renderSystemDescription() {
	}

	int width = 1;
	int height = 1;
	void* windowId = nullptr;
	bool enableMSAA = false;
	bool forceWarpDevice = false;
	eRenderAPI renderAPI = eRenderAPI::Direct3D12;
};

struct multiSamplingDescription {
	int count;
	int quality;
};

struct vertexBufferDescription {
	buw::VertexLayout vertexLayout;
	unsigned int vertexCount;
	//unsigned int vertexStrideInBytes; // FIXME: used nowhere. remove?
	void *data;
};

enum class eIndexBufferFormat { UnsignedInt16, UnsignedInt32 };

struct indexBufferDescription {
	int indexCount;
	eIndexBufferFormat format;
	void *data;

	/* template <typename T>
	 indexBufferDescription(std::vector<T> &indices):
	     indexCount(indices.size()),
	     format(eIndexBufferFormat::UnsignedInt32),
	     data(&indices[0])
	 {
	 }*/

	size_t getElementByteSize() const {
		switch (format) {
		case eIndexBufferFormat::UnsignedInt16: return 2;
		case eIndexBufferFormat::UnsignedInt32: return 4;
		default: throw buw::Exception("Unknown element size");
		}
	}; // TODO: Add additional formats.
};

enum class eFilter : int { None = 0, Point = 1, Linear = 2, Anisotropic = 3 };

enum class eTextureAddressMode : int {
	Wrap = 0,
	Clamp = 1,
	Mirror = 2,
	Border = 3,
	MirrorOnce = 4,
};

enum class eComparisonFunction : int {
	Never = 0,
	Less = 1,
	Equal = 2,
	LessEqual = 3,
	Greater = 4,
	NotEqual = 5,
	GreaterEqual = 6,
	Always = 7,
};

enum class eCullMode { CullCounterClockWiseFaces, CullClockWiseFaces, None };

enum class eFillMode { Solid, Wireframe };

struct samplerStateDescription {
	samplerStateDescription() {
		minificationFilter = magnificationFilter = mipLevelFilter = eFilter::Linear;
		compFunction = eComparisonFunction::Always;
		textureAddressModeU = textureAddressModeV = textureAddressModeW = eTextureAddressMode::Wrap;
	}

	samplerStateDescription(eFilter filter) {
		minificationFilter = magnificationFilter = mipLevelFilter = filter;
		compFunction = eComparisonFunction::Always;
		textureAddressModeU = textureAddressModeV = textureAddressModeW = eTextureAddressMode::Wrap;
	}

	eFilter minificationFilter;
	eFilter magnificationFilter;
	eFilter mipLevelFilter;
	eComparisonFunction compFunction;

	eTextureAddressMode textureAddressModeU;
	eTextureAddressMode textureAddressModeV;
	eTextureAddressMode textureAddressModeW;
};

enum class eBlendValue {
	Unknown = 0,
	Zero = 1,
	One = 2,
	SrcColor = 3,
	InvSrcColor = 4,
	SrcAlpha = 5,
	InvSrcAlpha = 6,
	DestAlpha = 7,
	InvDestAlpha = 8,
	DestColor = 9,
	InvDestColor = 10,
	SrcAlphaSat = 11,
	BlendFactor = 14,
	InvBlendFactor = 15,
	Src1Color = 16,
	InvSrc1Color = 17,
	Src1Alpha = 18,
	InvSrc1Alpha = 19
};

enum class eBlendOperation { Add = 1, Sub = 2, RevSub = 3, Min = 4, Max = 5 };

enum class eLogicOperation {
	Clear = 0,
	Set = 1,
	Copy = 2,
	CopyInv = 3,
	NoOp = 4,
	Invert = 5,
	And = 6,
	Nand = 7,
	Or = 8,
	Nor = 9,
	Xor = 10,
	Equiv = 11,
	AndRev = 12,
	AndInv = 13,
	OrRev = 14,
	OrInv = 15
};

struct renderTargetBlendDescription {
	renderTargetBlendDescription() {
		blendEnable = false;
		logicOpEnable = false;
		srcBlend = eBlendValue::One;
		destBlend = eBlendValue::Zero;
		blendOp = eBlendOperation::Add;
		srcBlendAlpha = eBlendValue::One;
		destBlendAlpha = eBlendValue::Zero;
		blendOpAlpha = eBlendOperation::Add;
		renderTargetWriteMask = 0x0F;
	}
	bool blendEnable, logicOpEnable;
	eBlendValue srcBlend, destBlend, srcBlendAlpha, destBlendAlpha;
	eBlendOperation blendOp, blendOpAlpha;
	eLogicOperation logicOp;
	UINT8 renderTargetWriteMask;
};

struct blendStateDescription {
	blendStateDescription() {
		alphaToCoverageEnable = false;
		independentBlendEnable = false;
		renderTarget[0] = {};
	}
	bool alphaToCoverageEnable, independentBlendEnable;
	renderTargetBlendDescription renderTarget[8];
};

enum class eTextureFormat { R8G8B8A8_UnsignedNormalizedInt_SRGB, D24_UnsignedNormalizedInt_S8_UnsignedInt, R32_UnsignedInt, Undefined };

struct texture1DDescription {
	/// width of top-level mipmap in pixels
	int width = 0;

	eTextureFormat format;

	const void* data;

	bool isCpuReadable = false;

	bool useMSAA = false;	
};

struct texture2DDescription {
	/// width of top-level mipmap in pixels
	int width = 0;
	/// height of top-level mipmap in pixels
	int height = 0;

	eTextureFormat format;

	const void* data;

	bool isCpuReadable = false;
	bool isCpuWriteable = false;

	bool useMSAA = false;	
};

struct textureCubeDescription {
	/// width of top-level mipmap in pixels
	int width = 0;
	/// height of top-level mipmap in pixels
	int height = 0;

	eTextureFormat format;

	const void** data;

	bool isCpuReadable = false;

	bool useMSAA = false;
};

enum class eTextureBindType { None, SRV, RTV, DSV, SRV_RTV, SRV_DSV };

enum class ePrimitiveTopology : int { Undefined = 0, PointList = 1, LineList = 2, LineStrip = 3, TriangleList = 4, TriangleStrip = 5 };

struct drawCommand {
	drawCommand() {
		primitiveTopology = ePrimitiveTopology::TriangleList;
		vb = nullptr;
		vertexCountPerInstance = 0;
		instanceCount = 1;
		startVertexLocation = 0;
		startInstanceLocation = 0;
	}

	ePrimitiveTopology primitiveTopology;
	IVertexBuffer *vb;
	unsigned int vertexCountPerInstance;
	unsigned int instanceCount;
	unsigned int startVertexLocation;
	unsigned int startInstanceLocation;
};

struct drawIndexedCommand {
	drawIndexedCommand() {
		primitiveTopology = ePrimitiveTopology::TriangleList;
		vb = nullptr;
		ib = nullptr;
		indexCountPerInstance = 0;
		instanceCount = 1;
		startInstanceLocation = 0;
		baseVertexLocation = 0;
		startInstanceLocation = 0;
	}

	ePrimitiveTopology primitiveTopology;
	IVertexBuffer *vb;
	IIndexBuffer *ib;
	unsigned int indexCountPerInstance;
	unsigned int instanceCount;
	unsigned int startIndexLocation;
	int baseVertexLocation;
	unsigned int startInstanceLocation;
};

struct constantBufferDescription {
	unsigned int sizeInBytes;
	void *data;
};

struct depthStencilBufferDescription {
	int width;
	int height;
};

struct viewportDescription {
	viewportDescription() : width(0), height(0), left(0), top(0), minDepth(0), maxDepth(0) {
	}
	viewportDescription(const UINT width, const UINT height, const UINT left = 0, const UINT top = 0, const UINT minDepth = 0, const UINT maxDepth = 1)
	    : width(width), height(height), left(left), top(top), minDepth(minDepth), maxDepth(maxDepth) {
	}

	UINT width, height;
	UINT left, top;
	UINT minDepth, maxDepth;
};

struct pipelineStateDescription {
	pipelineStateDescription() {
	}

	pipelineStateDescription(const std::string &effectFilename,
							 const std::string &pipelineStateName,
	                         const VertexLayout &vertexLayout,
	                         ePrimitiveTopology primitiveTopology,
	                         const std::vector<eTextureFormat> &renderTargetFormats,
	                         bool useDepth,
							 bool useAdjacency)
	    : effectFilename(effectFilename)
		, pipelineStateName(pipelineStateName)
	    , vertexLayout(vertexLayout)
	    , primitiveTopology(primitiveTopology)
	    , renderTargetFormats(renderTargetFormats)
	    , useDepth(useDepth)
		, useAdjacency(useAdjacency){
	}

	std::string effectFilename;
	std::string pipelineStateName;
	VertexLayout vertexLayout;
	ePrimitiveTopology primitiveTopology = ePrimitiveTopology::TriangleList;
	std::vector<eTextureFormat> renderTargetFormats;
	bool useDepth = false;
	bool useMSAA = false;
	bool useAdjacency = false;
	eCullMode cullMode = eCullMode::None;
	eFillMode fillMode = eFillMode::Solid;
	eComparisonFunction depthComparisonFunction = eComparisonFunction::Less;
	blendStateDescription blendStateDesc;
};

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END

BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(blendStateDescription)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(constantBufferDescription)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(depthStencilBufferDescription)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(drawCommand)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(drawIndexedCommand)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(eBlendOperation)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(eBlendValue)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(eComparisonFunction)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(eCullMode)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(eFillMode)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(eFilter)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(eIndexBufferFormat)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(eLogicOperation)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(ePrimitiveTopology)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(eRenderAPI)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(eTextureAddressMode)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(eTextureBindType)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(eTextureFormat)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(indexBufferDescription)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(pipelineStateDescription)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(renderSystemDescription)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(renderTargetBlendDescription)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(samplerStateDescription)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(texture1DDescription)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(texture2DDescription)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(textureCubeDescription)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(vertexBufferDescription)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(viewportDescription)

#endif // end define BlueFramework_Rasterizer_renderDescriptors_e34da666_d358_48f3_a1fa_e7a4caa91140_h
