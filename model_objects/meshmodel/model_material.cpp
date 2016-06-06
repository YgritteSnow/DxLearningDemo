#include "model_objects/meshmodel/model_material.h"

ModelWithMaterial::~ModelWithMaterial()
{

}

void ModelWithMaterial::Render( LPDIRECT3DDEVICE9 device )
{
	device->SetRenderState( D3DRS_SPECULARENABLE, true );
	device->SetMaterial( &m_mtl );
	Model::Render( device );
}

void ModelWithMaterial::Config()
{
	ZeroMemory( &m_mtl, sizeof(m_mtl) );
	m_mtl.Ambient = D3DXCOLOR( 1, 1, 1, 1.0f );
	m_mtl.Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	m_mtl.Specular = D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f );
	m_mtl.Emissive = D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f );
	m_mtl.Power = 1.f;

	Model::Config();
}