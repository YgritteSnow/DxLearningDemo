#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__RENDER_OBJECTS_SPRITE_SPRITE_BALL_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__RENDER_OBJECTS_SPRITE_SPRITE_BALL_H__

/************************************************************************/
/* ���м������ܷ�ɢ�����ӣ�����ʱ�����β                               */
/************************************************************************/

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")
#include "render_objects/sprite/sprite.h"

class FurryParticleSprite : public ParticleSprite
{
public:
	FurryParticleSprite():m_speed_scale(1.f), m_radius(1.f), ParticleSprite(0.f, 0.f, 0.f, 0xffffffff){}

	virtual bool Update( DWORD timeDelta );
	void Reset( float x, float y, float z, D3DCOLOR color, const D3DXVECTOR3& pos_offset, const D3DXVECTOR3& speed, float speed_scale, float radius )
	{
		_x = x;
		_y = y;
		_z = z;
		_color = color;
		m_speed = speed;
		m_position = pos_offset;
		m_speed_scale = speed_scale;
		m_radius = radius;
		_isDead = false;
	}

protected:
	D3DXVECTOR3 m_speed;
	D3DXVECTOR3 m_position;
	float m_speed_scale;
	float m_radius;
};

class FurrySprite : public Sprite
{
public:
	virtual ~FurrySprite();
	void Config();
	void OnResetSprites( DWORD timeDelta );

private:
	void AddSprite( FurryParticleSprite* p_fsprite );
	ParticleSprite* SearchDeadSprite();

	D3DXVECTOR3 m_pos;
	float m_radius;
	float m_speed;

	std::vector< ParticleSprite* > m_vec_sprite_dead; // �����洢�Ѿ������˵����ӵ�ָ�룬����ֱ��ʹ�����������и���
};

#endif 