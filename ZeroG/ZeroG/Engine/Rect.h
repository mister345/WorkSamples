/*******************************************************************************
File:           Rect.h

Author:         Gregory Weiner
Version:        2.0 6.24.2015  
Last Modified:  10.11.2015     
License:        Free Software (GNU License Included)
Purpose:        This is part of a DirectX 9 framework for powering Win32 graphics
for 2D games. Many thanks to Chili and his excellent tutorials in
game programming with C++ for making this possible.

Description:    The Rect class contains functions for building rectangles from
                vectors to be used in more complicated geometries.

Requirements:   Latest Visual Studio C++ compiler recommended.

******************************************************************************/
#pragma once

#include "Vec2.h"

template < typename T >
class Rect
{
public:
	inline	Rect() {}
	inline	Rect( T top,T bottom,T left,T right )
		:
	top( top ),
	bottom( bottom ),
	left( left ),
	right( right )
	{}
	inline	Rect( const Rect& rect )
		:
	top( rect.top ),
	bottom( rect.bottom ),
	left( rect.left ),
	right( rect.right )
	{}
	inline	Rect( _Vec2<T> p0,_Vec2<T> p1 )
		:
		Rect( min( p0.y,p1.y ),
			max( p0.y,p1.y ),
			min( p0.x,p1.x ),
			max( p0.x,p1.x ) )
	{}
	inline	void Translate( _Vec2< T > d )
	{
		Translate( d.x,d.y );
	}
	inline	void Translate( T dx,T dy )
	{
		top += dy;
		bottom += dy;
		left += dx;
		right += dx;
	}
	template < typename T2 >
	inline	operator Rect< T2 >() const
	{
		return { (T2)top,(T2)bottom,(T2)left,(T2)right };
	}
	inline	void ClipTo( const Rect& rect )
	{
		top = max( top,rect.top );
		bottom = min( bottom,rect.bottom );
		left = max( left,rect.left );
		right = min( right,rect.right );
	}
	inline	T GetWidth() const
	{
		return right - left;
	}
	inline	T GetHeight() const
	{
		return bottom - top;
	}
	inline	bool Overlaps( const Rect& rect ) const
	{
		return top < rect.bottom && bottom > rect.top && 
			left < rect.right && right > rect.left;
	}
	template < typename T2 >
	inline	bool Contains( _Vec2<T2> p ) const
	{
		return p.y >= top && p.y <= bottom && p.x >= left && p.x <= right;
	}

public:
	T top;
	T bottom;
	T left;
	T right;
};

typedef Rect< int > RectI;
typedef Rect< float > RectF;