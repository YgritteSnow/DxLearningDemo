#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_MODEL_MATERIAL_TEXTURE_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_MODEL_MATERIAL_TEXTURE_H__

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include "model/model_material.h"

struct MtlTexVertex
{
	MtlTexVertex():_x(0), _y(0), _z(0), _nx(0), _ny(0), _nz(0), _color(0), _u(0), _v(0){}

	float _x, _y, _z;
	float _nx, _ny, _nz;
	DWORD _color;
	float _u, _v;
	static DWORD FVF;
};

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

private:
	LPDIRECT3DTEXTURE9 m_ptex;
};

#endif 