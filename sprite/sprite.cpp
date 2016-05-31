#include "sprite.h"
#include "tool_funcs.h"

DWORD SpriteVertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE ;
const static size_t c_render_size_of_sprite_at_one_shot = 1000;

#define TEX_FILE_PATH L"tex_alpha.png"

void Sprite::PreRender( LPDIRECT3DDEVICE9 device )
{
	// 顶点缓存
	if( FAILED( device->CreateVertexBuffer(
		m_vertex_size * sizeof( ModelVertexStruct ), 
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY, 
		ModelVertexStruct::FVF, 
		D3DPOOL_DEFAULT, 
		&m_vb, 
		NULL
		) ) )
		return;

	if( FAILED( D3DXCreateTextureFromFile(
		device, TEX_FILE_PATH, &m_ptex ) ) )
		exit(0);

	ZeroMemory( &m_mtl, sizeof(m_mtl) );
	m_mtl.Ambient = D3DXCOLOR( 1, 1, 1, 1.0f );
	m_mtl.Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	m_mtl.Specular = D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f );
	m_mtl.Emissive = D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f );
	m_mtl.Power = 1.f;

	return;
}

void Sprite::Render( LPDIRECT3DDEVICE9 device )
{
	device->SetRenderState( D3DRS_LIGHTING, false );
	device->SetRenderState( D3DRS_POINTSPRITEENABLE, true );
	device->SetRenderState( D3DRS_POINTSCALEENABLE, true );
	device->SetRenderState( D3DRS_POINTSCALE_A, Tools::FtoD(0.0f));
	device->SetRenderState( D3DRS_POINTSCALE_B, Tools::FtoD(0.0f));
	device->SetRenderState( D3DRS_POINTSCALE_C, Tools::FtoD(1.0f));
	float t = 1.0f;
	device->SetRenderState( D3DRS_POINTSIZE, *((DWORD*)&(t)) );
	device->SetFVF( ModelVertexStruct::FVF );
	device->SetStreamSource( 0, m_vb, 0, sizeof(ModelVertexStruct) );
	device->SetTexture( 0, m_ptex );
	device->SetMaterial( &m_mtl );

	device->SetTransform( D3DTS_WORLD, &m_matrix );
	//debug
	ModelVertexStruct vb[1];
	m_vb->Lock( 
		0, 
		1 * sizeof( ModelVertexStruct ), 
		(void**)&vb, 
		D3DLOCK_DISCARD 
		);
	vb[0]._x = 1.1f;
	vb[0]._y = 5.1f;
	vb[0]._z = 0.1f;
	vb[0]._color = 0xff0000ff;
	m_vb->Unlock();
	device->DrawPrimitive( D3DPT_POINTLIST, 0, 1 );


	// 循环遍历拿到若干个活着的粒子，每次若干个，分成若干次渲染出来
	//ModelVertexStruct vb[c_render_size_of_sprite_at_one_shot];
	//size_t temp_size;
	//temp_size = 0;
	//for( size_t i = 0; i < m_vec_sprite.size(); ++i )
	//{
	//	if( m_vec_sprite[i]->isDead() )
	//	{
	//		continue;
	//	}

	//	if( temp_size % c_render_size_of_sprite_at_one_shot == 0 )
	//	{
	//		if( temp_size != 0 )
	//		{
	//			m_vb->Unlock();
	//			device->DrawPrimitive( D3DPT_POINTLIST, temp_size - c_render_size_of_sprite_at_one_shot, c_render_size_of_sprite_at_one_shot );
	//		}
	//		m_vb->Lock( 
	//			temp_size * sizeof( ModelVertexStruct ), 
	//			c_render_size_of_sprite_at_one_shot * sizeof( ModelVertexStruct ), 
	//			(void**)&vb, 
	//			(temp_size == 0) ? D3DLOCK_DISCARD : D3DLOCK_NOOVERWRITE
	//			);
	//	}
	//	size_t idx = temp_size % c_render_size_of_sprite_at_one_shot;
	//	
	//	vb[idx]._x = m_vec_sprite[i]->_x;
	//	vb[idx]._y = m_vec_sprite[i]->_y;
	//	vb[idx]._z = m_vec_sprite[i]->_z;
	//	vb[idx]._color = m_vec_sprite[i]->_color;
	//	//vb[idx]._size = 100.f;

	//	++temp_size;
	//}
	//m_vb->Unlock();
	//device->DrawPrimitive( D3DPT_POINTLIST, temp_size - (temp_size % c_render_size_of_sprite_at_one_shot), (temp_size % c_render_size_of_sprite_at_one_shot) );

	device->SetRenderState( D3DRS_POINTSPRITEENABLE, false );
	device->SetRenderState( D3DRS_POINTSCALEENABLE, false );
	device->SetRenderState( D3DRS_LIGHTING, true );
}

void Sprite::Update( DWORD timeDelta )
{
	OnResetSprites( timeDelta );
}