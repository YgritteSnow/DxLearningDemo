#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__RENDER_OBJECTS_TEXT_TEXTFONT_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__RENDER_OBJECTS_TEXT_TEXTFONT_H__

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include <string>

#include "render_interface/render_object_base.h"

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

	void SetText( std::string t_str );

private:
	std::string m_str;
	LPD3DXFONT m_font;
};

#endif 