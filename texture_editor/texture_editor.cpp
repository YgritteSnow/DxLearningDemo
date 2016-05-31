#include "texture_editor/texture_editor.h"
#include "d3d9.h"
#include <Windef.h>
#pragma comment(lib, "d3d9.lib")
#include "config/config.h"
#include <time.h>

void TextureEditor::PreRender( LPDIRECT3DDEVICE9 device )
{
	SetCurTextureByPath( L"tex2.png", device );
	Edit();
	RefreshDiaplay();
}

void TextureEditor::Render( LPDIRECT3DDEVICE9 device )
{

}

void TextureEditor::SetPlayBoard( TextureDiaplayBoard* pPlayBoard )
{
	m_textureDisplayer = pPlayBoard;
}

void TextureEditor::RefreshDiaplay()
{
	if( !m_textureDisplayer || !m_cur_pTexture )
	{
		return;
	}

	m_textureDisplayer->SetTexture( m_cur_pTexture );
}

inline DWORD PixelFun_sin_color( BYTE* pBits, int x, int y, int max_x, int max_y )
{
	return ( DWORD(rand()) << 16 | DWORD(rand()) );
}

void TextureEditor::Edit()
{
	if( !m_cur_pTexture )
	{
		return;
	}

	D3DLOCKED_RECT lock_rect;
	if( FAILED( m_cur_pTexture->LockRect(0, &lock_rect, NULL, 0 ) ) )
	{
		return;
	}

	int max_x = 1024;
	int max_y = 1024;
	BYTE* pBits = (BYTE*)lock_rect.pBits;
	BYTE* pOriginBits = pBits;
	srand((unsigned)time(0));
	for( int y = 0; y < max_y; ++y )
	{
		DWORD* start_bit = (DWORD*)pBits;
		pBits += lock_rect.Pitch;

		for( int x = 0; x < max_x; ++x )
		{
			*start_bit = PixelFun_sin_color( pOriginBits, x, y, max_x, max_y );
			start_bit ++ ;
		}
	}
	m_cur_pTexture->UnlockRect(0);
}

