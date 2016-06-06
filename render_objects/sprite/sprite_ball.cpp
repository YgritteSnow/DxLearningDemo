#include "render_objects/sprite/sprite_ball.h"
#include "tool_funcs/tool_funcs.h"

bool FurryParticleSprite::Update( DWORD timeDelta )
{
	if( _isDead )
	{
		return false;
	}
	D3DXVECTOR3 pos_offset = m_speed * m_speed_scale * (timeDelta / 1000.f);
	m_position += pos_offset;
	_x += pos_offset.x;
	_y += pos_offset.y;
	_z += pos_offset.z;
	if( D3DXVec3Dot( &m_position, &m_position ) > m_radius )
	{
		_isDead = true;
		return true;
	}
	return false;
}

FurrySprite::~FurrySprite()
{
	delete [] m_vec_sprite[0];
	m_vec_sprite.clear();
	m_vec_sprite_dead.clear();
}

void FurrySprite::Config()
{
	m_vertex_size = 1;
	FurryParticleSprite* p_buf = new FurryParticleSprite[m_vertex_size];
	for( int i = 0; i < m_vertex_size; ++i )
	{
		AddSprite( p_buf + i );
	}

	m_pos = D3DXVECTOR3(0, 2, 0);
	m_radius = 5.f;
	m_speed = 0.2f;

	D3DXMatrixIdentity( &m_matrix );
}

void FurrySprite::OnResetSprites( DWORD timeDelta )
{
	static DWORD temp_t = 0;
	temp_t += timeDelta;
	if( temp_t > 1000 )
	{
		temp_t = 0;
		// 每过1秒，做点事儿
		for( int i = 0; i < 1; ++i )
		{
			FurryParticleSprite* new_sprite = dynamic_cast< FurryParticleSprite* >(SearchDeadSprite());
			if( !new_sprite )
			{
				break;
			}
			new_sprite->Reset( m_pos.x, m_pos.y, m_pos.z, 0xffff00ff, Tools::RandVector3(), Tools::RandVector3(), m_speed, m_radius );
		}
	}

	for( int i = 0; i < m_vertex_size; ++i )
	{
		// 时刻更新所有粒子
		if( m_vec_sprite[i]->Update( timeDelta ) )
		{
			m_vec_sprite_dead.push_back( m_vec_sprite[i] );
		}
	}
}

void FurrySprite::AddSprite( FurryParticleSprite* p_fsprite )
{
	m_vec_sprite.push_back( p_fsprite );
	if( p_fsprite->isDead() )
	{
		m_vec_sprite_dead.push_back( p_fsprite );
	}
}

ParticleSprite* FurrySprite::SearchDeadSprite()
{
	if( m_vec_sprite_dead.size() > 0 )
	{
		ParticleSprite* t = m_vec_sprite_dead.back();
		m_vec_sprite_dead.pop_back();
		return t;
	}
	else
	{
		return NULL;
	}
}