#ifndef __MODEL_OBJECTS_SPRITE_SPRITE_MESH_H__
#define __MODEL_OBJECTS_SPRITE_SPRITE_MESH_H__

#include <d3dx9.h>
#include <d3dx9math.h>
#pragma comment(lib, "d3dx9.lib")

#include "render_interface/render_object_base.h"
#include "file_reader/data_section.h"
#include "file_reader/file_readee_base.h"

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

class SpriteMesh : public RenderObjectBase, public FileReadBase
{
public:
	SpriteMesh();
	SpriteMesh( DataSection* rootSec );
	~SpriteMesh();

	typedef SpriteVertex ModelVertexStruct;

	bool OnLoadByDataSection( DataSection* rootSec );

	virtual void Config(){}
	virtual void PreRender( LPDIRECT3DDEVICE9 device );
	virtual void Render( LPDIRECT3DDEVICE9 device );

private:
	LPDIRECT3DVERTEXBUFFER9 m_vb;
	LPDIRECT3DINDEXBUFFER9 m_ib;

	int m_vertex_size;
	ModelVertexStruct* m_vertex_arr;
};

#endif 