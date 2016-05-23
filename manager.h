#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MANAGER_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MANAGER_H__

#include "model/model.h"
#include "model/model_material.h"
#include "model/model_material_texture.h"
#include "model/model_material_texture_alpha.h"

#include "camera/camera.h"
#include "camera/camera_simple_move.h"

#include "light/light.h"
#include "light/light_point.h"

#include "model/terrain.h"

#include "text/textfont.h"

#include "update_base.h"

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