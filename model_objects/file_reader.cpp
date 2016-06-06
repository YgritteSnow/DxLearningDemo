#include "file_reader.h"
#include <deque>

IOFileBase::IOFileBase( const char* filename )
	: m_fstream(NULL)
{
	strcpy( m_filename, filename );
}

IOFileBase::~IOFileBase()
{

}

bool IOFileBase::OpenFile( const char* filename )
{
	CloseFile();
	m_fstream = new std::fstream( m_filename );

	return true;
}

bool IOFileBase::WriteFile( const char* filename, DataSection* rootSec )
{
	OpenFile( filename );
	WriteFileData( rootSec );
	CloseFile();
}

void IOFileBase::WriteFileData( DataSection* rootSec )
{
	// 采用先序遍历来遍历多叉树
	if( !m_fstream )
	{
		return;
	}

	std::deque< DataSection* > temp_tack;
	temp_tack.push_back( rootSec );
	while( !temp_tack.empty() )
	{
		DataSection* cur_sec = temp_tack.back();
		temp_tack.pop_back();
		
		size_t idx = cur_sec->GetChildren().size() - 1;
		do
		{
			temp_tack.push_back( cur_sec->GetChildren()[idx] );
		}
		while( idx != 0 );

		WriteLineData( cur_sec );
	}
}

void IOFileBase::WriteLineData( DataSection* dataSec )
{
	int i = dataSec->depth;
	while( i-- != 0 )
	{
		(*m_fstream)<<'-';
	}
	(*m_fstream)<<dataSec->name.c_str()<<dataSec->data.c_str()<<std::endl;
}

bool IOFileBase::CloseFile()
{
	if( m_fstream )
	{
		m_fstream->close();
		delete m_fstream;
		m_fstream = NULL;
	}

	return true;
}