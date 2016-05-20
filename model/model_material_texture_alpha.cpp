#include "model/model_material_texture_alpha.h"

void ModelWithMaterialTextureAlpha::Render( LPDIRECT3DDEVICE9 device )
{
	device->SetRenderState( D3DRS_ALPHABLENDENABLE, true );

	device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	device->SetTextureStageState( 0, D3DTSS_ALPHAARG0, D3DTA_TEXTURE );
	device->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );

	ModelWithMaterialTexture::Render(device);
	device->SetRenderState( D3DRS_ALPHABLENDENABLE, false );
}