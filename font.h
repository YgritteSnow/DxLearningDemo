#ifndef __FONT_H__
#define __FONT_H__

#include <wstring>
#include <d3dx9.h>
#pragma comment( lib, "d3dx9.lib" )

#include "render_object_base.h"
class Font : public RenderObjectBase
{
public:
	Font();
	virtual ~Font();
	
	void Config();
	void PreRender( LPDIRECT3DDEVICE9 device );
	void Render( LPDIRECT3DDEVICE9 device );
	
public:
	D3DXFont* m_font;
	std::wstring m_str;
};
#endif