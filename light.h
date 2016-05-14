#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")
#include "render_object_base.h"

class Light : public RenderObjectBase
{
public:
	Light(){};
	virtual ~Light();

	virtual void Config();
	virtual void PreRender( LPDIRECT3DDEVICE9 device );
	virtual void Render( LPDIRECT3DDEVICE9 device );

private:
	D3DLIGHT9 m_light;
};

#endif