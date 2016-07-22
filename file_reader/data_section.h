#ifndef __FILE_READER_DATA_SECTION_H__
#define __FILE_READER_DATA_SECTION_H__
#include <vector>
#include <sstream>

class DataSection;
typedef std::vector< DataSection* > DataSectionVec;

class DataSection
{
private:
	std::string name;
	DataSectionVec children;
	std::stringstream datastream;

public:
	void AddChild( DataSection* child )
	{
		children.push_back( child );
	}
	const DataSectionVec& GetChildren()
	{
		return children;
	}
	bool GetChildByName( const char* name, DataSection*& childSec )
	{
		childSec = NULL;
		for( auto it = children.begin(); it != children.end(); ++it )
		{
			if( strcmp( (*it)->GetNameStr().c_str(), name ) == 0 )
			{
				childSec = *it;
				return true;
			}
		}
		return false;
	}

	const std::string& GetNameStr()
	{
		return name;
	}

	void SetName( const char* namestr )
	{
		name = namestr;
	}

	template <typename DataType>
	DataType GetData()
	{
		DataType i;
		datastream >> i;
		return i;
	}

	std::string GetDataString()
	{
		return datastream.str();
	}
	
	template < typename DataType >
	void SetData( DataType buf )
	{
		datastream.clear();
		datastream<<buf;
	}
	
	template < typename DataType >
	void AddData( DataType buf )
	{
		datastream<<buf;
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