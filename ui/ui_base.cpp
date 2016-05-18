#include "ui_base.h"
#include "../manager.h"
#include "../config.h"
extern float g_zmin;

DWORD UIBase::UIVertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;

void UIBase::Config()
{
	SetSize(2.0f, 1.0f);
	SetPos(1.f, 1.0f);
}

void UIBase::PreRender( LPDIRECT3DDEVICE9 device )
{
	if( FAILED( D3DXCreateTextureFromFile(
		device, L"tex_alpha.png", &m_tex ) ) )
		exit(0);

	// 顶点缓存
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
	v_arr[0] = UIVertex( -1.0f, -1.0f, 1.0000f, 0xffffffff, 0.f, 0.f );
	v_arr[1] = UIVertex( 1.0f, 1.0f, 1.0000f, 0xffffffff, 1.f, 1.f );
	v_arr[2] = UIVertex( -1.0f, 1.0f, 1.0000f, 0xffffffff, 0.f, 1.f );

	v_arr[3] = UIVertex( -1.0f, -1.0f, 1.0000f, 0xffffffff, 0.f, 0.f );
	v_arr[4] = UIVertex( 1.0f, -1.0f, 1.0000f, 0xffffffff, 1.f, 0.f );
	v_arr[5] = UIVertex( 1.0f, 1.0f, 1.0000f, 0xffffffff, 1.f, 1.f );

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

	device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	//device->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );

	device->SetTexture( 0, m_tex );
	device->SetStreamSource( 0, m_vb, 0, sizeof(UIVertex) );
	device->SetFVF( UIVertex::FVF );
	device->SetTransform( D3DTS_WORLD, &m_matrix );
	device->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 );

	device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	//device->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
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

float UIBase::GetScaleH()
{
	float clip_size = m_h_size;
	switch( m_h_size_mode )
	{
	case PIXEL:
		clip_size = m_h_size / g_screen_pixel_width;
	}

	return clip_size * g_screen_real_width * 0.5f;
}

float UIBase::GetScaleV()
{
	float clip_size = m_v_size;
	switch( m_v_size_mode )
	{
	case PIXEL:
		clip_size = m_v_size / g_screen_pixel_height;
	}

	return clip_size * g_screen_real_height * 0.5f;
}

float UIBase::GetPosOffsetH()
{
	float clip_pos = m_h_pos;
	switch( m_h_pos_size_mode )
	{
	case PIXEL:
		clip_pos = m_h_size / g_screen_pixel_width;
	}

	return clip_pos * g_screen_real_width * 0.5f;
}

float UIBase::GetPosOffsetV()
{
	float clip_pos = m_v_pos;
	switch( m_v_pos_size_mode )
	{
	case PIXEL:
		clip_pos = m_v_size / g_screen_pixel_height;
	}

	return clip_pos * g_screen_real_height * 0.5f;
}

float UIBase::GetPosH()
{
	switch( m_h_pos_mode )
	{
	case LEFT:
		return GetPosOffsetH() - GetScaleH() * 0.5f;
	case RIGHT:
		return GetPosOffsetH() + GetScaleH() * 0.5f;
	case CENTER:
	default:
		return GetPosOffsetH();
	}
}

float UIBase::GetPosV()
{
	switch( m_v_pos_mode )
	{
	case LEFT:
		return GetPosOffsetV() - GetScaleV() * 0.5f;
	case RIGHT:
		return GetPosOffsetV() + GetScaleV() * 0.5f;
	case CENTER:
	default:
		return GetPosOffsetV();
	}
}

void UIBase::RecalMatrix()
{
	float t;
	t = GetScaleH();
	t = GetScaleV(); 
	t = GetPosOffsetH();
	t = GetPosOffsetV();
	t = GetPosH();
	t = GetPosV();

	const D3DXMATRIX* inv_view_mat = ModelManager::GetInvCameraMatrix();
	
	D3DXMATRIX trans_mat;

	//第一种，平移一丢丢
	D3DXMatrixTranslation( &trans_mat, 0.f, 0.f, 0.1f );
	
	//第二种，自己做个投影矩阵。。。
	//D3DXMatrixIdentity( &trans_mat );
	//trans_mat._33 = 1.1f;
	//trans_mat._34 = 1.f;
	//trans_mat._43 = 0.0f;
	//trans_mat._44 = 0.0f;

	//第三种，用函数做投影矩阵。。。
	//D3DXMatrixOrthoLH( &trans_mat, g_screen_real_width * 0.9f, g_screen_real_height * 0.9f, 1 + 0.01f, 1 );
	//D3DXMatrixInverse( &trans_mat, NULL, &trans_mat );

	D3DXMatrixMultiply( &m_matrix, &trans_mat, inv_view_mat );


}