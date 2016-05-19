#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__RENDER_OBJECT_BASE_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__RENDER_OBJECT_BASE_H__

#include <d3dx9.h>
#pragma comment( lib, "d3dx9.lib" )

// maybe useful later
class RenderObjectBase
{
public:
	RenderObjectBase(){};
	virtual ~RenderObjectBase(){};

	virtual void Config() = 0;
	virtual void PreRender( LPDIRECT3DDEVICE9 device ) = 0;
	virtual void Render( LPDIRECT3DDEVICE9 device ) = 0;
};


 #endif 