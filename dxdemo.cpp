#include <d3d9.h>
#pragma comment( lib, "d3d9.lib" )

#include "render_interface/manager.h"
#include "config/config.h"
#include "game_manager.h"

#include "model_objects/meshmodel/model.h"

LPDIRECT3D9 g_d3d = NULL;
LPDIRECT3DDEVICE9 g_d3ddevice = NULL;

void Render()
{
}

void Clear()
{
	if( g_d3d )
	{
		g_d3d->Release();
		g_d3d = NULL;
	}
	if( g_d3ddevice )
	{
		g_d3ddevice->Release();
		g_d3d = NULL;
	}
}

HRESULT InitD3d( HWND hwnd )
{
	g_d3d = Direct3DCreate9( D3D_SDK_VERSION );
	if( !g_d3d )
		return E_FAIL;

	D3DPRESENT_PARAMETERS dp;
	ZeroMemory( &dp, sizeof(dp) );
	dp.Windowed = true;
	dp.BackBufferFormat = D3DFMT_UNKNOWN;
	dp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	dp.EnableAutoDepthStencil = TRUE;
	dp.AutoDepthStencilFormat = D3DFMT_D16;

	if( FAILED( g_d3d->CreateDevice(
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, 
		hwnd, 
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
		&dp, 
		&g_d3ddevice
		) ) )
		return E_FAIL;

	return S_OK;
}

LRESULT CALLBACK MyWinProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_PAINT:
		break;

	case WM_LBUTTONDOWN:
		GameManager::GetGameManager().HandleLeftMouseButton( true );
		break;

	case WM_LBUTTONUP:
		GameManager::GetGameManager().HandleLeftMouseButton( false );
		break;

	case WM_MOUSEMOVE:
		GameManager::GetGameManager().HandleMouseMove( LOWORD( lParam ), HIWORD( lParam ) );
		break;

	case WM_KEYDOWN:
		{
			switch( wParam )
			{
			case VK_ESCAPE:
				DestroyWindow( hwnd );
				break;

			default:
				GameManager::GetGameManager().OnKeyDown( wParam );
			}
		}
		break;

	case WM_DESTROY:
		Clear();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc( hwnd, msg, wParam, lParam );
}

#if USE_DEBUG
INT WINAPI ygritte_WinMain( HINSTANCE hinst, HINSTANCE, LPSTR cmdline, INT nCmd )
#else
INT WINAPI WinMain( HINSTANCE hinst, HINSTANCE, LPSTR cmdline, INT nCmd )
#endif
{
	WNDCLASSEX wc = {
		sizeof( WNDCLASSEX ), 
		CS_CLASSDC, 
		MyWinProc, 
		0, 0, 
		hinst, 
		NULL, NULL, NULL, NULL, 
		L"classname", 
		NULL
	};
	RegisterClassEx( &wc );

	HWND hwnd = CreateWindow(
		L"classname", 
		L"caption?...", 
		WS_OVERLAPPEDWINDOW, 
		800, 400, g_screen_pixel_width, g_screen_pixel_height, 
		NULL, NULL, hinst, 0
		);

	if( hwnd )
	{
		if( SUCCEEDED( InitD3d( hwnd ) ) )
		{
			ShowWindow( hwnd, SW_SHOWDEFAULT );
			UpdateWindow( hwnd );
			GameManager::GetGameManager().PreRender();

			MSG msg;
			ZeroMemory( &msg, sizeof(msg));

			while( msg.message != WM_QUIT )
			if( PeekMessage( &msg, NULL, NULL, NULL, PM_REMOVE ) )
			{

				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			else
			{
				GameManager::GetGameManager().Render();
				GameManager::GetGameManager().Update();
			}
		}
	}

	UnregisterClass( L"classname", wc.hInstance );

	return 0;
}