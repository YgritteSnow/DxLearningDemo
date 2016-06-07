
#include "file_reader/file_reader.h"
/************************************************************************/
/* 统筹管理游戏全局的单例、配置等的类
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

private:
	void InitGame()
	{
		FileReaderManager::GetFileReaderManager();
	}
};