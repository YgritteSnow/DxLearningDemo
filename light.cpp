#include "light.h"

Light::~Light()
{

}

void Light::Config()
{
	ZeroMemory( &m_light, sizeof(m_light) );
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Direction = D3DXVECTOR3( -1.f, -1.f, -1.f );
	m_light.Ambient = D3DXCOLOR( 0.2f, 0.2f, 0.2f, 1.0f );
	m_light.Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	m_light.Specular = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
}

void Light::PreRender( LPDIRECT3DDEVICE9 device )
{
	device->SetRenderState( D3DRS_LIGHTING, true );
	device->SetLight(0, &m_light);
	device->LightEnable(0, true);
}

void Light::Render( LPDIRECT3DDEVICE9 device )
{

}