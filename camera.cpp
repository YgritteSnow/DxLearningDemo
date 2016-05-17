#include "camera.h"
#include "config.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

void Camera::Config()
{
	D3DXMatrixPerspectiveFovLH( &m_projMat, g_fov, g_aspect, g_zmin, g_zmax );
}

void Camera::PreRender( LPDIRECT3DDEVICE9 device )
{
	device->SetTransform( D3DTS_PROJECTION, &m_projMat );
	D3DVIEWPORT9 vp = { 0, 0, g_screen_pixel_width, g_screen_pixel_height, 0, 1 };
	device->SetViewport( &vp );
}

void Camera::Render( LPDIRECT3DDEVICE9 device )
{
	device->SetTransform( D3DTS_VIEW, &m_viewMat );
}

bool Camera::OnKeyMoveDown( int x, int y, int z )
{
	return false;
}

bool Camera::OnKeyDown( WPARAM wParam )
{
	bool ret = false;
	switch( wParam )
	{
	case 'A':
		ret = OnKeyMoveDown(-1, 0, 0);
		break;
	case 'D':
		ret = OnKeyMoveDown(1, 0, 0);
		break;
	case 'Q':
		ret = OnKeyMoveDown(0, 1, 0);
		break;
	case 'E':
		ret = OnKeyMoveDown(0, -1, 0);
		break;
	case 'W':
		ret = OnKeyMoveDown(0, 0, 1);
		break;
	case 'S':
		ret = OnKeyMoveDown(0, 0, -1);
		break;
	}
	return ret;
}