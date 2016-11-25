/************************************************************************************************
* File:           Keyboard.h                                                                      *
*                                                                                               *
* Author:         Gregory Weiner                                                                *
* Version:        1.0 10.15.2015                                                                *
* Last Modified:  2.2.2016                                                                      *
* License:        Free Software (GNU License Included)                                          *
* Purpose:        This is a Windows desktop application designed to render simple wireframe     *
*				  shapes and apply the appropriate transformations to display them on screen    * 
*				  with the illusion of real life perspective. It was created primarily to       *
*				  brush up pn core concepts of linear algebra, matrix math, and 3D simulation.  *
*                                                                                               *
* Description:    In the current implementation, only a tetrahedron, the simplest 3D polyhedron * 
*				  possible, can be rendered. The simple PutPixel function was based on the chili* 
*				  framework, for placing a single pixel of a specified RGB color at a given     *  
*				  coordinate in screen space. Everything else has been hand coded on top of this*  
*				  simple function. Because this is not taking advantage of DirectX's true       * 
*				  rendering capabilities, not surprisingly, it runs incredibly slow and is not  * 
*				  suited for creating a graphics intensive 3D game. However, it is useful to    * 
*				  show the inner workings of 3D rendering.										*
*																								*
* Input(keyboard):          																	*
*				  END - stop / reset rotation													*
*			      SPACE - accelerate rotation													*
*				  CTRL - decelerate rotation													*
*				  UP/DOWN - pitch																*
*				  LEFT/RIGHT- yaw																*
*				  Q/E - roll																	*
*				  S/W - change distance between 'lens' and screen								*
*				  U/T - change distance between polyhedron and screen							*
*				  G/J - move polyhedron right/left												*
*				  Y/H - move polyhedron up/down													*
*				  ESC - exit			  														*			    					    
*                                                                                               *
* Requirements:   Windows 10, Latest Visual C++ compiler recommended.                           *    	    
*                 Requires a functioning keyboard for input.    							    *
*                                                                                               *
*************************************************************************************************/

#pragma once
#include <queue>
#include <bitset>

class Keyboard
{
	friend class MainWindow;
public:
	class Event
	{
	public:
		enum Type
		{
			Press,
			Release,
			Invalid
		};
	private:
		Type type;
		unsigned char code;
	public:
		Event()
			:
			type( Invalid ),
			code( 0u )
		{}
		Event( Type type,unsigned char code )
			:
			type( type ),
			code( code )
		{}
		bool IsPress() const
		{
			return type == Press;
		}
		bool IsRelease() const
		{
			return type == Release;
		}
		bool IsValid() const
		{
			return type != Invalid;
		}
		unsigned char GetCode() const
		{
			return code;
		}
	};
public:
	Keyboard() = default;
	Keyboard( const Keyboard& ) = delete;
	Keyboard& operator=( const Keyboard& ) = delete;
	bool KeyIsPressed( unsigned char keycode ) const;
	Event ReadKey();
	bool KeyIsEmpty() const;
	unsigned char ReadChar();
	bool CharIsEmpty() const;
	void FlushKey();
	void FlushChar();
	void Flush();
	void EnableAutorepeat();
	void DisableAutorepeat();
	bool AutorepeatIsEnabled() const;
private:
	void OnKeyPressed( unsigned char keycode );
	void OnKeyReleased( unsigned char keycode );
	void OnChar( unsigned char character );
	template<typename T>
	void TrimBuffer( std::queue<T>& buffer );
private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 4u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keystates;
	std::queue<Event> keybuffer;
	std::queue<unsigned char> charbuffer;
};