#include "sprite.h"

DWORD SpriteVertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
const static size_t c_render_size_of_sprite_at_one_shot = 1000;

Sprite::~Sprite()
{
}

void Sprite::Config()
{
	AddSprite( 0.f, 5.f, 0.f, 0xffff0000 );
}
void Sprite::PreRender( LPDIRECT3DDEVICE9 device )
{

}

void Sprite::Render( LPDIRECT3DDEVICE9 device )
{
	device->SetRenderState( D3DRS_LIGHTING, false );
	device->SetRenderState( D3DRS_POINTSPRITEENABLE, true );
	device->SetRenderState( D3DRS_POINTSCALEENABLE, true );
	float t = 3.0f;
	device->SetRenderState( D3DRS_POINTSIZE, *((DWORD*)&(t)) );
	device->SetFVF( ModelVertexStruct::FVF );
	device->SetStreamSource( 0, m_vb, 0, sizeof(ModelVertexStruct) );

	// 循环遍历拿到若干个活着的粒子，每次若干个，分成若干次渲染出来
	ModelVertexStruct vb[c_render_size_of_sprite_at_one_shot];
	size_t temp_size = 0;
	for( size_t i = 0; i < m_vec_sprite.size(); ++i )
	{
		if( m_vec_sprite_deadmark[i] )
		{
			continue;
		}

		if( temp_size % c_render_size_of_sprite_at_one_shot == 0 )
		{
			if( temp_size != 0 )
			{
				m_vb->Unlock();
				device->DrawPrimitive( D3DPT_POINTLIST, temp_size - c_render_size_of_sprite_at_one_shot, c_render_size_of_sprite_at_one_shot );
			}
			m_vb->Lock( 
				temp_size * sizeof( ModelVertexStruct ), 
				c_render_size_of_sprite_at_one_shot * sizeof( ModelVertexStruct ), 
				(void**)&vb, 
				(temp_size == 0) ? D3DLOCK_DISCARD : D3DLOCK_NOOVERWRITE
				);
		}
		size_t idx = temp_size % c_render_size_of_sprite_at_one_shot;
		
		vb[idx]._x = m_vec_sprite[i]._x;
		vb[idx]._y = m_vec_sprite[i]._y;
		vb[idx]._z = m_vec_sprite[i]._z;
		vb[idx]._color = m_vec_sprite[i]._color;

		++temp_size;
	}
	m_vb->Unlock();
	device->DrawPrimitive( D3DPT_POINTLIST, temp_size - (temp_size % c_render_size_of_sprite_at_one_shot), (temp_size % c_render_size_of_sprite_at_one_shot) );

	device->SetRenderState( D3DRS_POINTSPRITEENABLE, false );
	device->SetRenderState( D3DRS_LIGHTING, true );
}

void Sprite::AddSprite( float x, float y, float z, D3DCOLOR c )
{
	m_vec_sprite.push_back( ModelVertexStruct(x, y, z, c) );
}