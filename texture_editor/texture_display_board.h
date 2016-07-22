#ifndef __TEXTURE_EDITOR_TEXTURE_DISPLAY_BOARD_H__
#define __TEXTURE_EDITOR_TEXTURE_DISPLAY_BOARD_H__

#include "model_objects/ui/ui_base.h"

class TextureDiaplayBoard : public UIBase
{
public:
	virtual void SetTexture( LPDIRECT3DTEXTURE9 pTexture )
	{
		UIBase::SetTexture( pTexture );
	}
};

#endif 