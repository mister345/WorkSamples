/*************************************************************************************
* File:           Mouse.cpp                                                          *
*                                                                                    *
* Author:         Gregory Weiner                                                     *
* Version:        2.0 6.24.2015                                                      *
* Last Modified:  10.11.2015                                                         *
* License:        Free Software (GNU License Included)                               *
* Purpose:        This is part of a DirectX 9 framework for powering Win32 graphics  *
*                 for 2D games. Many thanks to Chili and his excellent tutorials in  *
*                 game programming with C++ for making this possible.                *
*                                                                                    *
* Description:    Mouse input functionality.                                         *
*                                                                                    *
* Requirements:   Latest Visual Studio C++ compiler recommended.                     *
*                                                                                    *
**************************************************************************************/

#include "Mouse.h"

MouseClient::MouseClient( MouseServer& server )
: server( server )
{}
int MouseClient::GetMouseX() const
{
	return server.x;
}
int MouseClient::GetMouseY() const
{
	return server.y;
}
bool MouseClient::LeftIsPressed() const
{
	return server.leftIsPressed;
}
bool MouseClient::RightIsPressed() const
{
	return server.rightIsPressed;
}
bool MouseClient::IsInWindow() const
{
	return server.isInWindow;
}
MouseEvent MouseClient::ReadMouse()
{
	if( server.buffer.size() > 0 )
	{
		MouseEvent e = server.buffer.front( );
		server.buffer.pop( );
		return e;
	}
	else
	{
		return MouseEvent( MouseEvent::Invalid,0,0 );
	}
}
bool MouseClient::MouseEmpty( ) const
{
	return server.buffer.empty( );
}


MouseServer::MouseServer()
:	isInWindow( false ),
	leftIsPressed( false ),
	rightIsPressed( false ),
	x( -1 ),
	y( -1 )
{}
void MouseServer::OnMouseMove( int x,int y )
{
	this->x = x;
	this->y = y;

	buffer.push( MouseEvent( MouseEvent::Move,x,y ) );
	if( buffer.size( ) > bufferSize )
	{
		buffer.pop( );
	}
}
void MouseServer::OnMouseLeave()
{
	isInWindow = false;
}
void MouseServer::OnMouseEnter()
{
	isInWindow = true;
}
void MouseServer::OnLeftPressed( int x,int y )
{
	leftIsPressed = true;

	buffer.push( MouseEvent( MouseEvent::LPress,x,y ) );
	if( buffer.size( ) > bufferSize )
	{
		buffer.pop( );
	}
}
void MouseServer::OnLeftReleased( int x,int y )
{
	leftIsPressed = false;

	buffer.push( MouseEvent( MouseEvent::LRelease,x,y ) );
	if( buffer.size( ) > bufferSize )
	{
		buffer.pop( );
	}
}
void MouseServer::OnRightPressed( int x,int y )
{
	rightIsPressed = true;

	buffer.push( MouseEvent( MouseEvent::RPress,x,y ) );
	if( buffer.size( ) > bufferSize )
	{
		buffer.pop( );
	}
}
void MouseServer::OnRightReleased( int x,int y )
{
	rightIsPressed = false;

	buffer.push( MouseEvent( MouseEvent::RRelease,x,y ) );
	if( buffer.size( ) > bufferSize )
	{
		buffer.pop( );
	}
}
void MouseServer::OnWheelUp( int x,int y )
{
	buffer.push( MouseEvent( MouseEvent::WheelUp,x,y ) );
	if( buffer.size( ) > bufferSize )
	{
		buffer.pop( );
	}

}
void MouseServer::OnWheelDown( int x,int y )
{
	buffer.push( MouseEvent( MouseEvent::WheelDown,x,y ) );
	if( buffer.size( ) > bufferSize )
	{
		buffer.pop( );
	}

}
bool MouseServer::IsInWindow() const
{
	return isInWindow;
}