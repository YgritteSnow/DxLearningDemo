#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__FILE_READER_DATA_SECTION_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__FILE_READER_DATA_SECTION_H__
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

#endif 