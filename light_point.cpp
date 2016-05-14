#include "light_point.h"

void LightPoint::Config()
{
	m_pos = D3DXVECTOR3( 3.0f, 3.0f, 3.0f );

	ZeroMemory( &m_light, sizeof(m_light) );
	m_light.Type = D3DLIGHT_POINT;
	m_light.Position = m_pos;
	//m_light.Direction = D3DXVECTOR3( -1.f, -1.f, -1.f );
	m_light.Ambient = D3DXCOLOR( 0.2f, 0.2f, 0.2f, 1.0f );
	m_light.Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	m_light.Specular = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	m_light.Attenuation0 = 1.0f;
	//m_light.Falloff = 1.0f;
	m_light.Range = 10.f;

	m_sunmodel.Config();
}

void LightPoint::PreRender( LPDIRECT3DDEVICE9 device )
{
	Light::PreRender(device);
	//m_sunmodel.PreRender(device);
}

void LightPoint::Render( LPDIRECT3DDEVICE9 device )
{
	Light::Render(device);
	//m_sunmodel.Render(device);
}