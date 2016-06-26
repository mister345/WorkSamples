/****************************************************************************************
* File:           Windows.cpp                                                           *
*                                                                                       *
* Author:         Gregory Weiner                                                        *
* Version:        2.0 6.24.2015                                                         *
* Last Modified:  10.11.2015                                                            *
* License:        Free Software (GNU License Included)                                  *
* Purpose:        This is part of a DirectX 9 framework for powering Win32 graphics     *
*                 for 2D games. Many thanks to Chili and his excellent tutorials in     *
*                 game programming with C++ for making this possible.                   *
*                                                                                       *
* Description:    Contains WinMain function required by all Win32 applications to run.  *
*                 Handles system messages necessary for mouse and keyboard input via    *
*                 MsgProc; creates and registers main window, as well as instantiating  *
*                 main Game object in wWinMain() function.                              *
*                                                                                       *
* Requirements:   Latest Visual Studio C++ compiler recommended.                        *
*                 Requires a functioning keyboard for input.                            *
*                 Runs in windowed mode.                                                *
*                                                                                       *
*****************************************************************************************/
#include <Windows.h>
#include <wchar.h>
#include "D3DGraphics.h"
#include "Game.h"
#include "Mouse.h"

static KeyboardServer kServ;
static MouseServer mServ;

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

		// ************ KEYBOARD MESSAGES ************ //
		case WM_KEYDOWN:
			if( !( lParam & 0x40000000 ) ) // no thank you on the autorepeat
			{
				kServ.OnKeyPressed( wParam );
			}
			break;
		case WM_KEYUP:
   			kServ.OnKeyReleased( wParam );
			break;
		case WM_CHAR:
			kServ.OnChar( wParam );
			break;
		// ************ END KEYBOARD MESSAGES ************ //

		// ************ MOUSE MESSAGES ************ //
		case WM_MOUSEMOVE:
		{
			int x = (short)LOWORD( lParam );
			int y = (short)HIWORD( lParam );
			if( x > 0 && x < D3DGraphics::SCREENWIDTH && y > 0 && y < D3DGraphics::SCREENHEIGHT )
			{
				mServ.OnMouseMove( x,y );
				if( !mServ.IsInWindow() )
				{
					SetCapture( hWnd );
					mServ.OnMouseEnter();
				}
			}
			else
			{
				if( wParam & (MK_LBUTTON | MK_RBUTTON) )
				{
					x = max( 0,x );
					x = min( D3DGraphics::SCREENWIDTH - 1,x );
					y = max( 0,y );
					y = min( D3DGraphics::SCREENHEIGHT - 1,y );
					mServ.OnMouseMove( x,y );
				}
				else
				{
					ReleaseCapture();
					mServ.OnMouseLeave();
					mServ.OnLeftReleased( x,y );
					mServ.OnRightReleased( x,y );
				}
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			int x = (short)LOWORD( lParam );
			int y = (short)HIWORD( lParam );
			mServ.OnLeftPressed( x,y );
			break;
		}
		case WM_RBUTTONDOWN:
		{
			int x = (short)LOWORD( lParam );
			int y = (short)HIWORD( lParam );
			mServ.OnRightPressed( x,y );
			break;
		}
		case WM_LBUTTONUP:
		{
			int x = (short)LOWORD( lParam );
			int y = (short)HIWORD( lParam );
			mServ.OnLeftReleased( x,y );
			break;
		}
		case WM_RBUTTONUP:
		{
			int x = (short)LOWORD( lParam );
			int y = (short)HIWORD( lParam );
			mServ.OnRightReleased( x,y );
			break;
		}
		case WM_MOUSEWHEEL:
		{
			int x = (short)LOWORD( lParam );
			int y = (short)HIWORD( lParam );
			if( GET_WHEEL_DELTA_WPARAM( wParam ) > 0 )
			{
				mServ.OnWheelUp( x,y );
			}
			else if( GET_WHEEL_DELTA_WPARAM( wParam ) < 0 )
			{
				mServ.OnWheelDown( x,y );
			}
			break;
		}
		// ************ END MOUSE MESSAGES ************ //
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

int WINAPI wWinMain( HINSTANCE hInst,HINSTANCE,LPWSTR,INT )
{
	WNDCLASSEX wc = { sizeof( WNDCLASSEX ),CS_CLASSDC,MsgProc,0,0,
                      GetModuleHandle( NULL ),NULL,NULL,NULL,NULL,
                      L"ZeroG",NULL };
	wc.hIcon   = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor( NULL,IDC_ARROW );
    RegisterClassEx( &wc );
	
	RECT wr;
	wr.left = 650;
	wr.right = D3DGraphics::SCREENWIDTH + wr.left;
	wr.top = 150;
	wr.bottom = D3DGraphics::SCREENHEIGHT + wr.top;
	AdjustWindowRect( &wr,WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,FALSE );
    HWND hWnd = CreateWindowW( L"ZeroG",L"ZeroG",
                              WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,wr.left,wr.top,wr.right-wr.left,wr.bottom-wr.top,
                              NULL,NULL,wc.hInstance,NULL );

    ShowWindow( hWnd,SW_SHOWDEFAULT );
    UpdateWindow( hWnd );

	Game theGame( hWnd,kServ,mServ );
	
    MSG msg;
    ZeroMemory( &msg,sizeof( msg ) );
    while( msg.message != WM_QUIT )
    {
        if( PeekMessage( &msg,NULL,0,0,PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        //else
		{
			theGame.Go();
		}
    }

    UnregisterClass( L"ZeroG",wc.hInstance );
    return 0;
}