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

#include <limits>
using std::numeric_limits;

namespace BlueFramework
{
	namespace Engine
	{

template<typename T>
RectT<T>::RectT( const std::vector<Vector2 > &points )
{
	x1 = numeric_limits<T>::max();
	x2 = -numeric_limits<T>::max();
	y1 = numeric_limits<T>::max();
	y2 = -numeric_limits<T>::max();
	for( size_t s = 0; s < points.size(); ++s )
		include( points[s] );
}

template<typename T>
void RectT<T>::set( T aX1, T aY1, T aX2, T aY2 )
{
	x1 = aX1;
	y1 = aY1;
	x2 = aX2;
	y2 = aY2;
}

template<typename T>
void RectT<T>::canonicalize()
{
	if ( x1 > x2 ) {
		T temp = x1;
		x1 = x2;
		x2 = temp;
	}

	if ( y1 > y2 ) {
		T temp = y1;
		y1 = y2;
		y2 = temp;
	}
}

template<typename T>
RectT<T> RectT<T>::canonicalized() const
{
	RectT<T> result( *this );
	result.canonicalize();
	return result;
}

template<typename T>
void RectT<T>::clipBy( const RectT &clip )
{
	if ( x1 < clip.x1 )
		x1 = clip.x1;
	if ( x2 < clip.x1 )
		x2 = clip.x1;
	if ( x1 > clip.x2 )
		x1 = clip.x2;
	if ( x2 > clip.x2 )
		x2 = clip.x2;

	if ( y1 < clip.y1 )
		y1 = clip.y1;
	if ( y2 < clip.y1 )
		y2 = clip.y1;
	if ( y1 > clip.y2 )
		y1 = clip.y2;
	if ( y2 > clip.y2 )
		y2 = clip.y2;
}

template<typename T>
RectT<T> RectT<T>::getClipBy( const RectT &clip ) const
{
	RectT<T> result( *this );
	result.clipBy( RectT<T>( clip ) );
	return result;
}

template<typename T>
void RectT<T>::offset( const Vector2 &offset )
{
	x1 += offset.x();
	x2 += offset.x();
	y1 += offset.y();
	y2 += offset.y();
}

template<typename T>
void RectT<T>::inflate( const Vector2 &amount )
{
	x1 -= amount.x();
	x2 += amount.x();
	y1 -= amount.y(); // assume canonical rect has y1 < y2
	y2 += amount.y();
}

template<typename T>
RectT<T> RectT<T>::inflated( const Vector2 &amount ) const
{
	RectT<T> result( *this );
	result.inflate( amount );
	return result;
}

template<typename T>
void RectT<T>::scaleCentered( const Vector2 &scale )
{
	T halfWidth = getWidth() * scale.x() / 2.0f;
	T halfHeight = getHeight() * scale.y() / 2.0f;
	const Vector2 center( getCenter() );
	x1 = center.x() - halfWidth;
	x2 = center.x() + halfWidth;
	y1 = center.y() - halfHeight;
	y2 = center.y() + halfHeight;
}

template<typename T>
void RectT<T>::scaleCentered( T scale )
{
	T halfWidth = getWidth() * scale / 2;
	T halfHeight = getHeight() * scale / 2;
	const Vector2 center( getCenter() );
	x1 = center.x() - halfWidth;
	x2 = center.x() + halfWidth;
	y1 = center.y() - halfHeight;
	y2 = center.y() + halfHeight;
}

template<typename T>
RectT<T> RectT<T>::scaledCentered( T scale ) const
{
	T halfWidth = getWidth() * scale / 2;
	T halfHeight = getHeight() * scale / 2;
	const Vector2 center( getCenter() );
	return RectT<T>( center.x() - halfWidth, center.y() - halfHeight, center.x() + halfWidth, center.y() + halfHeight );
}

template<typename T>
void RectT<T>::scale( T s )
{
	x1 *= s;
	x2 *= s;
	y1 *= s;
	y2 *= s;
}

template<typename T>
void RectT<T>::scale( const Vector2 &scale )
{
	x1 *= scale.x();
	y1 *= scale.y();
	x2 *= scale.x();
	y2 *= scale.y();
}

template<typename T>
RectT<T> RectT<T>::scaled( T s ) const
{
	return RectT<T>( x1 * s, y1 * s, x2 * s, y2 * s );
}

template<typename T>
RectT<T> RectT<T>::scaled( const Vector2 &scale ) const
{
	return RectT<T>( x1 * scale.x(), y1 * scale.y(), x2 * scale.x(), y2 * scale.y() );
}

template<typename T>
bool RectT<T>::intersects( const RectT<T> &rect ) const
{
	if( ( x1 > rect.x2 ) || ( x2 < rect.x1 ) || ( y1 > rect.y2 ) || ( y2 < rect.y1 ) )
		return false;
	else
		return true;
}

template<typename T>
T RectT<T>::distance( const Vector2 &pt ) const
{
	T squaredDistance = 0;
	if( pt.x() < x1 ) squaredDistance += ( x1 - pt.x() ) * ( x1 - pt.x() );
	else if( pt.x() > x2 ) squaredDistance += ( pt.x() - x2 ) * ( pt.x() - x2 );
	if( pt.y() < y1 ) squaredDistance += ( y1 - pt.y() ) * ( y1 - pt.y() );
	else if( pt.y() > y2 ) squaredDistance += ( pt.y() - y2 ) * ( pt.y() - y2 );
	
	if( squaredDistance > 0 )
		return std::sqrt( squaredDistance );
	else
		return 0;
}

template<typename T>
T RectT<T>::distanceSquared( const Vector2 &pt ) const
{
	T squaredDistance = 0;
	if( pt.x() < x1 ) squaredDistance += ( x1 - pt.x() ) * ( x1 - pt.x() );
	else if( pt.x() > x2 ) squaredDistance += ( pt.x() - x2 ) * ( pt.x() - x2 );
	if( pt.y() < y1 ) squaredDistance += ( y1 - pt.y() ) * ( y1 - pt.y() );
	else if( pt.y() > y2 ) squaredDistance += ( pt.y() - y2 ) * ( pt.y() - y2 );
	
	return squaredDistance;
}

template<typename T>
BlueFramework::Core::Math::vector<T, 2>	RectT<T>::closestPoint( const Vector2 &pt ) const
{
	Vector2 result = pt;
	if( pt.x() < x1 ) result.x() = x1;
	else if( pt.x() > x2 ) result.x() = x2;
	if( pt.y() < y1 ) result.y() = y1;
	else if( pt.y() > y2 ) result.y() = y2;
	return result;
}

template<typename T>
void RectT<T>::include( const Vector2 &point )
{
	if( x1 > point.x() ) x1 = point.x();
	if( x2 < point.x() ) x2 = point.x();
	if( y1 > point.y() ) y1 = point.y();
	if( y2 < point.y() ) y2 = point.y();
}

template<typename T>
void RectT<T>::include( const std::vector<Vector2 > &points )
{
	for( size_t s = 0; s < points.size(); ++s )
		include( points[s] );
}

template<typename T>
void RectT<T>::include( const RectT<T> &rect )
{
	include( Vector2( rect.x1, rect.y1 ) );
	include( Vector2( rect.x2, rect.y2 ) );
}

template<typename T>
RectT<T> RectT<T>::getCenteredFit( const RectT<T> &other, bool expand ) const
{
	RectT<T> result = *this;
	result.offset( other.getCenter() - result.getCenter() );
	
	bool isInside = ( ( result.getWidth() < other.getWidth() ) && ( result.getHeight() < other.getHeight() ) );
	if( expand || ( ! isInside ) ) { // need to do some scaling
		T aspectAspect = result.getAspectRatio() / other.getAspectRatio();
		if( aspectAspect >= 1.0f ) { // result is proportionally wider so we need to fit its x-axis
			T scaleBy = other.getWidth() / result.getWidth();
			result.scaleCentered( scaleBy );
		}
		else { // result is proportionally wider so we need to fit its y-axis
			T scaleBy = other.getHeight() / result.getHeight();
			result.scaleCentered( scaleBy );
		}
	}
	
	return result;
}

template<typename T>
std::ostream& operator<< ( std::ostream& o, const RectT<T>& rect )
{
	return o << "(" << rect.x1 << ", " << rect.y1 << ")-(" << rect.x2 << ", " << rect.y2 << ")";
}

template class RectT<float>;
template class RectT<double>;

}
}