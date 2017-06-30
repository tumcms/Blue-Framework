#pragma once

#include <string>
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

#include "Rect.h"
#include "SignedDistanceFont.h"

#include "../../BlueEngine.h"
#include "BlueFramework/Rasterizer/IRenderSystem.h"
#include "BlueFramework/Core/class.h"

namespace BlueFramework { namespace Engine {

class Text
{
public:
	typedef enum { LEFT, CENTER, RIGHT } Alignment;
	//! Specifies the boundary used to break up text in word wrapping and other algorithms
	typedef enum { LINE, WORD } Boundary;
public:
	Text(buw::ReferenceCounted<buw::IRenderSystem> renderSystem);;

	virtual ~Text(void) {};

	virtual void draw(const buw::matrix44f& transform);
	virtual void drawWireframe();

	std::string	getFontFamily() const { if(mFont) return mFont->getFamily(); else return std::string(); }
	void		setFont( buw::ReferenceCounted<SignedDistanceFont> font ) { mFont = font; mInvalid = true; }

	float		getFontSize() const { return mFontSize; }
	void		setFontSize( float size ) { mFontSize = size; mInvalid = true; }

	float		getLineSpace() const { return mLineSpace; }
	void		setLineSpace( float value ) { mLineSpace = value; mInvalid = true; }

	float		getLeading() const { return (mFont ? std::floor( mFont->getLeading(mFontSize) * mLineSpace + 0.5f ) : 0.0f); }

	Alignment	getAlignment() const { return mAlignment; }
	void		setAlignment( Alignment alignment ) { mAlignment = alignment; mInvalid = true; }

	Boundary	getBoundary() const { return mBoundary; }
	void		setBoundary( Boundary boundary ) { mBoundary = boundary; mInvalid = true; }

//	void		setText(const std::string& text) { setText( ci::toUtf16(text) ); }
	void		setText(const std::wstring &text) { mText = text; mMust.clear(); mAllow.clear(); mInvalid = true; }

	Rectf		getBounds() const;
protected:
	//! get the maximum width of the text at the specified vertical position
	virtual float	getWidthAt(float /*y*/) { return 0.0f; }
	//! get the maximum height of the text
	virtual float	getHeight() { return 0.0f; }
	//! function to move the cursor to the next line
	virtual	bool	newLine( buw::vector2f *cursor ) {
		cursor->x() = 0.0f;
		cursor->y() += getLeading();

		return ( getHeight() == 0.0f || cursor->y() < getHeight() );
	}

	//!
	virtual std::string	getVertexShader() const;
	virtual std::string getFragmentShader() const;
	virtual bool		bindShader();
	virtual bool		unbindShader();

	//! clears the mesh and the buffers
	virtual void		clearMesh();
	//! renders the current contents of mText
	virtual void		renderMesh();
	//! helper to render a non-word-wrapped string
	virtual void		renderString( const std::wstring &str, buw::vector2f *cursor, float stretch=1.0f );
	//! creates the VBO from the data in the buffers
	virtual void		createMesh();
public:
	// special Unicode functions (requires Cinder v0.8.5)
	void findBreaksUtf8( const std::string& line, std::vector<size_t> *must, std::vector<size_t> *allow );
	void findBreaksUtf16( const std::wstring &line, std::vector<size_t> *must, std::vector<size_t> *allow );
	bool isWhitespaceUtf8( const char ch );
	bool isWhitespaceUtf16( const wchar_t ch );
protected:
	bool					mInvalid;

	mutable bool			mBoundsInvalid;
	mutable Rectf			mBounds;

	Alignment				mAlignment;
	Boundary				mBoundary;

	std::wstring			mText;

	buw::ReferenceCounted<buw::IRenderSystem> renderSystem_;
	buw::ReferenceCounted<buw::IShader>		shader_;
	buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer_;
	buw::ReferenceCounted<buw::IIndexBuffer>  indexBuffer_;
	buw::ReferenceCounted<buw::IVertexLayout> vertexLayout_;
	buw::ReferenceCounted<buw::ISamplerState> sampler_;
	buw::ReferenceCounted<buw::IBlendState>	defaultBlendState_;
	buw::ReferenceCounted<buw::IBlendState>	alphaCoverageState_;

	buw::ReferenceCounted<SignedDistanceFont>	mFont;
	float					mFontSize;

	float					mLineSpace;

	std::vector<size_t>		mMust, mAllow;
	std::vector<buw::vector3f>	mVertices;
	std::vector<uint32_t>	mIndices;
	std::vector<buw::vector2f>	mTexcoords;
};

} }

namespace buw
{
	using BlueFramework::Engine::Text;
}

