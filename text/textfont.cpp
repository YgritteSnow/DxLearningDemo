#include "text/textfont.h"

FontText::FontText()
	: m_font(NULL)
{
}

FontText::~FontText()
{
	if( m_font )
	{
		m_font->Release();
		m_font = NULL;
	}
}

void FontText::Config()
{
	m_str = "ÃÈÃÈßÕ\nÀ²À²À²À²";
}

void FontText::PreRender( LPDIRECT3DDEVICE9 device )
{
	D3DXFONT_DESC fd;
	ZeroMemory( &fd, sizeof(fd) );
	fd.Height = 20;
	fd.Width = 8;
	fd.Weight = 400;
	fd.Italic = false;
	fd.MipLevels = D3DX_DEFAULT;

	fd.Quality = 0;
	fd.OutputPrecision = 0;
	fd.PitchAndFamily = 0;
	fd.CharSet = DEFAULT_CHARSET;
	wcscpy_s( fd.FaceName, L"Times New Roman" );

	D3DXCreateFontIndirect( device, &fd, &m_font );
}

void FontText::Render( LPDIRECT3DDEVICE9 device )
{
	m_font->DrawTextA(
		NULL, 
		m_str.c_str(), 
		m_str.size(), 
		NULL, 
		DT_TOP | DT_LEFT, 
		0xff000000
		);
}

void FontText::SetText( std::string t_str )
{
	m_str = t_str;
}