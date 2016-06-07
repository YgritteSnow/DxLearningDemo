#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_OBJECTS_FILE_READER_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_OBJECTS_FILE_READER_H__

#include "file_reader/file_reader_ygritte.h"

class FileReaderManager
{
private:
	explicit FileReaderManager(){ InitSelf(); }
public:
	~FileReaderManager(){}
	static FileReaderManager& GetFileReaderManager()
	{
		static FileReaderManager fileReaderManager;
		return fileReaderManager; 
	}

	void WriteFile_dataSec( const char* filename, DataSection* in_sec, bool ifNullRoot ){ m_iofile_ygritte.WriteFile( filename, in_sec, ifNullRoot ); }
	void ReadFile_dataSec( const char* filename, DataSection*& out_sec ){ m_iofile_ygritte.ReadFile( filename, out_sec ); }

private:
	void InitSelf(){}

	IOFile_ygritte m_iofile_ygritte;
};

#endif 