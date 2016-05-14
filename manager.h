#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "model.h"
#include "model_material.h"

#include "camera.h"
#include "camera_simple_move.h"

#include "light.h"

#include "terrain.h"

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

private:
	LPDIRECT3DDEVICE9 m_device;
	std::vector< RenderObjectBase* > m_vec_model;

	double m_last_time;
};

#endif