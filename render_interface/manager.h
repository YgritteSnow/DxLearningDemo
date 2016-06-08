#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__RENDER_INTERFACE_MANAGER_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__RENDER_INTERFACE_MANAGER_H__

#include "model_objects/meshmodel/model.h"
#include "camera/camera.h"
#include "camera/camera_simple_move.h"

#include "light/light.h"
#include "light/light_point.h"

#include "model_objects/terrain/terrain.h"

#include "model_objects/text/textfont.h"

#include "render_interface/update_base.h"

#include <vector>

/************************************************************************/
/* 掌管所有可渲染的物体
*/
/************************************************************************/

class ModelManager
{
private:
	explicit ModelManager();
public:
	~ModelManager();

	static ModelManager& GetModelManager()
	{
		static ModelManager model_manager;
		return model_manager;
	}

	void PreRender();
	void Render();
	void Clear();
	void Update();

	bool OnKeyDown( WPARAM wParam );
	bool HandleLeftMouseButton( bool isDown );
	bool HandleMouseMove( int x, int y );

	static const D3DXMATRIX* GetCameraMatrix();
	static const D3DXMATRIX* GetInvCameraMatrix();
	static const D3DXMATRIX* GetProjMatrix();

private:
	void Config();
	float GetCurTime();

private:
	LPDIRECT3DDEVICE9 m_device;
	static Camera* s_pCamera;

	std::vector< RenderObjectBase* > m_vec_model;
	std::vector< EventHandlerBase* > m_vec_eventhandle;
	std::vector< UpdateBase* > m_vec_updater;

	DWORD m_last_time;
};

#endif 