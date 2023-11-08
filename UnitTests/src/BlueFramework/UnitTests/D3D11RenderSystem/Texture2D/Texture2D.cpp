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

#include <BlueFramework/D3D11RenderSystem/D3D11RenderSystem.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace BlueFramework::D3D11RenderSystem;

class ITexture2DBuilder {
	
	buw::texture2DDescription _desc = buw::texture2DDescription(1,1, buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB);
	buw::eTextureBindType _bindType = BlueFramework::Rasterizer::eTextureBindType::None;
	buw::ReferenceCounted<buw::IRenderSystem> _renderSystem = nullptr;
	
public:
	buw::ReferenceCounted<buw::ITexture2D> Build() {
		return _renderSystem->createTexture2D(_desc, _bindType);
	}

	ITexture2DBuilder WithMSAA() {
		_desc.useMSAA = true;
		_bindType = BlueFramework::Rasterizer::eTextureBindType::SRV;
		return *this;
	}

	ITexture2DBuilder WithDescription(const BlueFramework::Rasterizer::texture2DDescription& desc) {
		_desc = desc;
		return *this;
	}

	ITexture2DBuilder MakeCPUReadable() {
		_desc.isCpuReadable = true;
		return *this;
	}

	ITexture2DBuilder(const buw::ReferenceCounted<D3D11RenderSystem> & renderSystem) : _renderSystem{renderSystem} {
		
	}
};

class D3D11Texture2DTest : public Test {
public:
	D3D11Texture2DTest() {
		_renderSystemDescription.renderAPI = BlueFramework::Rasterizer::eRenderAPI::Direct3D11;
		_renderSystemDescription.width = 640;
		_renderSystemDescription.height = 480;
		_renderSystemDescription.windowId = (void*)this;
		_renderSystemDescription.enableMSAA = true;

		_renderSystem = buw::makeReferenceCounted<D3D11RenderSystem>(_renderSystemDescription);
	}

	~D3D11Texture2DTest() override {
		_renderSystem.reset();
	}

protected:
	buw::renderSystemDescription _renderSystemDescription = buw::renderSystemDescription();
	buw::ReferenceCounted<D3D11RenderSystem> _renderSystem = nullptr;

	void SetUp() override {
	}

	void TearDown() override {
	}
};

TEST_F(D3D11Texture2DTest, CreateTexture2D_AfterConstruction_IsNotNull) {
	// Arrange
	buw::ReferenceCounted<BlueFramework::Rasterizer::ITexture2D> texture = nullptr;
	buw::texture2DDescription desc = buw::texture2DDescription(100, 100, BlueFramework::Rasterizer::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB);
		
	// Act, Assert
	EXPECT_NO_THROW(texture = ITexture2DBuilder(_renderSystem).WithDescription(desc).Build());
	EXPECT_FALSE(texture == nullptr);

	// Annihilate
	texture.reset();
}

TEST_F(D3D11Texture2DTest, CreateWithMSAA_AfterCreation_HasMSAAEnabled) {
	// Arrange
	auto texture = ITexture2DBuilder(_renderSystem)
		.WithMSAA()
		.Build();

	// Act, Assert
	EXPECT_TRUE(texture->isMultisampled());

	// Annihilate
	texture.reset();
}

TEST_F(D3D11Texture2DTest, TextureWithMSAA_MakeCPUReadable_IsCPUReadable) {
	// Arrange
	auto texture = ITexture2DBuilder(_renderSystem)
		.WithMSAA()
		.MakeCPUReadable()
		.Build();

	// Act, Assert
	EXPECT_TRUE(texture->isCPUReadable());

	// Annihilate
	texture.reset();
}

TEST_F(D3D11Texture2DTest, TextureWithMSAA_DownloadTexture_NoFailure) {
	// Arrange
	auto texture = ITexture2DBuilder(_renderSystem)
		.WithMSAA()
		.MakeCPUReadable()
		.Build();

	buw::Image4b image = buw::Image4b(texture->width(), texture->height());
	
	// Act, Assert
	EXPECT_NO_THROW(_renderSystem->downloadTexture(texture, image));

	// Annihilate
	texture.reset();
}

