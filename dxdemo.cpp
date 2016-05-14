#include <d3d9.h>
#pragma comment( lib, "d3d9.lib" )

#include "manager.h"

//#include <tchar.h>

#include "model.h"

LPDIRECT3D9 g_d3d = NULL;
LPDIRECT3DDEVICE9 g_d3ddevice = NULL;
ModelManager* g_mng = NULL;

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
	if( g_mng )
	{
		delete g_mng;
		g_mng = NULL;
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

	case WM_KEYDOWN:
		{
			switch( wParam )
			{
			case VK_ESCAPE:
				DestroyWindow( hwnd );
				break;

			default:
				g_mng->OnKeyDown( wParam );
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

INT WINAPI WinMain( HINSTANCE hinst, HINSTANCE, LPSTR cmdline, INT nCmd )
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
		800, 600, 600, 400, 
		NULL, NULL, hinst, 0
		);

	if( hwnd )
	{
		if( SUCCEEDED( InitD3d( hwnd ) ) )
		{
			g_mng = new ModelManager( g_d3ddevice );

			ShowWindow( hwnd, SW_SHOWDEFAULT );
			UpdateWindow( hwnd );
			g_mng->PreRender();

			MSG msg;
			while( GetMessage( &msg, NULL, NULL, NULL ) )
			{
				g_mng->Render();
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
	}

	UnregisterClass( L"classname", wc.hInstance );

	return 0;
}