#ifndef __TEXT_FONT_H__
#define __TEXT_FONT_H__

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include <string>

#include "render_object_base.h"

// 核心函数：ID3DXFont
// 内部使用GDI接口来调用函数，所以可以处理复杂的字体和格式，但是性能上略有损失
class FontText : public RenderObjectBase
{
public:
	FontText();
	virtual ~FontText();

	void Config();
	void PreRender( LPDIRECT3DDEVICE9 device );
	void Render( LPDIRECT3DDEVICE9 device );

	void SetText( std::wstring t_str );

private:
	std::wstring m_str;
	LPD3DXFONT m_font;
};
#endif