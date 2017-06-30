/*
 Copyright (c) 2010, The Barbarian Group
 All rights reserved.

 Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and
	the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
	the following disclaimer in the documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
*/

#include "Text.h"

#include <boost/algorithm/string/trim.hpp>

#include "linebreak/linebreak.h"

#undef min
#undef max

#include <algorithm>
#include <cmath>

void calcLinebreaksUtf8( const char *str, size_t strLength, std::vector<uint8_t> *resultBreaks )
{
	resultBreaks->resize( strLength, 0 );

	// our UnicodeBreaks enum lines up with the liblinebreak definitions
	set_linebreaks_utf8( (const uint8_t*)str, strLength, NULL, (char*)&(*resultBreaks)[0] );
}

void calcLinebreaksUtf8( const char *str, std::vector<uint8_t> *resultBreaks )
{
	calcLinebreaksUtf8( str, strlen( str ), resultBreaks );
}

void calcLinebreaksUtf16( const uint16_t *str, size_t strLength, std::vector<uint8_t> *resultBreaks )
{
	resultBreaks->resize( strLength, 0 );

	// our UnicodeBreaks enum lines up with the liblinebreak definitions
	set_linebreaks_utf16( (const unsigned short*)str, strLength, NULL, (char*)&(*resultBreaks)[0] );
}

void calcLinebreaksUtf16( const uint16_t *str, std::vector<uint8_t> *resultBreaks )
{
	size_t strLength = 0;
	while( str[strLength] )
		++strLength;

	calcLinebreaksUtf16( str, strLength, resultBreaks );
}

//! Values returned by calcBreaksUtf8 and calcBreaksUtf16
enum UnicodeBreaks { UNICODE_MUST_BREAK, UNICODE_ALLOW_BREAK, UNICODE_NO_BREAK, UNICODE_INSIDE_CHAR };


namespace BlueFramework { namespace Engine {

using namespace std;

Text::Text(buw::ReferenceCounted<buw::IRenderSystem> renderSystem) :
	mInvalid(true),
	mBoundsInvalid(true),
	mAlignment(LEFT),
	mBoundary(WORD),
	mFontSize(14.0f),
	mLineSpace(1.0f),
	renderSystem_(renderSystem)
{
	shader_ = renderSystem_->createShader("Shader/Text.be");

	buw::samplerStateDescription samplerStateDesc;
	samplerStateDesc.textureAddressModeU = buw::eTextureAddressMode::Clamp;
	samplerStateDesc.textureAddressModeV = buw::eTextureAddressMode::Clamp;
	samplerStateDesc.textureAddressModeW = buw::eTextureAddressMode::Clamp;
	samplerStateDesc.minificationFilter		= buw::eFilter::Anisotropic;
	samplerStateDesc.magnificationFilter	= buw::eFilter::Anisotropic;
	samplerStateDesc.mipLevelFilter			= buw::eFilter::Anisotropic;
	sampler_ = renderSystem_->createSamplerState(samplerStateDesc);

	buw::blendStateDescription default_bsd;
	defaultBlendState_ = renderSystem_->createBlendState(default_bsd);

	buw::blendStateDescription bsd;
	bsd.AlphaToCoverageEnable					= false;
	bsd.IndependentBlendEnable					= false;
	bsd.RenderTarget[0].BlendEnable				= true;
	bsd.RenderTarget[0].SourceBlend				= buw::eBlendOption::SourceAlpha;
	bsd.RenderTarget[0].DestinationBlend		= buw::eBlendOption::InverseSourceAlpha;
	bsd.RenderTarget[0].BlendOperation			= buw::eBlendOperation::Add;
	bsd.RenderTarget[0].SourceBlendAlpha		= buw::eBlendOption::SourceAlpha;
	bsd.RenderTarget[0].DestinationBlendAlpha	= buw::eBlendOption::InverseSourceAlpha;
	bsd.RenderTarget[0].BlendOperationAlpha		= buw::eBlendOperation::Add;
	bsd.RenderTarget[0].RenderTargetWriteMask	= buw::eColorWriteMaskFlags::All;
	alphaCoverageState_ = renderSystem_->createBlendState(bsd);
}

void Text::draw(const buw::matrix44f& transform)
{
	if( mInvalid ) {
		clearMesh();
		renderMesh();
		createMesh();
	}

	buw::drawIndexedCommand idc;
	idc.setIndexBuffer(indexBuffer_);
	idc.setVertexBuffer(vertexBuffer_);
	idc.setVertexLayout(vertexLayout_);
	idc.indexCount = mIndices.size();
	idc.startIndexLocation = 0;
	idc.primitveType = buw::ePrimitveType::TriangleList;
	BLUE_ASSERT(idc.validate(), "Invalid draw description");

	auto renderContext = renderSystem_->getImmediateContext();

	buw::matrix44f m = transform;//	buw::createScale44f(0.01, -0.01, 0.5);

	buw::vector4f vblendFactor(0.0f);
	renderContext->setBlendState(alphaCoverageState_, &vblendFactor[0] );

	shader_->setSampler("samplerLinear", sampler_);
	shader_->setValue("font_map", mFont->getTexture());

	shader_->setValue("WorldViewProjection", m);

	renderContext->bind(shader_);
	renderContext->draw(idc);
	renderContext->unbind(shader_);

	renderContext->setBlendState(defaultBlendState_, &vblendFactor[0] );
}

void Text::drawWireframe()
{

}

void Text::clearMesh()
{
 	mVertices.clear();
 	mIndices.clear();
 	mTexcoords.clear();

 	mInvalid = true;
}

void Text::renderMesh()
{
	// prevent errors
	if(!mInvalid) return;
	if(!mFont) return;
	if( mText.empty() )	return;

	// initialize variables
	const float		space = mFont->getAdvance(32, mFontSize);
	const float		height = getHeight() > 0.0f ? (getHeight() - mFont->getDescent(mFontSize)) : 0.0f;
	float			width, linewidth;
	size_t			index = 0;
	std::wstring	trimmed, chunk;

	// initialize cursor position
	buw::vector2f cursor(0.0f, std::floor(mFont->getAscent(mFontSize) + 0.5f));

	// get word/line break information from Cinder's Unicode class if not available
	if( mMust.empty() || mAllow.empty() )
		findBreaksUtf16( mText, &mMust, &mAllow );

	//double t = app::getElapsedSeconds();

	// reserve some room in the buffers, to prevent excessive resizing. Do not use the full string length,
	// because the text may contain white space characters that don't need to be rendered.
	size_t sz = mText.length() / 2;
	mVertices.reserve( 4 * sz );
	mTexcoords.reserve( 4 * sz );
	mIndices.reserve( 6 * sz );

	// process text in chunks
	std::vector<size_t>::iterator	mitr = mMust.begin();
	std::vector<size_t>::iterator	aitr = mAllow.begin();
	while( aitr != mAllow.end() && mitr != mMust.end() && (height == 0.0f || cursor.y() <= height) )
	{
		// calculate the maximum allowed width for this line
		linewidth = getWidthAt( cursor.y() );

		switch (mBoundary )
		{
		case LINE:
			// render the whole paragraph
			trimmed = boost::trim_copy( mText.substr(index, *mitr - index + 1) );
			width = mFont->measureWidth( trimmed, mFontSize, true );

			// advance iterator
			index = *mitr;
			++mitr;

			break;
		case WORD:
			// measure the first chunk on this line
			chunk = ( mText.substr(index, *aitr - index + 1) );
			width = mFont->measureWidth( chunk, mFontSize, false );

			// if it fits, add the next chunk until no more chunks fit or are available
			while( linewidth > 0.0f && width < linewidth && *aitr != *mitr )
			{
				++aitr;

				if( aitr == mAllow.end() )
					break;

				chunk = ( mText.substr(*(aitr-1) + 1, *aitr - *(aitr-1)) );
				width += mFont->measureWidth( chunk, mFontSize, false );
			}

			// end of line encountered
			if( aitr == mAllow.begin() || *(aitr-1) <= index )
			{	// not a single chunk fits on this line, just render what we have
			}
			else if( linewidth > 0.0f && width > linewidth )
			{	// remove the last chunk
				--aitr;
			}

			if( aitr != mAllow.end() )
			{
				//
				trimmed = boost::trim_copy( mText.substr(index, *aitr - index + 1) );
				width = mFont->measureWidth( trimmed, mFontSize );

				// end of paragraph encountered, move to next
				if( *aitr == *mitr )
					++mitr;
				/*else if( mAlignment == JUSTIFIED )
				{
					// count spaces
					uint32_t c = std::count( trimmed.begin(), trimmed.end(), 32 );
					if( c == 0 ) break;
					// remaining whitespace
					float remaining = getWidthAt( cursor.y ) - width;
					float space = mFont->getAdvance( 32, mFontSize );
					//
					stretch = (remaining / c + space) / space;
					if( stretch > 3.0f ) stretch = 1.0f;
				}*/

				// advance iterator
				index = *aitr;
				++aitr;
			}

			break;
		}

		// adjust alignment
		switch( mAlignment ) {
			case CENTER:
				cursor.x() = 0.5f * (linewidth - width);
				break;
			case RIGHT:
				cursor.x() = (linewidth - width);
				break;
			break;
		}

		// add this fitting part of the text to the mesh
		renderString( trimmed, &cursor );

		// advance cursor to new line
		if( !newLine(&cursor) ) break;
	}
}

void Text::renderString( const std::wstring &str, buw::vector2f *cursor, float stretch )
{
	std::wstring::const_iterator itr;
	for(itr=str.begin();itr!=str.end();++itr) {
		// retrieve character code
		uint16_t id = (uint16_t) *itr;

		if( mFont->contains(id) ) {
			// get metrics for this character to speed up measurements
			SignedDistanceFont::Metrics m = mFont->getMetrics(id);

			// skip whitespace characters
			if( ! isWhitespaceUtf16(id) ) {
				size_t index = mVertices.size();


				Rectf bounds = mFont->getBounds(m, mFontSize);
				mVertices.push_back( buw::vector3f(*cursor + bounds.getUpperLeft()	, 0.0f ) );
				mVertices.push_back( buw::vector3f(*cursor + bounds.getUpperRight()	, 0.0f ) );
				mVertices.push_back( buw::vector3f(*cursor + bounds.getLowerRight()	, 0.0f ) );
				mVertices.push_back( buw::vector3f(*cursor + bounds.getLowerLeft()	, 0.0f ) );

				bounds = mFont->getTexCoords(m);
				mTexcoords.push_back( buw::vector2f( bounds.getUpperLeft()	));
				mTexcoords.push_back( buw::vector2f( bounds.getUpperRight()	));
				mTexcoords.push_back( buw::vector2f( bounds.getLowerRight()	));
				mTexcoords.push_back( buw::vector2f( bounds.getLowerLeft()	));

				mIndices.push_back(index+0); mIndices.push_back(index+3); mIndices.push_back(index+1);
				mIndices.push_back(index+1); mIndices.push_back(index+3); mIndices.push_back(index+2);
			}

			if( id == 32 )
				cursor->x() += stretch * mFont->getAdvance(m, mFontSize);
			else
				cursor->x() += mFont->getAdvance(m, mFontSize);
		}
	}

	//
	mBoundsInvalid = true;
}

void Text::createMesh()
{
 	//
 	if( mVertices.empty() || mIndices.empty() )
 		return;

// 	//
// 	gl::VboMesh::Layout layout;
// 	layout.setStaticPositions();
// 	layout.setStaticIndices();
// 	layout.setStaticTexCoords2d();
// 	//layout.setStaticColorsRGBA();
//
// 	mVboMesh = gl::VboMesh( mVertices.size(), mIndices.size(), layout, GL_TRIANGLES );
// 	mVboMesh.bufferPositions( &mVertices.front(), mVertices.size() );
// 	mVboMesh.bufferIndices( mIndices );
// 	mVboMesh.bufferTexCoords2d( 0, mTexcoords );
// 	//mVboMesh.bufferColorsRGBA( colors );
//

	std::vector<buw::VertexPosition3Texture2> vertices;
	for (int i = 0; i < mVertices.size(); i++)
	{
		buw::VertexPosition3Texture2 v;
		v.position = mVertices[i];
		v.uv = mTexcoords[i];
		vertices.push_back(v);
	}

	vertexLayout_ = renderSystem_->createVertexLayout(
		buw::VertexPosition3Texture2::getVertexLayoutDescription(),
		buw::VertexPosition3Texture2::getVertexLayoutElementCount(),
		shader_
	);

	vertexBuffer_ = renderSystem_->createVertexBuffer(
		sizeof(buw::VertexPosition3Texture2),
		static_cast<unsigned int>(vertices.size()),
		buw::eBufferUsage::Static,
		&vertices[0]
	);

	indexBuffer_ = renderSystem_->createIndexBuffer(
		buw::eIndexBufferFormat::UnsignedInt32,
		static_cast<int>(mIndices.size()),
		buw::eBufferUsage::Static,
		&mIndices[0]
	);

	mInvalid = false;
}

Rectf Text::getBounds() const
{
	if( mBoundsInvalid )
	{
		mBounds = Rectf(0.0f, 0.0f, 0.0f, 0.0f);

		vector< buw::vector3f >::const_iterator itr = mVertices.begin();
		while( itr != mVertices.end() ) {
			mBounds.x1 = std::min( itr->x(), mBounds.x1 );
			mBounds.y1 = std::min( itr->y(), mBounds.y1 );
			mBounds.x2 = std::max( itr->x(), mBounds.x2 );
			mBounds.y2 = std::max( itr->y(), mBounds.y2 );
			++ itr;
		}

		mBoundsInvalid = false;
	}

	return mBounds;
}

std::string Text::getVertexShader() const
{
	// vertex shader
	const char *vs =
		"#version 110\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_FrontColor = gl_Color;\n"
		"	gl_TexCoord[0] = gl_MultiTexCoord0;\n"
		"\n"
		"	gl_Position = ftransform();\n"
		"}\n";

	return std::string(vs);
}

std::string Text::getFragmentShader() const
{
	// fragment shader
	const char *fs =
		"#version 110\n"
		"\n"
		"uniform sampler2D	font_map;\n"
		"uniform float      smoothness;\n"
		"\n"
		"const float gamma = 2.2;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	// retrieve signed distance\n"
		"	float sdf = texture2D( font_map, gl_TexCoord[0].xy ).r;\n"
		"\n"
		"	// perform adaptive anti-aliasing of the edges\n"
		"	float w = clamp( smoothness * (abs(dFdx(gl_TexCoord[0].x)) + abs(dFdy(gl_TexCoord[0].y))), 0.0, 0.5);\n"
		"	float a = smoothstep(0.5-w, 0.5+w, sdf);\n"
		"\n"
		"	// gamma correction for linear attenuation\n"
		"	a = pow(a, 1.0/gamma);\n"
		"\n"
		"	// final color\n"
		"	gl_FragColor.rgb = gl_Color.rgb;\n"
		"	gl_FragColor.a = gl_Color.a * a;\n"
		"}\n";

	return std::string(fs);
}

bool Text::bindShader()
{
// 	if( ! mShader )
// 	{
// 		try {
// 			mShader = gl::GlslProg( getVertexShader().c_str(), getFragmentShader().c_str() );
// 		}
// 		catch( const std::exception &e ) {
// 			app::console() << "Could not load&compile shader: " << e.what() << std::endl;
// 			mShader = gl::GlslProg(); return false;
// 		}
// 	}
//
// 	mShader.bind();
// 	mShader.uniform( "font_map", 0 );
// 	mShader.uniform( "smoothness", 64.0f );

	return true;
}

bool Text::unbindShader()
{
// 	if( mShader )
// 		mShader.unbind();

	return true;
}

void Text::findBreaksUtf8( const std::string& line, std::vector<size_t> *must, std::vector<size_t> *allow )
{
	std::vector<uint8_t> resultBreaks;
	calcLinebreaksUtf8( line.c_str(), &resultBreaks );

	//
	must->clear();
	allow->clear();

	//
	for(size_t i=0;i<resultBreaks.size();++i) {
		if( resultBreaks[i] == UNICODE_ALLOW_BREAK )
			allow->push_back( i );
		else if( resultBreaks[i] == UNICODE_MUST_BREAK ) {
			must->push_back( i );
			allow->push_back( i );
		}
	}
}

void Text::findBreaksUtf16( const std::wstring &line, std::vector<size_t> *must, std::vector<size_t> *allow )
{
	std::vector<uint8_t> resultBreaks;
	calcLinebreaksUtf16( (uint16_t*) line.c_str(), &resultBreaks );

	//
	must->clear();
	allow->clear();

	//
	for(size_t i=0;i<resultBreaks.size();++i) {
		if( resultBreaks[i] == UNICODE_ALLOW_BREAK )
			allow->push_back( i );
		else if( resultBreaks[i] == UNICODE_MUST_BREAK ) {
			must->push_back( i );
			allow->push_back( i );
		}
	}
}

bool Text::isWhitespaceUtf8( const char ch )
{
	return isWhitespaceUtf16( (short) ch );
}

bool Text::isWhitespaceUtf16( const wchar_t ch )
{
	// see: http://en.wikipedia.org/wiki/Whitespace_character,
	// make sure the values are in ascending order,
	// otherwise the binary search won't work
	static const wchar_t arr[] = {
		0x0009, 0x000A, 0x000B, 0x000C, 0x000D,
		0x0020, 0x0085, 0x00A0, 0x1680, 0x180E,
		0x2000, 0x2001, 0x2002, 0x2003, 0x2004,
		0x2005, 0x2006, 0x2007, 0x2008, 0x2009,
		0x200A, 0x2028, 0x2029, 0x202F, 0x205F, 0x3000
	};
	static const vector<wchar_t> whitespace(arr, arr + sizeof(arr) / sizeof(arr[0]) );

	return std::binary_search( whitespace.begin(), whitespace.end(), ch );
}

} } // namespace ph::text
