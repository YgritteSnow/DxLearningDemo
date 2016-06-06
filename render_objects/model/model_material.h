#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__RENDER_OBJECTS_MODEL_MODEL_MATERIAL_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__RENDER_OBJECTS_MODEL_MODEL_MATERIAL_H__

#include "render_objects/model/model.h"

class ModelWithMaterial : public Model
{
public:
	ModelWithMaterial(){};
	virtual ~ModelWithMaterial();

	virtual void Config();
	virtual void Render( LPDIRECT3DDEVICE9 device );

protected:
	D3DMATERIAL9 m_mtl;
};

#endif 