#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__TEXTURE_EDITOR_TEXTURE_EDITOR_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__TEXTURE_EDITOR_TEXTURE_EDITOR_H__

/************************************************************************/
/* ������ͼ�ľ�̬�Ĵ���Ȼ�����ɳ���̬����ͼ                           */
/************************************************************************/

#include <d3dx9.h>
#pragma comment( lib, "d3dx9.lib" )

#include "texture_editor/texture_display_board.h"
#include "render_object_base.h"

class TextureEditor : public RenderObjectBase
{
public:
	TextureEditor():m_textureDisplayer(NULL), m_cur_pTexture(NULL){}

	void SetPlayBoard( TextureDiaplayBoard* pPlayBoard );

	void SetCurTexture( LPDIRECT3DTEXTURE9 pTexture );
	void SetCurTextureByPath( LPCWSTR filepath, LPDIRECT3DDEVICE9 device )
	{
		if( FAILED( D3DXCreateTextureFromFile(
			device, filepath, &m_cur_pTexture ) ) )
			exit(0);
	}
	void GetTexture();
	void SaveTexture( const char* filepath );

	void RefreshDiaplay();
	
	virtual void Config(){};
	virtual void PreRender( LPDIRECT3DDEVICE9 device );
	virtual void Render( LPDIRECT3DDEVICE9 device );

	void Edit();

private:
	TextureDiaplayBoard* m_textureDisplayer;

	LPDIRECT3DTEXTURE9 m_cur_pTexture;
};

#endif 