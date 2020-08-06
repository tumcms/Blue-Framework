/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2020 Technical University of Munich
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

#include <gtest/gtest.h>
#include <BlueFramework/D3D11RenderSystem/D3D11RenderSystem.h>

using namespace testing;
using namespace BlueFramework::D3D11RenderSystem;

class D3D11Texture2DTest : public Test {

public:

	D3D11Texture2DTest() {
		_renderSystemDescription.renderAPI = BlueFramework::Rasterizer::eRenderAPI::Direct3D11;
		_renderSystemDescription.width = 640;
		_renderSystemDescription.height = 480;
		_renderSystemDescription.windowId = (void*)this;
		
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
	//Arrange
	buw::texture2DDescription desc = buw::texture2DDescription(
            100,
            100,
            BlueFramework::Rasterizer::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB);
	buw::ReferenceCounted<BlueFramework::Rasterizer::ITexture2D> texture = nullptr;

	// Act, Assert
	EXPECT_NO_THROW(texture = _renderSystem->createTexture2D(desc, buw::eTextureBindType::None));
	EXPECT_FALSE(texture == nullptr);

	// Annihilate
	texture.reset();
}