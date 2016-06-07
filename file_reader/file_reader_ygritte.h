#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__FILE_READER_FILE_READER_YGRITTE_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__FILE_READER_FILE_READER_YGRITTE_H__
#include <fstream>
#include "file_reader/data_section.h"

struct DataSection;
class IOFile_ygritte
{
public:
	IOFile_ygritte();
	~IOFile_ygritte();

	bool WriteFile( const char* filename, DataSection* in_rootSec, bool ifNullRoot );
	bool WriteFile_addRoot( const char* filename, DataSection* in_rootSec );
	bool WriteFile_useNullRoot( const char* filename, DataSection* in_rootSec );

	bool ReadFile( const char* filename, DataSection*& out_rootSec );

private:
	bool OpenFile( const char* filename, std::ios_base::open_mode iosopenmode );
	bool CloseFile();
	void WriteFileData( DataSection* dataSec );
	void ReadFileData( DataSection*& out_rootSec );
	void WriteLineData( const DataSectionHelper& dataSec );
	bool ReadLineData( DataSectionHelper& out_rootSec );

	std::fstream m_fstream;
};
#endif 