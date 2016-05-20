#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__TEXTURE_EDITOR_TEXTURE_DISPLAY_BOARD_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__TEXTURE_EDITOR_TEXTURE_DISPLAY_BOARD_H__

#include "ui/ui_base.h"

class TextureDiaplayBoard : public UIBase
{
public:
	virtual void SetTexture( LPDIRECT3DTEXTURE9 pTexture )
	{
		UIBase::SetTexture( pTexture );
	}
};


 #endif 