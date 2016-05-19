#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_MATERIAL_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_MATERIAL_H__

#include "model.h"

class ModelWithMaterial : public Model 
{
public:
	ModelWithMaterial(){};
	virtual ~ModelWithMaterial();

	virtual void Config();
	virtual void Render( LPDIRECT3DDEVICE9 device );

private:
	D3DMATERIAL9 m_mtl;
};

 #endif 