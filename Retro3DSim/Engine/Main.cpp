/************************************************************************************************
* File:           Main.cpp                                                                      *
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

#include "MainWindow.h"
#include "Game.h"
#include "CustomException.h"

int WINAPI wWinMain( HINSTANCE hInst,HINSTANCE,LPWSTR pArgs,INT )
{
	try
	{
		MainWindow wnd( hInst,pArgs );		
		try
		{
			Game theGame( wnd );
			while( wnd.ProcessMessage() )
			{
				theGame.Go();
			}
		}
		catch( const CustomException& e )
		{
			const std::wstring eMsg = e.GetFullMessage() + 
				L"\n\nException caught at Windows message loop.";
			wnd.ShowMessageBox( e.GetExceptionType(),eMsg );
		}
		catch( const std::exception& e )
		{
			// need to convert std::exception what() string from narrow to wide string
			const std::string whatStr( e.what() );
			const std::wstring eMsg = std::wstring( whatStr.begin(),whatStr.end() ) + 
				L"\n\nException caught at Windows message loop.";
			wnd.ShowMessageBox( L"Unhandled STL Exception",eMsg );
		}
		catch( ... )
		{
			wnd.ShowMessageBox( L"Unhandled Non-STL Exception",
				L"\n\nException caught at Windows message loop." );
		}
	}
	catch( const CustomException& e )
	{
		const std::wstring eMsg = e.GetFullMessage() +
			L"\n\nException caught at main window creation.";
		MessageBox( nullptr,eMsg.c_str(),e.GetExceptionType().c_str(),MB_OK );
	}
	catch( ... )
	{
		MessageBox( nullptr,L"\n\nException caught in Windows creation.",
			L"Unhandled Non-STL Exception",MB_OK );
	}

	return 0;
}