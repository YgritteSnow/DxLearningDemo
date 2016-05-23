#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__SPRITE_SPRITE_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__SPRITE_SPRITE_H__

#include <vector>
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include "model/model.h"
#include "update_base.h"

struct SpriteVertex
{
	SpriteVertex( float x, float y, float z, D3DCOLOR c )
		:_x(x), _y(y), _z(z), _color(c){}
	SpriteVertex()
		:_x(0.f), _y(0.f), _z(0.f), _color(0){}

	float _x, _y, _z;
	D3DCOLOR _color;
	static DWORD FVF;
};

class Sprite : public Model< SpriteVertex >
{
public:
	Sprite():m_sprite_capacity(0), m_sprite_arraysize(0){};
	virtual ~Sprite();

	virtual void Config();
	virtual void PreRender( LPDIRECT3DDEVICE9 device );
	virtual void Render( LPDIRECT3DDEVICE9 device );
	
	virtual void AddSprite( float x, float y, float z, D3DCOLOR c );

protected:
	std::vector< ModelVertexStruct > m_vec_sprite;
	std::vector< bool > m_vec_sprite_deadmark;
	size_t m_sprite_capacity;
	size_t m_sprite_arraysize;
};

#endif 