#include "camera_simple_move.h"

void CameraSimpleMove::Config()
{
	m_eyepos = D3DXVECTOR3( 0.f, 0.f, -5.f );
	m_eyeypr = D3DXVECTOR3( 3.14f, 0.f, 0.f );
	D3DXMatrixTranslation( &m_viewMat, m_eyepos.x, m_eyepos.y, m_eyepos.z );
	D3DXMatrixRotationYawPitchRoll( &m_rotMat, m_eyeypr.x, m_eyeypr.y, m_eyeypr.z );
	D3DXMatrixMultiply( &m_viewMat, &m_viewMat, &m_rotMat );

	Camera::Config();
}
bool CameraSimpleMove::OnKeyMoveDown( int x, int y, int z )
{
	D3DXVECTOR3 t_transvec;
	D3DXVec3TransformNormal( &t_transvec, &(D3DXVECTOR3(0.f, 0.f, y * m_move_speed)), &m_viewMat );
	m_eyepos += t_transvec;

	m_eyeypr += D3DXVECTOR3( (float)x, 0, (float)z ) * m_move_speed;

	D3DXMatrixTranslation( &m_viewMat, m_eyepos.x, m_eyepos.y, m_eyepos.z );
	D3DXMatrixRotationYawPitchRoll( &m_rotMat, m_eyeypr.x, m_eyeypr.y, m_eyeypr.z );
	D3DXMatrixMultiply( &m_viewMat, &m_viewMat, &m_rotMat );

	return false;
}