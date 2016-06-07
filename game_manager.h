
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

private:
	void InitGame()
	{
		FileReaderManager::GetFileReaderManager();
	}
};