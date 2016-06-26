/*************************************************************************************
* File:           Mouse.h                                                            *
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
#pragma once

class MouseServer;

class MouseClient
{
public:
	MouseClient( const MouseServer& server );
	int GetMouseX() const;
	int GetMouseY() const;
	bool LeftIsPressed() const;
	bool RightIsPressed() const;
	bool IsInWindow() const;
private:
	const MouseServer& server;
};

class MouseServer
{
	friend MouseClient;
public:
	MouseServer();
	void OnMouseMove( int x,int y );
	void OnMouseLeave();
	void OnMouseEnter();
	void OnLeftPressed();
	void OnLeftReleased();
	void OnRightPressed();
	void OnRightReleased();
	bool IsInWindow() const;
private:
	int x;
	int y;
	bool leftIsPressed;
	bool rightIsPressed;
	bool isInWindow;
};