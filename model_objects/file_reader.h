#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_OBJECTS_FILE_READER_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_OBJECTS_FILE_READER_H__
#include <fstream>
#include <vector>

struct DataSection;
typedef std::vector< DataSection* > DataSectionVec;

struct DataSection
{
	std::string name;
	std::string data;
	DataSectionVec children;

	void AddChild( DataSection* child )
	{
		children.push_back( child );
	}
	const DataSectionVec& GetChildren()
	{
		return children;
	}
};

struct DataSectionHelper
{
	DataSectionHelper():sec(NULL), depth(-1){}
	DataSectionHelper( DataSection* _sec, int _depth ):sec(_sec), depth(_depth){}
	~DataSectionHelper(){}

	DataSection* sec;
	int depth;
};

class IOFileBase
{
public:
	IOFileBase();
	~IOFileBase();

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