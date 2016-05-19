#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__TEXTURE_EDITOR_TEXTURE_EDITOR_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__TEXTURE_EDITOR_TEXTURE_EDITOR_H__

/************************************************************************/
/* 用于贴图的静态的处理，然后生成出静态的贴图                           */
/************************************************************************/

#include <d3dx9.h>
#pragma comment( lib, "d3dx9.lib" )

#include "texture_display_board.h"

class TextureEditor
{
public:
	void SetCurTexture( LPDIRECT3DTEXTURE9 pTexture );
	void SetCurTextureByPath( LPCTSTR filepath, LPDIRECT3DDEVICE9 device )
	{
		if( FAILED( D3DXCreateTextureFromFile(
			device, filepath, &m_cur_pTexture ) ) )
			exit(0);
	}
	void GetTexture();

	void RefreshDiaplay();

private:
	TextureDiaplayBoard m_textureDisplayer;

	LPDIRECT3DTEXTURE9 m_cur_pTexture;
};


 #endif 