#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "model.h"
#include "model_material.h"
#include "model_material_texture.h"
#include "model_material_texture_alpha.h"

#include "camera.h"
#include "camera_simple_move.h"

#include "light.h"
#include "light_point.h"

#include "terrain.h"

#include "textfont.h"

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
	void Update( float delta_time );
	bool OnKeyDown( WPARAM wParam );
	bool HandleLeftMouseButton( bool isDown );
	bool HandleMouseMove( int x, int y );

private:
	LPDIRECT3DDEVICE9 m_device;
	std::vector< RenderObjectBase* > m_vec_model;
	std::vector< EventHandlerBase* > m_vec_eventhandle;

	double m_last_time;
};

#endif