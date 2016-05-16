#include "manager.h"
#include <Windows.h>
#pragma comment(lib, "winmm.lib")


/************************************************************************/
/*                                                                      */
/************************************************************************/

ModelManager::ModelManager( LPDIRECT3DDEVICE9 device ) 
{
	m_device = device;
	
	m_vec_model.clear();
	CameraSimpleMove* t_cam = new CameraSimpleMove();
	m_vec_model.push_back( t_cam );
	m_vec_model.push_back( new LightPoint() );
	m_vec_model.push_back( new Terrain() );
	m_vec_model.push_back( new ModelWithMaterialTextureAlpha() );
	m_vec_model.push_back( new FontText() );

	m_vec_eventhandle.clear();
	m_vec_eventhandle.push_back( t_cam );

	Config();
}

ModelManager::~ModelManager()
{
	Clear();
}

void ModelManager::Config()
{
	for( auto it = m_vec_model.begin(); it != m_vec_model.end(); ++it )
	{
		(*it)->Config();
	}
}

void ModelManager::PreRender()
{
	for( auto it = m_vec_model.begin(); it != m_vec_model.end(); ++it )
	{
		(*it)->PreRender( m_device );
	}
}

void ModelManager::Render()
{
	m_device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_XRGB(100, 200, 100), 1.0f, 0 );
	m_device->BeginScene();
	for( auto it = m_vec_model.begin(); it != m_vec_model.end(); ++it )
	{
		(*it)->Render( m_device );
	}

	m_device->EndScene();
	m_device->Present(NULL, NULL, NULL, NULL);

}

void ModelManager::Clear()
{
	for( auto it = m_vec_model.begin(); it != m_vec_model.end(); ++it )
	{
		delete (*it);
	}
	m_vec_model.clear();
}

float ModelManager::GetCurTime()
{
	return (float)timeGetTime();
}

void ModelManager::Update( float delta_time )
{

}

bool ModelManager::OnKeyDown( WPARAM wParam )
{
	bool ret = false;
	for( auto it = m_vec_eventhandle.begin(); it != m_vec_eventhandle.end(); ++it )
	{
		ret = ret || (*it)->OnKeyDown( wParam );
	}

	return ret;
}

bool ModelManager::HandleLeftMouseButton( bool isDown )
{
	bool ret = false;
	for( auto it = m_vec_eventhandle.begin(); it != m_vec_eventhandle.end(); ++it )
	{
		ret = ret || (*it)->HandleMouseDown( isDown );
	}
	return ret;
}

bool ModelManager::HandleMouseMove( int x, int y )
{
	bool ret = false;
	for( auto it = m_vec_eventhandle.begin(); it != m_vec_eventhandle.end(); ++it )
	{
		ret = ret || (*it)->HandleMouseMove( x, y );
	}
	return ret;
}