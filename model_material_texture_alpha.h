#ifndef __MODEL_MATERIAL_TEXTURE_ALPHA_H__
#define __MODEL_MATERIAL_TEXTURE_ALPHA_H__

#include "model_material_texture.h"

class ModelWithMaterialTextureAlpha : public ModelWithMaterialTexture
{
public:
	void Render( LPDIRECT3DDEVICE9 device );
};

#endif