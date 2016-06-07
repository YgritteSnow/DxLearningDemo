#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__GAME_MANAGER_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__GAME_MANAGER_H__
#include "file_reader/file_reader.h"
/************************************************************************/
/* ͳ�������Ϸȫ�ֵĵ��������õȵ���
*/
/************************************************************************/

class GameManager
{
private:
	explicit GameManager(){InitGame();}
public:
	~GameManager(){}
	static GameManager& GetGameManager()
	{ 
		static GameManager game_manager;
		return game_manager; 
	}

	// ����
	void PreRender()
	{
		ModelManager::GetModelManager().PreRender();
	}
	void Render()
	{
		ModelManager::GetModelManager().Render();
	}
	void Update()
	{
		ModelManager::GetModelManager().Update();
	}
	void Clear()
	{
		ModelManager::GetModelManager().Clear();
	}

	bool OnKeyDown( WPARAM wParam )
	{
		return ModelManager::GetModelManager().OnKeyDown( wParam );
	}
	bool HandleLeftMouseButton( bool isDown )
	{
		return ModelManager::GetModelManager().HandleLeftMouseButton( isDown );
	}
	bool HandleMouseMove( int x, int y )
	{
		return ModelManager::GetModelManager().HandleMouseMove( x, y );
	}
	
private:
	void InitGame()
	{
		FileReaderManager::GetFileReaderManager();
		ModelManager::GetModelManager();
	}
};

#endif 