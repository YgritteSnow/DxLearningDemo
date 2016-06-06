#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__LIGHT_LIGHT_POINT_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__LIGHT_LIGHT_POINT_H__

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include "render_objects/light/light.h"
#include <Windows.h>
#include "render_objects/model/model_material.h"

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
	ModelWithMaterial m_sunmodel;
};

#endif 