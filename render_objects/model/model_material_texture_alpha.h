#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__RENDER_OBJECTS_MODEL_MODEL_MATERIAL_TEXTURE_ALPHA_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__RENDER_OBJECTS_MODEL_MODEL_MATERIAL_TEXTURE_ALPHA_H__

#include "render_objects/model/model_material_texture.h"

class ModelWithMaterialTextureAlpha : public ModelWithMaterialTexture
{
public:
	void Render( LPDIRECT3DDEVICE9 device );
};

#endif 