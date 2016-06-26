/*************************************************************************************
* File:           Mouse.cpp                                                          *
*                                                                                    *
* Author:         Gregory Weiner                                                     *
* Version:        1.0 8.21.2014                                                      *
* Last Modified:  11.17.2014                                                         *
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

MouseClient::MouseClient( const MouseServer& server )
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
}
void MouseServer::OnMouseLeave()
{
	isInWindow = false;
}
void MouseServer::OnMouseEnter()
{
	isInWindow = true;
}
void MouseServer::OnLeftPressed()
{
	leftIsPressed = true;
}
void MouseServer::OnLeftReleased()
{
	leftIsPressed = false;
}
void MouseServer::OnRightPressed()
{
	rightIsPressed = true;
}
void MouseServer::OnRightReleased()
{
	rightIsPressed = false;
}
bool MouseServer::IsInWindow() const
{
	return isInWindow;
}