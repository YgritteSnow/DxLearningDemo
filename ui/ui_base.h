#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__UI_UI_BASE_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__UI_UI_BASE_H__
#include <d3dx9.h>
#include <d3dx9math.h>
#pragma comment( lib, "d3dx9.lib" )

#include "../render_object_base.h"

enum PosMode
{
	LEFT, 
	CENTER,
	RIGHT, 
};

enum SizeMode
{
	CLIP, 
	PIXEL, 
};

class UIBase : public RenderObjectBase
{
public:
	UIBase()
		: m_vb(NULL)
		, m_tex(NULL)
		, m_h_pos_mode(CENTER)
		, m_v_pos_mode(CENTER)
		, m_h_size_mode(CLIP)
		, m_v_size_mode(CLIP)
		, m_h_pos_size_mode(CLIP)
		, m_v_pos_size_mode(CLIP)
		, m_h_pos(0.f)
		, m_v_pos(0.f)
		, m_h_size(2.f)
		, m_v_size(2.f)
	{};
	virtual ~UIBase(){};

	virtual void Config();
	virtual void PreRender( LPDIRECT3DDEVICE9 device );
	virtual void Render( LPDIRECT3DDEVICE9 device );

	virtual void SetPos( float h_pos, float v_pos );
	virtual void SetSize( float h_size, float v_size );

protected:
	void RecalMatrix();

private:
	float GetScaleH();
	float GetScaleV();
	float GetPosOffsetH();
	float GetPosOffsetV();
	float GetPosH();
	float GetPosV();

	struct UIVertex
	{
		UIVertex()
			: _x(0), _y(0), _z(0), _color(0), _u(0), _v(0) {}
		UIVertex( float x, float y, float z, DWORD color, float u, float v )
			: _x(x), _y(y), _z(z), _color(color), _u(u), _v(v) {}
		float _x, _y, _z;
		DWORD _color;
		float _u, _v;
		static DWORD FVF;
	};
	D3DXMATRIX m_matrix;
	LPDIRECT3DVERTEXBUFFER9 m_vb;
	LPDIRECT3DTEXTURE9 m_tex;

	static const int c_vertex_size = 6;

	PosMode m_h_pos_mode;
	PosMode m_v_pos_mode;
	SizeMode m_h_pos_size_mode;
	SizeMode m_v_pos_size_mode;
	SizeMode m_h_size_mode;
	SizeMode m_v_size_mode;

	float m_h_pos;
	float m_v_pos;
	float m_h_size;
	float m_v_size;

	D3DXVECTOR2 m_ui_pos;	// -1 ~ 1
	D3DXVECTOR2 m_ui_size;	// -1 ~ 1
};
 #endif 