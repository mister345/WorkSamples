/*************************************************************************************
* File:           Keyboard.cpp                                                       *
*                                                                                    *
* Author:         Gregory Weiner                                                     *
* Version:        1.0 8.21.2014                                                      *
* Last Modified:  11.17.2014                                                         *
* License:        Free Software (GNU License Included)                               *
* Purpose:        This is part of a DirectX 9 framework for powering Win32 graphics  *
*                 for 2D games. Many thanks to Chili and his excellent tutorials in  *
*                 game programming with C++ for making this possible.                *
*                                                                                    *
* Description:    Main keyboard input file for keypress and release event handling.  *
*                                                                                    *
* Requirements:   Latest Visual Studio C++ compiler recommended.                     *
*                 Requires a functioning keyboard for input.                         *
*                                                                                    *
**************************************************************************************/

#include "Keyboard.h"

KeyboardClient::KeyboardClient( KeyboardServer& kServer )
	: server( kServer )
{}

bool KeyboardClient::KeyIsPressed( unsigned char keycode ) const
{
	return server.keystates[ keycode ];
}

KeyEvent KeyboardClient::ReadKey()
{
	if( server.keybuffer.size() > 0 )
	{
KeyEvent e = server.keybuffer.front();
		server.keybuffer.pop();
        return e;
	}
	else
	{
		return KeyEvent(KeyEvent::Invalid, 0);
	}
}

KeyEvent KeyboardClient::PeekKey() const
{	
	if( server.keybuffer.size() > 0 )
	{
		return server.keybuffer.front();
	}
	else
	{
        return KeyEvent(KeyEvent::Invalid, 0);
    }
}

bool KeyboardClient::KeyEmpty() const
{
    return server.keybuffer.empty();
}

bool KeyboardClient::CharEmpty() const
{
    return server.charbuffer.empty();
}

unsigned char KeyboardClient::ReadChar()
{
	if( server.charbuffer.size() > 0 )
	{
		unsigned char charcode = server.charbuffer.front();
		server.charbuffer.pop();
		return charcode;
	}
	else
	{
		return 0;
	}
}

unsigned char KeyboardClient::PeekChar() const
{
	if( server.charbuffer.size() > 0 )
	{
		return server.charbuffer.front();
	}
	else
	{
		return 0;
	}
}

void KeyboardClient::FlushKeyBuffer()
{
	while( !server.keybuffer.empty() )
	{
		server.keybuffer.pop();
	}
}

void KeyboardClient::FlushCharBuffer()
{
	while( !server.charbuffer.empty() )
	{
		server.charbuffer.pop();
	}
}

void KeyboardClient::FlushBuffers()
{
	FlushKeyBuffer();
	FlushCharBuffer();
}

KeyboardServer::KeyboardServer()
{
	for( int x = 0; x < nKeys; x++ )
	{
		keystates[ x ] = false;
	}
}

void KeyboardServer::OnKeyPressed( unsigned char keycode )
{
	keystates[ keycode ] = true;
	
	keybuffer.push( KeyEvent(KeyEvent::Press, keycode) );
	if( keybuffer.size() > bufferSize )
	{
		keybuffer.pop();
	}
}

void KeyboardServer::OnKeyReleased( unsigned char keycode )
{
	keystates[ keycode ] = false;
    keybuffer.push(KeyEvent(KeyEvent::Release, keycode));
    if (keybuffer.size() > bufferSize)
    {
        keybuffer.pop();
    }
}

void KeyboardServer::OnChar( unsigned char character )
{
	charbuffer.push( character );
	if( charbuffer.size() > bufferSize )
	{
		charbuffer.pop();
	}
}

