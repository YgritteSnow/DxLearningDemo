#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_OBJECTS_SPRITE_SPRITE_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_OBJECTS_SPRITE_SPRITE_H__

#include <vector>
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include "model_objects/meshmodel/model_material_texture.h"
#include "render_interface/update_base.h"

struct SpriteVertex
{
	SpriteVertex( float x, float y, float z, D3DCOLOR c )
		:_x(x), _y(y), _z(z), _color(c){}
	SpriteVertex()
		:_x(0.f), _y(0.f), _z(0.f), _color(0){}

	float _x, _y, _z;
	D3DCOLOR _color;
	//float _size;
	static DWORD FVF;
};

class ParticleSprite : public SpriteVertex
{
public:
	ParticleSprite( float x, float y, float z, D3DCOLOR c )
		: SpriteVertex( x, y, z, c )
		, _isDead(true){};

	bool isDead(){ return _isDead; }
	bool SetIsDead( bool isDead ){ _isDead = isDead; }
	virtual bool Update( DWORD timeDelta ){ return false; };
protected:
	bool _isDead;
};

class Sprite : public ModelWithMaterialTexture, public UpdateBase
{
public:
	Sprite():m_sprite_capacity(0), m_sprite_arraysize(0){};
	virtual ~Sprite(){};

	typedef SpriteVertex ModelVertexStruct;

	virtual void Config() = 0;
	virtual void PreRender( LPDIRECT3DDEVICE9 device );
	virtual void Render( LPDIRECT3DDEVICE9 device );
	virtual void Update( DWORD timeDelta );
	
	virtual void OnResetSprites( DWORD timeDelta ) = 0;

protected:
	std::vector< ParticleSprite* > m_vec_sprite;

	size_t m_sprite_capacity;
	size_t m_sprite_arraysize;
};

#endif 