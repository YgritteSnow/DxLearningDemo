#include <fstream>
#include <vector>

struct DataSection;
typedef std::vector< DataSection* > DataSectionVec;

struct DataSection
{
	std::string name;
	std::string data;
	DataSectionVec children;
	int depth;

	void AddChild( DataSection* child )
	{
		children.push_back( child );
	}
	const DataSectionVec& GetChildren()
	{
		return children;
	}
};

class IOFileBase
{
public:
	IOFileBase( const char* filename );
	~IOFileBase();

	bool WriteFile( const char* filename, DataSection* rootSec );

private:
	bool OpenFile( const char* filename );
	bool CloseFile();
	void WriteFileData( DataSection* dataSec );
	void WriteLineData( DataSection* dataSec );

	char m_filename[256];
	std::fstream* m_fstream;
};