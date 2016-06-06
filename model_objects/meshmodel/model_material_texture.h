#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_OBJECTS_MESHMODEL_MODEL_MATERIAL_TEXTURE_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_OBJECTS_MESHMODEL_MODEL_MATERIAL_TEXTURE_H__

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include "model_objects/meshmodel/model_material.h"

struct MtlTexVertex;

class ModelWithMaterialTexture : public ModelWithMaterial
{
public:
	ModelWithMaterialTexture():m_ptex(NULL){};
	~ModelWithMaterialTexture(){
		if( m_ptex )
		{
			m_ptex->Release();
			m_ptex = NULL;
		}
	};

	virtual void Config();
	virtual void PreRender( LPDIRECT3DDEVICE9 device );
	virtual void Render( LPDIRECT3DDEVICE9 device );

protected:
	LPDIRECT3DTEXTURE9 m_ptex;
};

#endif 