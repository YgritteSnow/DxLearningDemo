#ifndef __MODEL_OBJECTS_MESHMODEL_TEXTURE_H__
#define __MODEL_OBJECTS_MESHMODEL_TEXTURE_H__

#include <d3dx9.h>
#include <d3dx9math.h>
#pragma comment(lib, "d3dx9.lib")

#include "render_interface/render_object_base.h"
#include "file_reader/data_section.h"
#include "file_reader/file_readee_base.h"

class ModelTexture : public RenderObjectBase, public FileReadBase
{
public:
	ModelTexture();
	ModelTexture( const char* filename );
	ModelTexture( DataSection* rootSec );
	~ModelTexture();

	bool OnLoadByDataSection( DataSection* rootSec );

	virtual void Config(){};
	virtual void PreRender( LPDIRECT3DDEVICE9 device ){};
	virtual void Render( LPDIRECT3DDEVICE9 device );

private:
	LPDIRECT3DTEXTURE9 m_ptex;
	D3DMATERIAL9 m_mtl;

	bool m_isSpecularEnable;
	bool m_isAlphaEnable;
};

#endif 