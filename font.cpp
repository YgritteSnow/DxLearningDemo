#include "font.h"

Font::Font()
: m_font(NULL)
{}

Font::~Font()
{}

void Font::Config()
{
	m_str = L"asdfasdf";
}

void Font::PreRender( LPDIRECT3DDEVICE9 device )
{
	D3DXFONT_DESC fd;
	fd.Height = 100;
	fd.Width = 200;
	fd.Weight = 400;
	fd.MipLevel = 0;
	fd.Italic = true;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = 0;
	fd.Quality = 0;
	fd.PitchAndFamily = 0;
	strcpy( fd.FaceName, "Times New Roman" );
	
	D3DXCreateFontIndirect( device, &fd, &m_font );
}

void Font::Render( LPDIRECT3DDEVICE9 device )
{
	m_font->DrawFont(
			NULL, 
			m_str.c_str(),
			m_str.size(),
			&rect, 
			DT_TOP | DT_LEFT,
			0xff000000 );
}