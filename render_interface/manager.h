#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__RENDER_INTERFACE_MANAGER_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__RENDER_INTERFACE_MANAGER_H__

#include "render_objects/model/model.h"
#include "render_objects/model/model_material.h"
#include "render_objects/model/model_material_texture.h"
#include "render_objects/model/model_material_texture_alpha.h"

#include "camera/camera.h"
#include "camera/camera_simple_move.h"

#include "render_objects/light/light.h"
#include "render_objects/light/light_point.h"

#include "render_objects/terrain/terrain.h"

#include "render_objects/text/textfont.h"

#include "render_interface/update_base.h"

#include <vector>

/************************************************************************/
/*                                                                      */
/************************************************************************/

class ModelManager
{
public:
	ModelManager( LPDIRECT3DDEVICE9 device );
	~ModelManager();

	void Config();
	void PreRender();
	void Render();

	void Clear();

	
	float GetCurTime();
	void Update();
	bool OnKeyDown( WPARAM wParam );
	bool HandleLeftMouseButton( bool isDown );
	bool HandleMouseMove( int x, int y );

	static const D3DXMATRIX* GetCameraMatrix();
	static const D3DXMATRIX* GetInvCameraMatrix();
	static const D3DXMATRIX* GetProjMatrix();

private:
	LPDIRECT3DDEVICE9 m_device;
	static Camera* s_pCamera;

	std::vector< RenderObjectBase* > m_vec_model;
	std::vector< EventHandlerBase* > m_vec_eventhandle;
	std::vector< UpdateBase* > m_vec_updater;

	DWORD m_last_time;
};

#endif 