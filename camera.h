#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <d3dx9math.h>
#include <d3d9.h>
#pragma comment(lib, "d3dx9.lib")
#include "render_object_base.h"

class Camera : public RenderObjectBase
{
public:
	Camera(){};
	~Camera(){};

	virtual void Config();
	virtual void PreRender( LPDIRECT3DDEVICE9 device );
	virtual void Render( LPDIRECT3DDEVICE9 device );

	virtual bool OnKeyDown( WPARAM wParam );
	virtual bool OnKeyMoveDown( int x, int y, int z );

protected:
	D3DXMATRIX m_viewMat;
	D3DXMATRIX m_projMat;

	float m_move_speed;
};

#endif