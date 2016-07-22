#ifndef __FILE_READER_FILE_READEE_BASE_H__
#define __FILE_READER_FILE_READEE_BASE_H__

#include "file_reader/file_reader.h"

class FileReadBase
{
public:
	FileReadBase():m_isLoaded(false){}
	FileReadBase( const char* filename ):m_isLoaded(false){ LoadFromFile( filename ); }
	FileReadBase( DataSection* rootSec ){ LoadByDataSection( rootSec ); }
	virtual ~FileReadBase(){}
	virtual bool OnLoadByDataSection( DataSection* rootSec ) = 0;
	bool IsLoaded(){ return m_isLoaded; }

protected:
	bool m_isLoaded;

private:
	void LoadFromFile( const char* filename )
	{
		DataSection* root_sec = NULL;
		FileReaderManager::GetFileReaderManager().ReadFile_dataSec( filename, root_sec );
		LoadByDataSection( root_sec );
	}
	void LoadByDataSection( DataSection* rootSec ){ m_isLoaded = OnLoadByDataSection( rootSec ); }
};

#endif 