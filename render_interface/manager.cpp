#include "render_interface/manager.h"
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#include "debug_monitor/global_monitor.h"
#include "debug_monitor/global_debug_board.h"
#include "texture_editor/texture_editor.h"
#include "model_objects/sprite/sprite_ball.h"
#include "model_objects/ui/ui_base.h"

GlobalMonitorManager g_global_monitor = GlobalMonitorManager();

#include <d3d9.h>
#pragma comment( lib, "d3d9.lib" )
extern LPDIRECT3DDEVICE9 g_d3ddevice;


/************************************************************************/
/*                                                                      */
/************************************************************************/

Camera* ModelManager::s_pCamera = NULL;

ModelManager::ModelManager() 
	:m_last_time(0)
{
	m_device = g_d3ddevice;
	
	// 这部分是时刻渲染的
	m_vec_model.clear();
	CameraSimpleMove* t_cam = new CameraSimpleMove();
	m_vec_model.push_back( t_cam );

	s_pCamera = t_cam;

	m_vec_model.push_back( new LightPoint() );
	//m_vec_model.push_back( new Terrain() );
	m_vec_model.push_back( new UIBase() );

	//FurrySprite* t_sprite = new FurrySprite();
	//m_vec_model.push_back( t_sprite );

	GlobalDebugBoard* t_global_board = new GlobalDebugBoard();
	m_vec_model.push_back( t_global_board );

	/*TextureEditor* t_textureEditor = new TextureEditor();
	TextureDiaplayBoard* t_texturePlayBoard = new TextureDiaplayBoard();
	t_textureEditor->SetPlayBoard( t_texturePlayBoard );
	m_vec_model.push_back( t_textureEditor );
	m_vec_model.push_back( t_texturePlayBoard );*/

	// 这部分是处理消息的
	m_vec_eventhandle.clear();
	m_vec_eventhandle.push_back( t_cam );

	// 这部分是随时间更新的
	g_global_monitor.SetDisplayBoard( t_global_board );
	m_vec_updater.clear();
	m_vec_updater.push_back( &g_global_monitor );

	//m_vec_updater.push_back( t_sprite );

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

void ModelManager::Update()
{
	DWORD new_time = timeGetTime();

	if( m_last_time != 0 )
	{
		for( auto it = m_vec_updater.begin(); it != m_vec_updater.end(); ++it )
		{
			(*it)->Update( new_time - m_last_time );
		}
	}

	m_last_time = new_time;
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

const D3DXMATRIX* ModelManager::GetCameraMatrix()
{
	if( s_pCamera )
	{
		return s_pCamera->GetCamMatrix();
	}
	else
	{
		return NULL;
	}
}

const D3DXMATRIX* ModelManager::GetInvCameraMatrix()
{
	if( s_pCamera )
	{
		return s_pCamera->GetInvCamMatrix();
	}
	else
	{
		return NULL;
	}
}

const D3DXMATRIX* ModelManager::GetProjMatrix()
{
	if( s_pCamera )
	{
		return s_pCamera->GetProjMatrix();
	}
	else
	{
		return NULL;
	}
}