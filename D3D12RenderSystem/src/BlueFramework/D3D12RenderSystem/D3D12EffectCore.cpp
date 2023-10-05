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

#pragma comment (lib, "dxguid.lib")

#include "BlueFramework/D3D12RenderSystem/D3D12EffectCore.h"
#include "BlueFramework/D3D12RenderSystem/D3D12RenderSystem.h"
#include <fstream>
//#include <filesystem>
#include <boost/filesystem.hpp>

#include <tinyxml2.h>

#ifdef min
#undef min
#endif // min

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

HRESULT compileShader(const std::string& filename,
                      const std::string& shadermodel,
                      const std::string& entry,
                      ID3DBlob** compiledShader,
                      ID3D12ShaderReflection** reflection);

DXGI_FORMAT getD3D12VertexFormat(const buw::eVertexAttributeFormat format) {
	switch (format) {
	case buw::eVertexAttributeFormat::Float: return DXGI_FORMAT_R32_FLOAT;
	case buw::eVertexAttributeFormat::Float2: return DXGI_FORMAT_R32G32_FLOAT;
	case buw::eVertexAttributeFormat::Float3: return DXGI_FORMAT_R32G32B32_FLOAT;
	case buw::eVertexAttributeFormat::Float4: return DXGI_FORMAT_R32G32B32A32_FLOAT;
	case buw::eVertexAttributeFormat::Int: return DXGI_FORMAT_R32_SINT;
    case buw::eVertexAttributeFormat::UInt: return DXGI_FORMAT_R32_UINT;
    case buw::eVertexAttributeFormat::UInt3: return DXGI_FORMAT_R32G32B32_UINT;
	default: BLUE_LOG(error) << "Unknown vertex attribute format."; throw buw::Exception("Unknown vertex attribute format.");
	};
}

D3D12_COMPARISON_FUNC getD3D12ComparisonFunction(const buw::eComparisonFunction depthComparisonFunction) {
	switch (depthComparisonFunction) {
	case buw::eComparisonFunction::Never: break;
	case buw::eComparisonFunction::Less: return D3D12_COMPARISON_FUNC_LESS;
	case buw::eComparisonFunction::Equal: break;
	case buw::eComparisonFunction::LessEqual: return D3D12_COMPARISON_FUNC_LESS_EQUAL;
	case buw::eComparisonFunction::Greater: break;
	case buw::eComparisonFunction::NotEqual: break;
	case buw::eComparisonFunction::GreaterEqual: break;
	case buw::eComparisonFunction::Always: break;
	default: break;
	}
	return D3D12_COMPARISON_FUNC_NEVER;
}

std::vector<D3D12_INPUT_ELEMENT_DESC> getD3D12InputLayoutDesc(const buw::VertexLayout& vl) {
	std::vector<D3D12_INPUT_ELEMENT_DESC> result;

	UINT alignedByteOffset = 0;

	for (int i = 0; i < vl.componentCount(); i++) {
		D3D12_INPUT_ELEMENT_DESC desc;
		const char* semanticName = buw::toString(vl.componentAt(i).semantic);
		desc.SemanticName = semanticName;
		desc.SemanticIndex = vl.componentAt(i).semanticIndex;
		desc.Format = getD3D12VertexFormat(vl.componentAt(i).format);
		desc.InputSlot = 0;
		desc.AlignedByteOffset = alignedByteOffset;
		alignedByteOffset += vl.componentAt(i).ByteSize();
		desc.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;

		result.push_back(desc);
	}

	return result;
}

D3D12_PRIMITIVE_TOPOLOGY_TYPE getD3D12PrimitiveTopologyType(const buw::ePrimitiveTopology primitiveTopology) {
	switch (primitiveTopology) {
	case (buw::ePrimitiveTopology::LineStrip):
	case (buw::ePrimitiveTopology::LineList): return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
	case (buw::ePrimitiveTopology::PointList): return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
	case (buw::ePrimitiveTopology::TriangleStrip):
	case (buw::ePrimitiveTopology::TriangleList): return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	case (buw::ePrimitiveTopology::Undefined): return D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
	default: return D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
	}
}

D3D_PRIMITIVE_TOPOLOGY getD3D12PrimitiveTopology(const buw::ePrimitiveTopology primitiveTopology, bool adjacency) {
	switch (primitiveTopology) {
	case Rasterizer::ePrimitiveTopology::LineList: return (adjacency) ? D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ : D3D_PRIMITIVE_TOPOLOGY_LINELIST;
	case buw::ePrimitiveTopology::Undefined: return D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
	case buw::ePrimitiveTopology::PointList: return D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
	case buw::ePrimitiveTopology::LineStrip: return (adjacency) ? D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ: D3D_PRIMITIVE_TOPOLOGY_LINESTRIP;
	case buw::ePrimitiveTopology::TriangleList: return (adjacency) ? D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ : D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	case buw::ePrimitiveTopology::TriangleStrip: return (adjacency) ? D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ : D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	default: return D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
	}
}

D3D12_BLEND getD3D12BlendValue(buw::eBlendValue blendValue)
{
	switch(blendValue) {
	case buw::eBlendValue::One:
		return D3D12_BLEND_ONE;
	case buw::eBlendValue::Zero:
		return D3D12_BLEND_ZERO;
	case buw::eBlendValue::SrcColor:
		return D3D12_BLEND_SRC_COLOR;
	case buw::eBlendValue::InvSrcColor:
		return D3D12_BLEND_INV_SRC_COLOR;
	case buw::eBlendValue::SrcAlpha:
		return D3D12_BLEND_SRC_ALPHA;
	case buw::eBlendValue::InvSrcAlpha:
		return D3D12_BLEND_INV_SRC_ALPHA;
	case buw::eBlendValue::DestAlpha:
		return D3D12_BLEND_DEST_ALPHA;
	case buw::eBlendValue::InvDestAlpha:
		return D3D12_BLEND_INV_DEST_ALPHA;
	case buw::eBlendValue::DestColor:
		return D3D12_BLEND_DEST_COLOR;
	case buw::eBlendValue::InvDestColor:
		return D3D12_BLEND_INV_DEST_COLOR;
	case buw::eBlendValue::SrcAlphaSat:
		return D3D12_BLEND_SRC_ALPHA_SAT;
	case buw::eBlendValue::BlendFactor:
		return D3D12_BLEND_BLEND_FACTOR;
	case buw::eBlendValue::InvBlendFactor:
		return D3D12_BLEND_INV_BLEND_FACTOR;
	case buw::eBlendValue::Src1Color:
		return D3D12_BLEND_SRC1_COLOR;
	case buw::eBlendValue::InvSrc1Color:
		return D3D12_BLEND_INV_SRC1_COLOR;
	case buw::eBlendValue::Src1Alpha:
		return D3D12_BLEND_SRC1_ALPHA;
	case buw::eBlendValue::InvSrc1Alpha:
		return D3D12_BLEND_INV_SRC1_ALPHA;
	default:
		return D3D12_BLEND_ZERO;
	}
}

D3D12_BLEND_OP getD3D12BlendOperation(buw::eBlendOperation blendOperation)
{
	switch(blendOperation) {
	case buw::eBlendOperation::Add:
		return D3D12_BLEND_OP_ADD;
	case buw::eBlendOperation::Sub:
		return D3D12_BLEND_OP_SUBTRACT;
	case buw::eBlendOperation::RevSub:
		return D3D12_BLEND_OP_REV_SUBTRACT;
	case buw::eBlendOperation::Min:
		return D3D12_BLEND_OP_MIN;
	case buw::eBlendOperation::Max:
		return D3D12_BLEND_OP_MAX;
	default:
		return D3D12_BLEND_OP_ADD;
	}
}

D3D12_LOGIC_OP getD3D12LogicOperation(buw::eLogicOperation logicOperation)
{
	switch(logicOperation) {
	case buw::eLogicOperation::Clear:
		return D3D12_LOGIC_OP_CLEAR;
	case buw::eLogicOperation::Set:
		return D3D12_LOGIC_OP_SET;
	case buw::eLogicOperation::Copy:
		return D3D12_LOGIC_OP_COPY;
	case buw::eLogicOperation::CopyInv:
		return D3D12_LOGIC_OP_COPY_INVERTED;
	case buw::eLogicOperation::NoOp:
		return D3D12_LOGIC_OP_NOOP;
	case buw::eLogicOperation::Invert:
		return D3D12_LOGIC_OP_INVERT;
	case buw::eLogicOperation::And:
		return D3D12_LOGIC_OP_AND;
	case buw::eLogicOperation::Nand:
		return D3D12_LOGIC_OP_NAND;
	case buw::eLogicOperation::Or:
		return D3D12_LOGIC_OP_OR;
	case buw::eLogicOperation::Nor:
		return D3D12_LOGIC_OP_NOR;
	case buw::eLogicOperation::Xor:
		return D3D12_LOGIC_OP_XOR;
	case buw::eLogicOperation::Equiv:
		return D3D12_LOGIC_OP_EQUIV;
	case buw::eLogicOperation::AndRev:
		return D3D12_LOGIC_OP_AND_REVERSE;
	case buw::eLogicOperation::AndInv:
		return D3D12_LOGIC_OP_AND_INVERTED;
	case buw::eLogicOperation::OrRev:
		return D3D12_LOGIC_OP_OR_REVERSE;
	case buw::eLogicOperation::OrInv:
		return D3D12_LOGIC_OP_OR_INVERTED;
	default:
		return D3D12_LOGIC_OP_AND;
	}
}

D3D12_RENDER_TARGET_BLEND_DESC getD3D12RenderTargetBlendDesc(buw::renderTargetBlendDescription from)
{
	D3D12_RENDER_TARGET_BLEND_DESC to;
	to.BlendEnable = from.blendEnable;
	to.LogicOpEnable = from.logicOpEnable;
	to.BlendOp = getD3D12BlendOperation(from.blendOp);
	to.BlendOpAlpha = getD3D12BlendOperation(from.blendOpAlpha);
	to.LogicOp = getD3D12LogicOperation(from.logicOp);
	to.SrcBlend = getD3D12BlendValue(from.srcBlend);
	to.SrcBlendAlpha = getD3D12BlendValue(from.srcBlendAlpha);
	to.DestBlend = getD3D12BlendValue(from.destBlend);
	to.DestBlendAlpha = getD3D12BlendValue(from.destBlendAlpha);
	to.RenderTargetWriteMask = from.renderTargetWriteMask;
	return to;
}

D3D12_BLEND_DESC getD3D12BlendDesc(buw::blendStateDescription bsd) {
	D3D12_BLEND_DESC desc;
	desc.AlphaToCoverageEnable = bsd.alphaToCoverageEnable;
	desc.IndependentBlendEnable = bsd.independentBlendEnable;
	for(int i = 0; i < 8; i++)
		desc.RenderTarget[i] = getD3D12RenderTargetBlendDesc(bsd.renderTarget[i]);
	return desc;
}

void loadEffectFile(const std::string& filename, const std::string& pipelineStateName,
	std::string& vsFilename, std::string& vsEntry,
	std::string& gsFilename, std::string& gsEntry,
	std::string& psFilename, std::string& psEntry)
{
	if (!boost::filesystem::exists(filename.c_str()))
		throw buw::Exception("Cannot find effect file");

	std::string dir = boost::filesystem::path(filename.c_str()).parent_path().string();

	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename.c_str());

	auto xmlEffect = doc.FirstChildElement("effect");
	if (xmlEffect == nullptr)
		throw buw::Exception("Invalid effect file");

	auto xmlPipelineState = xmlEffect->FirstChildElement("pipelinestate");
	if (pipelineStateName != "")
	{
		for (; xmlPipelineState != nullptr; xmlPipelineState = xmlPipelineState->NextSiblingElement("pipelinestate"))
		{
			const auto name = ((const tinyxml2::XMLElement*)(xmlPipelineState))->FindAttribute("name");
			if (name != nullptr && name->Value() == pipelineStateName)
				break;
		}
	}

	if (xmlPipelineState == nullptr)
		throw buw::Exception("Invalid effect file");

	auto xmlD3D12 = xmlPipelineState->FirstChildElement("D3D12");
	if (xmlD3D12 == nullptr)
		throw buw::Exception("Invalid effect file");

	auto xmlD3D12VertexShader = xmlD3D12->FirstChildElement("VertexShader");
	if (xmlD3D12VertexShader != nullptr)
	{
		vsFilename = dir + "/" + xmlD3D12VertexShader->Attribute("filename");
		vsEntry = xmlD3D12VertexShader->Attribute("entry");
	}

	auto xmlD3D12GeometryShader = xmlD3D12->FirstChildElement("GeometryShader");
	if (xmlD3D12GeometryShader != nullptr)
	{
		gsFilename = dir + "/" + xmlD3D12GeometryShader->Attribute("filename");
		gsEntry = xmlD3D12GeometryShader->Attribute("entry");
	}

	auto xmlD3D12PixelShader = xmlD3D12->FirstChildElement("PixelShader");
	if (xmlD3D12PixelShader != nullptr)
	{
		psFilename = dir + "/" + xmlD3D12PixelShader->Attribute("filename");
		psEntry = xmlD3D12PixelShader->Attribute("entry");
	}
}

D3D12PipelineState::D3D12PipelineState(D3D12RenderSystem* renderSystem, const buw::pipelineStateDescription& psd)
    : IPipelineState(renderSystem, psd)
    , renderSystem_(renderSystem)
    , primitiveTopology_(psd.primitiveTopology)
    , numRenderTargets_(UINT(psd.renderTargetFormats.size()))
	, adjacency_(psd.useAdjacency) {
	ID3DBlob *vsCompiled = nullptr, *gsCompiled = nullptr, *psCompiled = nullptr;
	ID3D12ShaderReflection *vsReflection = nullptr, *gsReflection = nullptr, *psReflection = nullptr;

	std::string vsFilename, gsFilename, psFilename;
	std::string vsEntry, gsEntry, psEntry;

	BLUE_LOG(trace) << "Before compiling shaders.";
	loadEffectFile(
		psd.effectFilename, psd.pipelineStateName,
		vsFilename, vsEntry,
		gsFilename, gsEntry,
		psFilename, psEntry);

	if (vsFilename != "" && vsEntry != "")
		throwIfFailed(compileShader(vsFilename, "vs_5_0", vsEntry, &vsCompiled, &vsReflection));

	if (gsFilename != "" && gsEntry != "")
		throwIfFailed(compileShader(gsFilename, "gs_5_0", gsEntry, &gsCompiled, &gsReflection));

	if (psFilename != "" && psEntry != "")
		throwIfFailed(compileShader(psFilename, "ps_5_0", psEntry, &psCompiled, &psReflection));
	BLUE_LOG(trace) << "After compiling shaders.";

	fillBindings(vsReflection, D3D12_SHADER_VISIBILITY_VERTEX);
	fillBindings(gsReflection, D3D12_SHADER_VISIBILITY_GEOMETRY);
	fillBindings(psReflection, D3D12_SHADER_VISIBILITY_PIXEL);

	{
		ComPtr<ID3DBlob> signature;
		ComPtr<ID3DBlob> error;

		size_t numParams = cbBindings_.size() + samplerBindings_.size() + srvBindings_.size();

		std::vector<CD3DX12_DESCRIPTOR_RANGE> descRange(numParams);
		std::vector<CD3DX12_ROOT_PARAMETER> rootParam(numParams);

		int i = 0;
		for (int j = 0; j < cbBindings_.size(); j++, i++) {
			cbBindings_[j].slot = i;
			descRange[i].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, cbBindings_[j].reg);
			rootParam[i].InitAsDescriptorTable(1, &descRange[i], cbBindings_[j].visibility);
		}
		for (int j = 0; j < samplerBindings_.size(); j++, i++) {
			samplerBindings_[j].slot = i;
			descRange[i].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER, 1, samplerBindings_[j].reg);
			rootParam[i].InitAsDescriptorTable(1, &descRange[i], samplerBindings_[j].visibility);
		}
		for (int j = 0; j < srvBindings_.size(); j++, i++) {
			srvBindings_[j].slot = i;
			descRange[i].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, srvBindings_[j].reg);
			rootParam[i].InitAsDescriptorTable(1, &descRange[i], srvBindings_[j].visibility);
		}

		CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
		rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		rootSignatureDesc.NumParameters = static_cast<UINT>(rootParam.size());
		rootSignatureDesc.NumStaticSamplers = 0;
		rootSignatureDesc.pParameters = rootParam.size() > 0 ? &rootParam[0] : nullptr;
		rootSignatureDesc.pStaticSamplers = nullptr;
		rootSignatureDesc.Init((UINT)rootParam.size(), rootParam.size() > 0 ? &rootParam[0] : nullptr, 0, nullptr,
		                       D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

		throwIfFailed(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
		throwIfFailed(renderSystem_->getDevice()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(),
		                                                              IID_PPV_ARGS(&rootSignature_)));
	}

	{
		std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout = getD3D12InputLayoutDesc(psd.vertexLayout);

		CD3DX12_RASTERIZER_DESC rasterizerStateDesc(D3D12_DEFAULT);
		rasterizerStateDesc.FrontCounterClockwise = true;

		switch (psd.cullMode) {
		case Rasterizer::eCullMode::CullClockWiseFaces: 
			rasterizerStateDesc.CullMode = D3D12_CULL_MODE_BACK; 
			break;
		case Rasterizer::eCullMode::CullCounterClockWiseFaces:
			rasterizerStateDesc.CullMode = D3D12_CULL_MODE_FRONT; // Counter-Clockwise orientation should be considered as default triangle orientation
			break;
		case Rasterizer::eCullMode::None: 
			rasterizerStateDesc.CullMode = D3D12_CULL_MODE_NONE; 
			break;
		default: break;
		}
        if (renderSystem_->getMSAAEnabled() == true) {
            rasterizerStateDesc.MultisampleEnable = psd.useMSAA;
        }
        else {
            if(psd.useMSAA == true) BLUE_LOG(warning) << "MSAA is disabled.";
            rasterizerStateDesc.MultisampleEnable = false;
			
        }


		switch (psd.fillMode) {
		case Rasterizer::eFillMode::Solid:
			rasterizerStateDesc.FillMode = D3D12_FILL_MODE_SOLID;
			break;
		case Rasterizer::eFillMode::Wireframe:
			rasterizerStateDesc.FillMode = D3D12_FILL_MODE_WIREFRAME;
			break;
		default:
			throw buw::Exception("FillMode unknown.");
		}

		// Describe and create the graphics pipeline state object (PSO).
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.InputLayout = {&inputLayout[0], (UINT)inputLayout.size()};
		psoDesc.pRootSignature = rootSignature_.Get();
		if (vsCompiled != nullptr)
			psoDesc.VS = CD3DX12_SHADER_BYTECODE(vsCompiled);
		if (gsCompiled != nullptr)
			psoDesc.GS = CD3DX12_SHADER_BYTECODE(gsCompiled);
		if (psCompiled != nullptr)
			psoDesc.PS = CD3DX12_SHADER_BYTECODE(psCompiled);
		psoDesc.RasterizerState = rasterizerStateDesc;
		psoDesc.BlendState = getD3D12BlendDesc(psd.blendStateDesc);
		psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
        psoDesc.DepthStencilState.DepthFunc = getD3D12ComparisonFunction(psd.depthComparisonFunction);
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = getD3D12PrimitiveTopologyType(primitiveTopology_);
		psoDesc.NumRenderTargets = numRenderTargets_;
        for (UINT index = 0; index < numRenderTargets_; index++)
            psoDesc.RTVFormats[index] = mapTextureFormat(psd.renderTargetFormats[index]);
		psoDesc.DSVFormat = psd.useDepth ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_UNKNOWN;
        if (!psd.renderTargetFormats.empty() && psd.useMSAA && renderSystem_->getMSAAEnabled() == true) {
            psoDesc.SampleDesc.Count = renderSystem_->getSampleCount();
            psoDesc.SampleDesc.Quality = renderSystem_->getSampleQuality();
        }
        else {
            psoDesc.SampleDesc.Count = 1;
            psoDesc.SampleDesc.Quality = 0;
        }

		throwIfFailed(renderSystem_->getDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineState_)));
	}
}

D3D12PipelineState::~D3D12PipelineState() {
	pipelineState_ = nullptr;
	rootSignature_ = nullptr;
}

void D3D12PipelineState::fillBindings(ID3D12ShaderReflection* reflection, const D3D12_SHADER_VISIBILITY visibility) {
	if (reflection != nullptr) {
		D3D12_SHADER_DESC shaderDesc;
		reflection->GetDesc(&shaderDesc);
		for (UINT i = 0; i < shaderDesc.BoundResources; i++) {
			D3D12_SHADER_INPUT_BIND_DESC desc;
			reflection->GetResourceBindingDesc(i, &desc);
			if (desc.Type == D3D_SIT_CBUFFER)
				cbBindings_.push_back(Binding(const_cast<char*>(desc.Name), desc.BindPoint, visibility));
			else if (desc.Type == D3D_SIT_SAMPLER)
				samplerBindings_.push_back(Binding(const_cast<char*>(desc.Name), desc.BindPoint, visibility));
			else if (desc.Type == D3D_SIT_TEXTURE)
				srvBindings_.push_back(Binding(const_cast<char*>(desc.Name), desc.BindPoint, visibility));
		}
	}
}

bool D3D12PipelineState::useAdjacency() const {
	return adjacency_;
}

D3D12EffectCore::D3D12EffectCore(D3D12RenderSystem* renderSystem) : IEffectCore(renderSystem), renderSystem_(renderSystem) {
}

void D3D12EffectCore::preInit() {
}

void D3D12EffectCore::postInit() {
	throwIfFailed(renderSystem_->getDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, renderSystem_->getCommandAllocator().Get(),
	                                                            nullptr, IID_PPV_ARGS(&commandList_)));
	commandList_->Close();
}

buw::IRenderSystem* D3D12EffectCore::renderSystem() {
	return renderSystem_;
}

buw::ReferenceCounted<buw::IPipelineState> D3D12EffectCore::createPipelineState(const buw::pipelineStateDescription& psd) {
	return buw::makeReferenceCounted<D3D12PipelineState>(renderSystem_, psd);
}

void D3D12EffectCore::setPipelineState(buw::ReferenceCounted<buw::IPipelineState> ipipelineState) {
	current_ = std::static_pointer_cast<D3D12PipelineState>(ipipelineState);

	ID3D12DescriptorHeap* descHeaps[] = {renderSystem_->getShaderVisibleDescriptorHeap()->getPtr().Get(),
	                                     renderSystem_->getSamplerDescriptorHeap()->getPtr().Get()};

	commandList_->SetDescriptorHeaps(ARRAYSIZE(descHeaps), descHeaps);
	commandList_->SetGraphicsRootSignature(current_->rootSignature_.Get());
	commandList_->SetPipelineState(current_->pipelineState_.Get());
	commandList_->IASetPrimitiveTopology(getD3D12PrimitiveTopology(current_->primitiveTopology_, current_->useAdjacency()));
}

void D3D12EffectCore::setVertexBuffer(buw::ReferenceCounted<buw::IVertexBuffer> ivertexBuffer) const {
	buw::ReferenceCounted<D3D12VertexBuffer> vertexBuffer = std::static_pointer_cast<D3D12VertexBuffer>(ivertexBuffer);
	if (vertexBuffer) {
		D3D12_VERTEX_BUFFER_VIEW vb = vertexBuffer->getVertexBufferView();
		commandList_->IASetVertexBuffers(0, 1, &vb);
	} else {
		commandList_->IASetVertexBuffers(0, 1, nullptr);
	}
}

void D3D12EffectCore::setIndexBuffer(buw::ReferenceCounted<buw::IIndexBuffer> iindexBuffer) const {
	buw::ReferenceCounted<D3D12IndexBuffer> indexBuffer = std::static_pointer_cast<D3D12IndexBuffer>(iindexBuffer);
	D3D12_INDEX_BUFFER_VIEW ib = indexBuffer->getIndexBufferView();
	commandList_->IASetIndexBuffer(&ib);
}

void D3D12EffectCore::setConstantBuffer(buw::ReferenceCounted<buw::IConstantBuffer> iconstantBuffer, const std::string& name) const {
	buw::ReferenceCounted<D3D12ConstantBuffer> constantBuffer = std::static_pointer_cast<D3D12ConstantBuffer>(iconstantBuffer);
	
	bool found = false;
	for (const Binding& binding : current_->cbBindings_) {
		if (binding.name == name) {
			commandList_->SetGraphicsRootDescriptorTable(binding.slot, constantBuffer->getGPUConstantBufferView());
			found = true;
		}
	}

	if(!found)
		throw buw::Exception("Binding name %s not found", name.c_str());
}

void D3D12EffectCore::setTexture(buw::ReferenceCounted<buw::ITexture1D> itexture, const std::string& name) const {
	buw::ReferenceCounted<D3D12Texture1D> texture = std::static_pointer_cast<D3D12Texture1D>(itexture);
	texture->prepareSRV();

	bool found = false;
	for (const Binding& binding : current_->srvBindings_) {
		if (binding.name == name) {
			commandList_->SetGraphicsRootDescriptorTable(binding.slot, texture->getGPUShaderResourceView());
			found = true;
		}
	}

	if (!found)
		throw buw::Exception("Binding name %s not found", name.c_str());
}

void D3D12EffectCore::setTexture(buw::ReferenceCounted<buw::ITexture2D> itexture, const std::string& name) const {
	buw::ReferenceCounted<D3D12Texture2D> texture = std::static_pointer_cast<D3D12Texture2D>(itexture);
	texture->prepareSRV();

	bool found = false;
	for (const Binding& binding : current_->srvBindings_) {
		if (binding.name == name) {
			commandList_->SetGraphicsRootDescriptorTable(binding.slot, texture->getGPUShaderResourceView());
			found = true;
		}
	}

	if (!found)
		throw buw::Exception("Binding name %s not found", name.c_str());
}

void D3D12EffectCore::setTexture(buw::ReferenceCounted<buw::ITextureCube> itexture, const std::string& name) const {
    buw::ReferenceCounted<D3D12TextureCube> texture = std::static_pointer_cast<D3D12TextureCube>(itexture);
    texture->prepareSRV();

    bool found = false;
    for(const Binding& binding : current_->srvBindings_) {
        if(binding.name == name) {
            commandList_->SetGraphicsRootDescriptorTable(binding.slot, texture->getGPUShaderResourceView());
            found = true;
        }
    }

    if(!found)
        throw buw::Exception("Binding name %s not found", name.c_str());
}

void D3D12EffectCore::setSampler(buw::ReferenceCounted<buw::ISampler> isampler, const std::string& name) const {
	buw::ReferenceCounted<D3D12Sampler> sampler = std::static_pointer_cast<D3D12Sampler>(isampler);

	bool found = false;
	for (const Binding& binding : current_->samplerBindings_) {
		if (binding.name == name) {
			commandList_->SetGraphicsRootDescriptorTable(binding.slot, sampler->getGPUSamplerView());
			found = true;
		}
	}

	if (!found)
		throw buw::Exception("Binding name %s not found", name.c_str());
}

void D3D12EffectCore::setViewport(buw::ReferenceCounted<buw::IViewport> iviewport) const {
	buw::ReferenceCounted<D3D12Viewport> viewport = std::static_pointer_cast<D3D12Viewport>(iviewport);
	commandList_->RSSetViewports(1, viewport->viewport());
	commandList_->RSSetScissorRects(1, viewport->scissorRect());
}

void D3D12EffectCore::setRenderTarget(buw::ReferenceCounted<buw::ITexture2D> irenderTarget,
                                      buw::ReferenceCounted<buw::ITexture2D> idepthStencil) const {
	setRenderTargets({irenderTarget}, idepthStencil);
}

void D3D12EffectCore::setRenderTargets(std::vector<buw::ReferenceCounted<buw::ITexture2D>> irenderTargets,
                                       buw::ReferenceCounted<buw::ITexture2D> idepthStencil) const {
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandles[8];
	CD3DX12_CPU_DESCRIPTOR_HANDLE* prtvHandle = nullptr;
    //BLUE_ASSERT(current_->numRenderTargets_ == irenderTargets.size());
	
    for (int index = 0; index < irenderTargets.size(); ++index) {
        buw::ReferenceCounted<D3D12Texture2D> renderTarget = std::static_pointer_cast<D3D12Texture2D>(irenderTargets[index]);
        renderTarget->prepareRTV();
        rtvHandles[index] = renderTarget->getCPURenderTargetView();
    }
	prtvHandle = &rtvHandles[0];
	

	buw::ReferenceCounted<D3D12Texture2D> depthStencil = std::static_pointer_cast<D3D12Texture2D>(idepthStencil);
	CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle;
	CD3DX12_CPU_DESCRIPTOR_HANDLE* pdsvHandle = nullptr;

	if (depthStencil) {
		depthStencil->prepareDSV();
		dsvHandle = depthStencil->getCPUDepthStencilView();
		pdsvHandle = &dsvHandle;
	}

	commandList_->OMSetRenderTargets(UINT(irenderTargets.size()), prtvHandle, false, pdsvHandle);
}

void D3D12EffectCore::draw(UINT vertices) const {
	commandList_->DrawInstanced(vertices, 1, 0, 0);
}

void D3D12EffectCore::drawIndexed(UINT indices) const {
	commandList_->DrawIndexedInstanced(indices, 1, 0, 0, 0);
}

void D3D12EffectCore::preRender() {
	commandList_->Reset(renderSystem_->getCommandAllocator().Get(), nullptr);
}

void D3D12EffectCore::postRender() {
	current_ = nullptr;
	commandList_->Close();
	ID3D12CommandList* com = commandList_.Get();
	renderSystem_->getCommandQueue()->ExecuteCommandLists(1, &com);
}

std::string getFileAsString(const std::string& filename) {
	std::ifstream ifs(filename);
	return std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
}

HRESULT compileShader(const std::string& filename,
                      const std::string& shadermodel,
                      const std::string& entry,
                      ID3DBlob** compiledShader,
                      ID3D12ShaderReflection** reflection) {
	if (!boost::filesystem::exists(filename))
	{
		BLUE_LOG(error) << "File " << filename << " does not exist.";
		throw buw::Exception("File %s does not exist.", filename.c_str());
	}

// The following code does not produce the same results as the above shown one - it seems that the exist implementation has still some bugs... (tested with VC 2015)
// 	if (!std::tr2::sys::exists(filename)) {
// 		BLUE_LOG(error) << "File " << filename << " does not exist.";
// 		throw buw::Exception("File does not exist.");
// 	}

	UINT flag = 0;
#if _DEBUG
	flag |= D3DCOMPILE_DEBUG;
#endif // _DEBUG

	std::string sourceCode = getFileAsString(filename);
	ID3DBlob* errorBlob = nullptr;

	HRESULT hr = S_FALSE;
	hr = D3DCompile(sourceCode.c_str(), sourceCode.size(), filename.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), shadermodel.c_str(), flag, 0, compiledShader,
	                &errorBlob);

	if (errorBlob) {
		if (errorBlob->GetBufferSize() > 0) {
			BLUE_LOG(warning) << static_cast<char*>(errorBlob->GetBufferPointer());
			OutputDebugStringA(static_cast<char*>(errorBlob->GetBufferPointer()));
		}
		else {
			BLUE_LOG(error) << "D3DCompile: Strange error blob.";
		}
	}

	if (FAILED(hr))	{
		BLUE_LOG(error) << "D3DCompile failed. (2)";
		return hr;
	}

	BLUE_LOG(trace) << "Before D3DReflect.";
	hr = D3DReflect((*compiledShader)->GetBufferPointer(), (*compiledShader)->GetBufferSize(), IID_ID3D12ShaderReflection,
	                reinterpret_cast<void**>(reflection));

	return hr;
}

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END