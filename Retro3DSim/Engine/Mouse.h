/************************************************************************************************
* File:           Mouse.h                                                                       *
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

class Mouse
{
	friend class MainWindow;
public:
	class Event
	{
	public:
		enum Type
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Invalid
		};
	private:
		Type type;
		bool leftIsPressed;
		bool rightIsPressed;
		int x;
		int y;
	public:
		Event()
			:
			type( Invalid ),
			leftIsPressed( false ),
			rightIsPressed( false ),
			x( 0 ),
			y( 0 )
		{}
		Event( Type type,const Mouse& parent )
			:
			type( type ),
			leftIsPressed( parent.leftIsPressed ),
			rightIsPressed( parent.rightIsPressed ),
			x( parent.x ),
			y( parent.y )
		{}
		bool IsValid() const
		{
			return type != Invalid;
		}
		Type GetType() const
		{
			return type;
		}
		std::pair<int,int> GetPos() const
		{
			return{ x,y };
		}
		int GetPosX() const
		{
			return x;
		}
		int GetPosY() const
		{
			return y;
		}
		bool LeftIsPressed() const
		{
			return leftIsPressed;
		}
		bool RightIsPressed() const
		{
			return rightIsPressed;
		}
	};
public:
	Mouse() = default;
	Mouse( const Mouse& ) = delete;
	Mouse& operator=( const Mouse& ) = delete;
	std::pair<int,int> GetPos() const;
	int GetPosX() const;
	int GetPosY() const;
	bool LeftIsPressed() const;
	bool RightIsPressed() const;
	bool IsInWindow() const;
	Mouse::Event Read();
	bool IsEmpty() const
	{
		return buffer.empty();
	}
	void Flush();
private:
	void OnMouseMove( int x,int y );
	void OnMouseLeave();
	void OnMouseEnter();
	void OnLeftPressed( int x,int y );
	void OnLeftReleased( int x,int y );
	void OnRightPressed( int x,int y );
	void OnRightReleased( int x,int y );
	void OnWheelUp( int x,int y );
	void OnWheelDown( int x,int y );
	void TrimBuffer();
private:
	static constexpr unsigned int bufferSize = 4u;
	int x;
	int y;
	bool leftIsPressed = false;
	bool rightIsPressed = false;
	bool isInWindow = false;
	std::queue<Event> buffer;
};