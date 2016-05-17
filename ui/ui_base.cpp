#include "ui_base.h"
#include "../manager.h"
#include "../config.h"
extern float g_zmin;

DWORD UIBase::UIVertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;

void UIBase::Config()
{
}

void UIBase::PreRender( LPDIRECT3DDEVICE9 device )
{
	if( FAILED( D3DXCreateTextureFromFile(
		device, L"tex_alpha.png", &m_tex ) ) )
		exit(0);

	// ¶¥µã»º´æ
	if( FAILED( device->CreateVertexBuffer(
		c_vertex_size * sizeof( UIVertex ), 
		D3DUSAGE_SOFTWAREPROCESSING, 
		UIVertex::FVF, 
		D3DPOOL_DEFAULT, 
		&m_vb, 
		NULL
		) ) )
		return;

	UIVertex* verticies = NULL;
	UIVertex v_arr[c_vertex_size];
	v_arr[0] = UIVertex( -5.f, -5.f, 0.f, 0xffffffff, 0.f, 0.f );
	v_arr[1] = UIVertex( 5.f, 5.f, 0.f, 0xffffffff, 1.f, 1.f );
	v_arr[2] = UIVertex( -5.f, 5.f, 0.f, 0xffffffff, 0.f, 1.f );

	v_arr[3] = UIVertex( -5.f, -5.f, 0.f, 0xffffffff, 0.f, 0.f );
	v_arr[4] = UIVertex( 5.f, -5.f, 0.f, 0xffffffff, 1.f, 0.f );
	v_arr[5] = UIVertex( 5.f, 5.f, 0.f, 0xffffffff, 1.f, 1.f );

	m_vb->Lock( 0, 0, (void **) &verticies, 0 );
	memcpy( verticies, v_arr, c_vertex_size * sizeof( UIVertex ) );
	m_vb->Unlock();
}

void UIBase::Render( LPDIRECT3DDEVICE9 device )
{
	RecalMatrix();

	DWORD isLight;
	device->GetRenderState( D3DRS_LIGHTING, &isLight );
	device->SetRenderState( D3DRS_LIGHTING, false );

	device->SetTexture( 0, m_tex );
	device->SetStreamSource( 0, m_vb, 0, sizeof(UIVertex) );
	device->SetFVF( UIVertex::FVF );
	device->SetTransform( D3DTS_WORLD, &m_matrix );
	device->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 );

	device->SetRenderState( D3DRS_LIGHTING, isLight );
}

void UIBase::SetPos( float h_pos, float v_pos )
{
	m_h_pos = h_pos;
	m_v_pos = v_pos;
}

void UIBase::SetSize( float h_size, float v_size )
{
	m_h_size = h_size;
	m_v_size = v_size;
}

void UIBase::RecalMatrix()
{
	D3DXMATRIX t_mat;
	D3DXMatrixTranslation( &t_mat, 0, 0, g_zmin + 0.1f );
	const D3DXMATRIX* m_mat = ModelManager::GetInvCameraMatrix();

	D3DXMatrixMultiply( &m_matrix, &t_mat, m_mat );
}