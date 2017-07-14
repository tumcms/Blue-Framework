/*
	This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2016-2017 Technical University of Munich
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

// link D3D libraries with linker
#pragma comment(lib, "dxguid.lib")

#include "BlueFramework/Core/string.h"

#include "BlueFramework/D3D11RenderSystem/D3D11EffectCore.h"
#include "BlueFramework/D3D11RenderSystem/D3D11RenderSystem.h"

#include <boost/filesystem.hpp>

#include <tinyxml2.h>
// #include <fstream>
BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN


HRESULT compileShader(const std::string& filename,
	const std::string& shadermodel,
	const std::string& entry,
	ID3DBlob** compiledShader,
	ID3D11ShaderReflection** reflection);

DXGI_FORMAT getD3D11VertexFormat(const buw::eVertexAttributeFormat format) {
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

std::vector<D3D11_INPUT_ELEMENT_DESC> getD3D11InputLayoutDesc(const buw::VertexLayout& vl) {
	std::vector<D3D11_INPUT_ELEMENT_DESC> result;

	UINT alignedByteOffset = 0;

	for (int i = 0; i < vl.componentCount(); i++) {
		D3D11_INPUT_ELEMENT_DESC desc;
		const char* semanticName = buw::toString(vl.componentAt(i).semantic);
		desc.SemanticName = semanticName;
		desc.SemanticIndex = vl.componentAt(i).semanticIndex;
		desc.Format = getD3D11VertexFormat(vl.componentAt(i).format);
		desc.InputSlot = 0;
		desc.AlignedByteOffset = alignedByteOffset;
		alignedByteOffset += vl.componentAt(i).ByteSize();
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;

		result.push_back(desc);
	}

	return result;
}

D3D11_PRIMITIVE_TOPOLOGY getD3D11PrimitiveTopologyType(const buw::ePrimitiveTopology primitiveTopology, bool adjacency) {
	switch (primitiveTopology) {
	case (buw::ePrimitiveTopology::LineStrip): return (adjacency) ? D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ : D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
	case (buw::ePrimitiveTopology::LineList): return (adjacency) ? D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ : D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	case (buw::ePrimitiveTopology::PointList): return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
	case (buw::ePrimitiveTopology::TriangleStrip): return (adjacency) ? D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ : D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	case (buw::ePrimitiveTopology::TriangleList): return (adjacency) ? D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ : D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	case (buw::ePrimitiveTopology::Undefined): return D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
	default: return D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
	}
}

D3D11_FILL_MODE getD3D11FillMode(const buw::eFillMode fillMode) {
	switch (fillMode) {
	case buw::eFillMode::Solid: return D3D11_FILL_SOLID;
	case buw::eFillMode::Wireframe: return D3D11_FILL_WIREFRAME;
	default: return D3D11_FILL_SOLID;
	}
}

D3D11_CULL_MODE getD3D11CullMode(const buw::eCullMode cullMode) {
	switch (cullMode) {
	case buw::eCullMode::CullClockWiseFaces: return D3D11_CULL_BACK;
	case buw::eCullMode::CullCounterClockWiseFaces: return D3D11_CULL_FRONT;
	case buw::eCullMode::None: return D3D11_CULL_NONE;
	default: return D3D11_CULL_FRONT;
	}
}


// std::ofstream outfile("precompile.cmd");

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


	auto xmlD3D11 = xmlPipelineState->FirstChildElement("D3D11");
	if (xmlD3D11 == nullptr)
		throw buw::Exception("Invalid effect file");

	auto xmlD3D11VertexShader = xmlD3D11->FirstChildElement("VertexShader");
	if (xmlD3D11VertexShader != nullptr)
	{
		vsFilename = dir + "/" + xmlD3D11VertexShader->Attribute("filename");
		vsEntry = xmlD3D11VertexShader->Attribute("entry");
	}

	auto xmlD3D11GeometryShader = xmlD3D11->FirstChildElement("GeometryShader");
	if (xmlD3D11GeometryShader != nullptr)
	{
		gsFilename = dir + "/" + xmlD3D11GeometryShader->Attribute("filename");
		gsEntry = xmlD3D11GeometryShader->Attribute("entry");
	}

	auto xmlD3D11PixelShader = xmlD3D11->FirstChildElement("PixelShader");
	if (xmlD3D11PixelShader != nullptr)
	{
		psFilename = dir + "/" + xmlD3D11PixelShader->Attribute("filename");
		psEntry = xmlD3D11PixelShader->Attribute("entry");
	}

	/*boost::filesystem::path vsPath(vsFilename);
	boost::filesystem::path gsPath(gsFilename);
	boost::filesystem::path psPath(psFilename);

	std::string vsPreFilename = vsPath.parent_path().string() + "/" + vsPath.stem().string() + "_" + vsEntry + ".cso";
	std::string gsPreFilename = gsPath.parent_path().string() + "/" + gsPath.stem().string() + "_" + gsEntry + ".cso";
	std::string psPreFilename = psPath.parent_path().string() + "/" + psPath.stem().string() + "_" + psEntry + ".cso";

	if (vsFilename != "" && vsEntry != "")
		outfile << "fxc /T vs_5_0 /E " + vsEntry + " /Fo " + vsPreFilename + " " + vsFilename << std::endl;
	if (gsFilename != "" && gsEntry != "")
		outfile << "fxc /T gs_5_0 /E " + gsEntry + " /Fo " + gsPreFilename + " " + gsFilename << std::endl;
	if (psFilename != "" && psEntry != "")
		outfile << "fxc /T ps_5_0 /E " + psEntry + " /Fo " + psPreFilename + " " + psFilename << std::endl;*/
}


D3D11PipelineState::D3D11PipelineState(D3D11RenderSystem* renderSystem, const buw::pipelineStateDescription& psd) :
	IPipelineState(renderSystem, psd),
	renderSystem_(renderSystem),
	primitiveTopology_(psd.primitiveTopology),
	numRenderTargets_(UINT(psd.renderTargetFormats.size())),
	vertexShader_(nullptr),
	geometryShader_(nullptr),
	pixelShader_(nullptr),
	adjacency_(psd.useAdjacency)
{
	ID3DBlob *vsCompiled = nullptr, *gsCompiled = nullptr, *psCompiled = nullptr;
	ID3D11ShaderReflection *vsReflection = nullptr, *gsReflection = nullptr, *psReflection = nullptr;

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

	fillBindings(vsReflection, 0);
	fillBindings(gsReflection, 1);
	fillBindings(psReflection, 2);

	if (vsCompiled)
		renderSystem_->getDevice()->CreateVertexShader(vsCompiled->GetBufferPointer(), vsCompiled->GetBufferSize(), nullptr, vertexShader_.GetAddressOf());
	if (gsCompiled)
		renderSystem_->getDevice()->CreateGeometryShader(gsCompiled->GetBufferPointer(), gsCompiled->GetBufferSize(), nullptr, geometryShader_.GetAddressOf());
	if (psCompiled)
		renderSystem_->getDevice()->CreatePixelShader(psCompiled->GetBufferPointer(), psCompiled->GetBufferSize(), nullptr, pixelShader_.GetAddressOf());

	std::vector<D3D11_INPUT_ELEMENT_DESC> elements = getD3D11InputLayoutDesc(psd.vertexLayout);
	renderSystem_->getDevice()->CreateInputLayout(&elements[0], elements.size(), vsCompiled->GetBufferPointer(), vsCompiled->GetBufferSize(), inputLayout_.GetAddressOf());

	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = getD3D11FillMode(psd.fillMode);
	rd.CullMode = getD3D11CullMode(psd.cullMode);
	rd.FrontCounterClockwise = true;
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = renderSystem->getMSAAEnabled();
	rd.AntialiasedLineEnable = false;

	renderSystem_->getDevice()->CreateRasterizerState(&rd, rasterizerState_.GetAddressOf());
}
D3D11PipelineState::~D3D11PipelineState() {

}

void D3D11PipelineState::fillBindings(ID3D11ShaderReflection* reflection, int type) {
	if (reflection != nullptr) {
		D3D11_SHADER_DESC shaderDesc;
		reflection->GetDesc(&shaderDesc);
		for (UINT i = 0; i < shaderDesc.BoundResources; i++) {
			D3D11_SHADER_INPUT_BIND_DESC desc;
			reflection->GetResourceBindingDesc(i, &desc);
			switch (type) {
			case 0: bindings_[desc.Name].vsBindPoint = desc.BindPoint; bindings_[desc.Name].vsBindCount = desc.BindCount; break;
			case 1: bindings_[desc.Name].gsBindPoint = desc.BindPoint; bindings_[desc.Name].gsBindCount = desc.BindCount; break;
			case 2: bindings_[desc.Name].psBindPoint = desc.BindPoint; bindings_[desc.Name].psBindCount = desc.BindCount; break;
			default:
				break;
			}
		}
	}
}

bool D3D11PipelineState::useAdjacency() const {
	return adjacency_;
}

D3D11EffectCore::D3D11EffectCore(D3D11RenderSystem* renderSystem) : IEffectCore(renderSystem), renderSystem_(renderSystem) {
}

buw::IRenderSystem* D3D11EffectCore::renderSystem() {
	return renderSystem_;
}


buw::ReferenceCounted<buw::IPipelineState> D3D11EffectCore::createPipelineState(const buw::pipelineStateDescription& psd) {
	return buw::makeReferenceCounted<D3D11PipelineState>(renderSystem_, psd);
}
void D3D11EffectCore::setPipelineState(buw::ReferenceCounted<buw::IPipelineState> pipelineState) {
	current_ = std::static_pointer_cast<D3D11PipelineState>(pipelineState);

	renderSystem_->getDeviceContext()->IASetInputLayout(current_->inputLayout_.Get());
	renderSystem_->getDeviceContext()->IASetPrimitiveTopology(getD3D11PrimitiveTopologyType(current_->primitiveTopology_, current_->useAdjacency()));

	renderSystem_->getDeviceContext()->RSSetState(current_->rasterizerState_.Get());

	if (current_->vertexShader_)
		renderSystem_->getDeviceContext()->VSSetShader(current_->vertexShader_.Get(), nullptr, 0);
	else
		renderSystem_->getDeviceContext()->VSSetShader(nullptr, nullptr, 0);

	if (current_->geometryShader_)
		renderSystem_->getDeviceContext()->GSSetShader(current_->geometryShader_.Get(), nullptr, 0);
	else
		renderSystem_->getDeviceContext()->GSSetShader(nullptr, nullptr, 0);

	if (current_->pixelShader_)
		renderSystem_->getDeviceContext()->PSSetShader(current_->pixelShader_.Get(), nullptr, 0);
	else
		renderSystem_->getDeviceContext()->PSSetShader(nullptr, nullptr, 0);

}
void D3D11EffectCore::setVertexBuffer(buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer) const {
	ID3D11Buffer* vb = std::static_pointer_cast<D3D11VertexBuffer>(vertexBuffer)->getVertexBuffer().Get();
	UINT stride = vertexBuffer->getVertexSize(), offset = 0;
	renderSystem_->getDeviceContext()->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
}
void D3D11EffectCore::setIndexBuffer(buw::ReferenceCounted<buw::IIndexBuffer> indexBuffer) const {
	ID3D11Buffer* ib = std::static_pointer_cast<D3D11IndexBuffer>(indexBuffer)->getIndexBuffer().Get();
	renderSystem_->getDeviceContext()->IASetIndexBuffer(ib, mapIndexBufferFormat(indexBuffer->getFormat()), 0);
}
void D3D11EffectCore::setConstantBuffer(buw::ReferenceCounted<buw::IConstantBuffer> constantBuffer, const std::string& name) const {
	auto it = current_->bindings_.find(name);
	if (it != current_->bindings_.end()) {
		ID3D11Buffer* cb = std::static_pointer_cast<D3D11ConstantBuffer>(constantBuffer)->getConstantBuffer().Get();
		Binding& binding = it->second;

		if (binding.vsBindPoint >= 0)
			renderSystem_->getDeviceContext()->VSSetConstantBuffers(binding.vsBindPoint, binding.vsBindCount, &cb);
		if (binding.gsBindPoint >= 0)
			renderSystem_->getDeviceContext()->GSSetConstantBuffers(binding.gsBindPoint, binding.gsBindCount, &cb);
		if (binding.psBindPoint >= 0)
			renderSystem_->getDeviceContext()->PSSetConstantBuffers(binding.psBindPoint, binding.psBindCount, &cb);

	}
}
void D3D11EffectCore::setTexture(buw::ReferenceCounted<buw::ITexture1D> texture, const std::string& name) const {
	auto it = current_->bindings_.find(name);
	if (it != current_->bindings_.end()) {
		ID3D11ShaderResourceView* srv = std::static_pointer_cast<D3D11Texture1D>(texture)->getShaderResourceView().Get();
		Binding& binding = it->second;

		if (binding.vsBindPoint >= 0)
			renderSystem_->getDeviceContext()->VSSetShaderResources(binding.vsBindPoint, 1, &srv);
		if (binding.gsBindPoint >= 0)
			renderSystem_->getDeviceContext()->GSSetShaderResources(binding.gsBindPoint, 1, &srv);
		if (binding.psBindPoint >= 0)
			renderSystem_->getDeviceContext()->PSSetShaderResources(binding.psBindPoint, 1, &srv);

	}
}
void D3D11EffectCore::setTexture(buw::ReferenceCounted<buw::ITexture2D> texture, const std::string& name) const {
	auto it = current_->bindings_.find(name);
	if (it != current_->bindings_.end()) {
		ID3D11ShaderResourceView* srv = std::static_pointer_cast<D3D11Texture2D>(texture)->getShaderResourceView().Get();
		Binding& binding = it->second;

		if (binding.vsBindPoint >= 0)
			renderSystem_->getDeviceContext()->VSSetShaderResources(binding.vsBindPoint, 1, &srv);
		if (binding.gsBindPoint >= 0)
			renderSystem_->getDeviceContext()->GSSetShaderResources(binding.gsBindPoint, 1, &srv);
		if (binding.psBindPoint >= 0)
			renderSystem_->getDeviceContext()->PSSetShaderResources(binding.psBindPoint, 1, &srv);

	}
}
void D3D11EffectCore::setTexture(buw::ReferenceCounted<buw::ITextureCube> texture, const std::string& name) const {
	auto it = current_->bindings_.find(name);
	if (it != current_->bindings_.end()) {
		ID3D11ShaderResourceView* srv = std::static_pointer_cast<D3D11TextureCube>(texture)->getShaderResourceView().Get();
		Binding& binding = it->second;

		if (binding.vsBindPoint >= 0)
			renderSystem_->getDeviceContext()->VSSetShaderResources(binding.vsBindPoint, 1, &srv);
		if (binding.gsBindPoint >= 0)
			renderSystem_->getDeviceContext()->GSSetShaderResources(binding.gsBindPoint, 1, &srv);
		if (binding.psBindPoint >= 0)
			renderSystem_->getDeviceContext()->PSSetShaderResources(binding.psBindPoint, 1, &srv);

	}
}
void D3D11EffectCore::setSampler(buw::ReferenceCounted<buw::ISampler> sampler, const std::string& name) const {
	auto it = current_->bindings_.find(name);
	if (it != current_->bindings_.end()) {
		ID3D11SamplerState* ss = std::static_pointer_cast<D3D11Sampler>(sampler)->getSamplerState().Get();
		Binding& binding = it->second;

		if (binding.vsBindPoint >= 0)
			renderSystem_->getDeviceContext()->VSSetSamplers(binding.vsBindPoint, 1, &ss);
		if (binding.gsBindPoint >= 0)
			renderSystem_->getDeviceContext()->GSSetSamplers(binding.gsBindPoint, 1, &ss);
		if (binding.psBindPoint >= 0)
			renderSystem_->getDeviceContext()->PSSetSamplers(binding.psBindPoint, 1, &ss);

	}
}
void D3D11EffectCore::setViewport(buw::ReferenceCounted<buw::IViewport> viewport) const {
	const D3D11_VIEWPORT* vp = std::static_pointer_cast<D3D11Viewport>(viewport)->viewport();
	renderSystem_->getDeviceContext()->RSSetViewports(1, vp);
}
void D3D11EffectCore::setRenderTarget(buw::ReferenceCounted<buw::ITexture2D> renderTarget, buw::ReferenceCounted<buw::ITexture2D> depthStencil) const {
	ID3D11RenderTargetView* rt = nullptr;
	ID3D11DepthStencilView* ds = nullptr;

	if (renderTarget)
		rt = std::static_pointer_cast<D3D11Texture2D>(renderTarget)->getRenderTargetView().Get();
	if (depthStencil)
		ds = std::static_pointer_cast<D3D11Texture2D>(depthStencil)->getDepthStencilView().Get();

	renderSystem_->getDeviceContext()->OMSetRenderTargets(1, &rt, ds);
}
void D3D11EffectCore::setRenderTargets(std::vector<buw::ReferenceCounted<buw::ITexture2D>> renderTargets,
	buw::ReferenceCounted<buw::ITexture2D> depthStencil) const {
	ID3D11RenderTargetView** rts = nullptr;
	ID3D11DepthStencilView* ds = nullptr;

	std::vector<ID3D11RenderTargetView*> tmp(renderTargets.size());
	if (renderTargets.size() > 0)
	{
		for (int i = 0; i < renderTargets.size(); i++)
		{
			tmp[i] = std::static_pointer_cast<D3D11Texture2D>(renderTargets[i])->getRenderTargetView().Get();
		}
		rts = &tmp[0];
	}
	if (depthStencil)
		ds = std::static_pointer_cast<D3D11Texture2D>(depthStencil)->getDepthStencilView().Get();

	renderSystem_->getDeviceContext()->OMSetRenderTargets(renderTargets.size(), rts, ds);
}
void D3D11EffectCore::draw(UINT vertices) const {
	renderSystem_->getDeviceContext()->Draw(vertices, 0);
}
void D3D11EffectCore::drawIndexed(UINT indices) const {
	renderSystem_->getDeviceContext()->DrawIndexed(indices, 0, 0);
}

void D3D11EffectCore::preInit()
{}
void D3D11EffectCore::postInit()
{}
void D3D11EffectCore::preRender()
{}
void D3D11EffectCore::postRender()
{}

std::string getFileAsString(const std::string& filename) {
	std::ifstream ifs(filename);
	return std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
}

HRESULT compileShader(const std::string& filename,
	const std::string& shadermodel,
	const std::string& entry,
	ID3DBlob** compiledShader,
	ID3D11ShaderReflection** reflection)
{
	HRESULT hr = S_FALSE;

	boost::filesystem::path path(filename);
	std::string precompiledFilename = path.parent_path().string() + "/" + path.stem().string() + "_" + entry + ".cso";
	if (boost::filesystem::exists(precompiledFilename))
	{
		BLUE_LOG(trace) << "Found precompiled shader.";
		hr = D3DReadFileToBlob(buw::String(precompiledFilename).toWStdString().c_str(), compiledShader);
	}
	else
	{
		if (!boost::filesystem::exists(filename))
		{
			BLUE_LOG(error) << "File " << filename << " does not exist.";
			throw buw::Exception("File %s does not exist.", filename.c_str());
		}

		UINT flag = 0;
#if _DEBUG
		flag |= D3DCOMPILE_DEBUG;
#endif // _DEBUG

		std::string sourceCode = getFileAsString(filename);
		ID3DBlob* errorBlob = nullptr;

		hr = D3DCompile(sourceCode.c_str(), sourceCode.size(), filename.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), shadermodel.c_str(), flag, 0, compiledShader,
			&errorBlob);

		if (errorBlob) {
			if (errorBlob->GetBufferSize() > 0) {
				BLUE_LOG(warning) << static_cast<char*>(errorBlob->GetBufferPointer());
				OutputDebugStringA(static_cast<char*>(errorBlob->GetBufferPointer()));
			}
			else {
				BLUE_LOG(error) << "D3DCompile: Strange error blob. Error in shader " << filename.c_str();
			}
		}
	}

	if (FAILED(hr)) {
		BLUE_LOG(error) << "D3DCompile failed. Error in shader " << filename.c_str();
		return hr;
	}

	BLUE_LOG(trace) << "Before D3DReflect.";
	hr = D3DReflect((*compiledShader)->GetBufferPointer(), (*compiledShader)->GetBufferSize(), IID_ID3D11ShaderReflection,
		reinterpret_cast<void**>(reflection));

	return hr;
}

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END