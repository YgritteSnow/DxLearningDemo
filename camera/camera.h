#ifndef __CAMERA_CAMERA_H__
#define __CAMERA_CAMERA_H__

#include <d3dx9math.h>
#include <d3d9.h>
#pragma comment(lib, "d3dx9.lib")
#include "render_interface/render_object_base.h"
#include "render_interface/event_handle_base.h"

class Camera : public RenderObjectBase, public EventHandlerBase
{
public:
	Camera(){};
	~Camera(){};

	virtual void Config();
	virtual void PreRender( LPDIRECT3DDEVICE9 device );
	virtual void Render( LPDIRECT3DDEVICE9 device );

	virtual bool OnKeyDown( WPARAM wParam );

	virtual bool OnKeyMoveDown( int x, int y, int z );

	const D3DXMATRIX* GetCamMatrix(){return &m_viewMat;};
	const D3DXMATRIX* GetInvCamMatrix(){return &m_invViewMat;};
	const D3DXMATRIX* GetProjMatrix(){return &m_projMat;};

protected:
	D3DXMATRIX m_viewMat;
	D3DXMATRIX m_invViewMat;
	D3DXMATRIX m_projMat;
};

#endif 