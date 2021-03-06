#ifndef __LIGHT_LIGHT_POINT_H__
#define __LIGHT_LIGHT_POINT_H__

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include "light/light.h"
#include <Windows.h>

class LightPoint : public Light
{
public:
	LightPoint(){};
	~LightPoint(){};

	virtual void Config();
	virtual void PreRender( LPDIRECT3DDEVICE9 device );
	virtual void Render( LPDIRECT3DDEVICE9 device );

private:
	D3DXVECTOR3 m_pos;
};

#endif 