#ifndef __TEXT_FONT_H__
#define __TEXT_FONT_H__

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include <string>

#include "render_object_base.h"

// ���ĺ�����ID3DXFont
// �ڲ�ʹ��GDI�ӿ������ú��������Կ��Դ����ӵ�����͸�ʽ������������������ʧ
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