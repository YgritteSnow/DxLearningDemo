#ifndef __MODEL_OBJECTS_SPRITE_SPRITE_H__
#define __MODEL_OBJECTS_SPRITE_SPRITE_H__

#include <vector>
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include "model_objects/meshmodel/texture.h"
#include "model_objects/sprite/sprite_mesh.h"
#include "render_interface/update_base.h"
#include "file_reader/file_readee_base.h"

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

class Sprite : public UpdateBase, public FileReadBase
{
public:
	Sprite( const char* filename ):FileReadBase( filename ){};
	virtual ~Sprite(){};

	typedef SpriteVertex ModelVertexStruct;

	bool OnLoadByDataSection( DataSection* rootSec );

	virtual void PreRender( LPDIRECT3DDEVICE9 device );
	virtual void Render( LPDIRECT3DDEVICE9 device );
	virtual void Update( DWORD timeDelta );
	
	virtual void OnResetSprites( DWORD timeDelta ) = 0;

protected:
	std::vector< ParticleSprite* > m_vec_sprite;

	size_t m_sprite_capacity;
	size_t m_sprite_arraysize;

	int m_vertex_size;
	D3DXMATRIX m_matrix;

	ModelTexture m_ptex;
	SpriteMesh m_spirte_mesh;
};

#endif 