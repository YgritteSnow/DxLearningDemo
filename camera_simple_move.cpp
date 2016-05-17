#include "camera_simple_move.h"

void CameraSimpleMove::Config()
{
	m_move_speed = 0.05f;
	m_mouse_speed = 0.005f;

	m_eyepos = D3DXVECTOR3( 0.f, -2.f, 5.f );
	m_eyeypr = D3DXVECTOR3(0.f, 0.f, 0.f );
	ReCalViewMat();

	Camera::Config();
}

void CameraSimpleMove::ReCalViewMat()
{
	D3DXMatrixTranslation( &m_viewMat, m_eyepos.x, m_eyepos.y, m_eyepos.z );
	D3DXMatrixRotationYawPitchRoll( &m_rotMat, m_eyeypr.x, m_eyeypr.y, m_eyeypr.z );
	D3DXMatrixMultiply( &m_viewMat, &m_viewMat, &m_rotMat );

	D3DXMatrixInverse( &m_invViewMat, NULL, &m_viewMat );
}

bool CameraSimpleMove::OnKeyMoveDown( int x, int y, int z )
{
	D3DXVECTOR3 t_transvec = D3DXVECTOR3( (float)x, (float)z, (float)y ) * (-m_move_speed);
	D3DXVec3TransformNormal( &t_transvec, &t_transvec, &m_invViewMat );
	m_eyepos += t_transvec;
	ReCalViewMat();

	return false;
}

bool CameraSimpleMove::OnMouseDownMove( int x, int y )
{
	m_eyeypr += D3DXVECTOR3( (float)x, (float)y, 0.f ) * m_mouse_speed;
	ReCalViewMat();

	return false;
}