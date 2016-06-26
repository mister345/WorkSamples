/****************************************************************************************
* File:           Windows.cpp                                                           *
*                                                                                       *
* Author:         Gregory Weiner                                                        *
* Version:        1.0 8.21.2014                                                         *
* Last Modified:  11.17.2014                                                            *
* License:        Free Software (GNU License Included)                                  *
* Purpose:        This is part of a DirectX 9 framework for powering Win32 graphics     *
*                 for 2D games. Many thanks to Chili and his excellent tutorials in     *
*                 game programming with C++ for making this possible.                   *
*                                                                                       *
* Description:    Contains WinMain function required by all Win32 applications to run.  *
*                 Handles system messages necessary for mouse and keyboard input via    *
*                 MsgProc; creates and registers main window, as well as instantiating  *
*                 main Game objet in wWinMain() function.                               *
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
			kServ.OnKeyPressed( wParam );
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
				if( x > 0 && x < SCREENWIDTH && y > 0 && y < SCREENHEIGHT )
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
						x = min( SCREENWIDTH-1,x );
						y = max( 0,y );
						y = min( SCREENHEIGHT-1,y );
						mServ.OnMouseMove( x,y );
					}
					else
					{
						ReleaseCapture();
						mServ.OnMouseLeave();
						mServ.OnLeftReleased();
						mServ.OnRightReleased();
					}
				}
			}
			break;
		case WM_LBUTTONDOWN:
			mServ.OnLeftPressed();
			break;
		case WM_RBUTTONDOWN:
			mServ.OnRightPressed();
			break;
		case WM_LBUTTONUP:
			mServ.OnLeftReleased();
			break;
		case WM_RBUTTONUP:
			mServ.OnRightReleased();
			break;
		// ************ END MOUSE MESSAGES ************ //
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

int WINAPI wWinMain( HINSTANCE hInst,HINSTANCE,LPWSTR,INT )
{
	WNDCLASSEX wc = { sizeof( WNDCLASSEX ),CS_CLASSDC,MsgProc,0,0,
                      GetModuleHandle( NULL ),NULL,NULL,NULL,NULL,
                      L"Platformer Window",NULL };
    wc.hIcon   = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
    RegisterClassEx( &wc );
	
	RECT wr;
	wr.left = 650;
	wr.right = SCREENWIDTH + wr.left;
	wr.top = 150;
	wr.bottom = SCREENHEIGHT + wr.top;
	AdjustWindowRect( &wr,WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,FALSE );
    HWND hWnd = CreateWindowW( L"Platformer Window",L"Platformer",
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
        else
		{
			theGame.Go();
		}
    }

    UnregisterClass( L"Platformer Window",wc.hInstance );

    return 0;
}