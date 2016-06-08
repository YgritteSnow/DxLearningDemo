#include "file_reader/file_reader_ygritte.h"
#include <deque>

const char Tag_Space = '-';
const char Tag_Name = '|';

IOFile_ygritte::IOFile_ygritte()
{
}

IOFile_ygritte::~IOFile_ygritte()
{

}

bool IOFile_ygritte::OpenFile( const char* filename, std::ios_base::open_mode iosopenmode )
{
	CloseFile();
	m_fstream.open( filename, iosopenmode );

	return true;
}

bool IOFile_ygritte::CloseFile()
{
	if( m_fstream.is_open() )
	{
		m_fstream.close();
	}

	return true;
}

bool IOFile_ygritte::WriteFile( const char* filename, DataSection* in_rootSec, bool ifNullRoot )
{
	if( ifNullRoot )
	{
		return WriteFile_useNullRoot( filename, in_rootSec );
	}
	else
	{
		return WriteFile_addRoot( filename, in_rootSec );
	}
}

bool IOFile_ygritte::WriteFile_addRoot( const char* filename, DataSection* in_rootSec )
{
	OpenFile( filename, std::ios::app );
	WriteFileData( in_rootSec );
	CloseFile();
	return true;
}

bool IOFile_ygritte::WriteFile_useNullRoot( const char* filename, DataSection* in_rootSec )
{
	OpenFile( filename, std::ios::out );
	for( auto it = in_rootSec->GetChildren().begin(); it != in_rootSec->GetChildren().end(); ++it )
	{
		WriteFileData( *it );
	}
	CloseFile();
	return true;
}

void IOFile_ygritte::WriteFileData( DataSection* rootSec )
{
	// 采用先序遍历来遍历多叉树
	if( !m_fstream.is_open() )
	{
		return;
	}

	std::deque< DataSectionHelper > temp_tack;
	temp_tack.push_back( DataSectionHelper(rootSec, -1) );
	while( !temp_tack.empty() )
	{
		DataSectionHelper cur_sec = temp_tack.back();
		temp_tack.pop_back();

		if( cur_sec.sec->GetChildren().size() >= 1 )
		{
			int idx = cur_sec.sec->GetChildren().size() - 1;
			do
			{
				temp_tack.push_back( DataSectionHelper(cur_sec.sec->GetChildren()[idx], cur_sec.depth + 1) );
				--idx;
			}
			while( idx >= 0 );
		}

		WriteLineData( cur_sec );
	}
}

void IOFile_ygritte::WriteLineData( const DataSectionHelper& dataSec )
{
	int i = dataSec.depth;
	while( i-- >= 0 )
	{
		m_fstream<<Tag_Space;
	}
	m_fstream<<dataSec.sec->GetNameStr().c_str()<<Tag_Name<<dataSec.sec->GetDataString().c_str()<<std::endl;
}

bool IOFile_ygritte::ReadFile( const char* filename, DataSection*& out_rootSec )
{
	OpenFile( filename, std::ios::in );
	ReadFileData( out_rootSec );
	CloseFile();
	return true;
}

void IOFile_ygritte::ReadFileData( DataSection*& out_rootSec )
{
	// 默认文件是按照先序遍历的方式存储的
	if( !m_fstream.is_open() )
	{
		return;
	}

	DataSectionHelper rootSec;
	rootSec.sec = new DataSection();
	out_rootSec = rootSec.sec;

	std::deque< DataSectionHelper > temp_stack;
	temp_stack.push_back( rootSec );// 栈里边一定至少有一个root，并且depth最小
	DataSectionHelper cur_father;

	DataSectionHelper new_line_sec;
	while( ReadLineData( new_line_sec ) )
	{
		if( new_line_sec.depth > temp_stack.back().depth )
		{
			cur_father = temp_stack.back();
			temp_stack.push_back( new_line_sec );
		}
		else if( new_line_sec.depth == temp_stack.back().depth )
		{
			temp_stack.pop_back();
			temp_stack.push_back( new_line_sec );
		}
		else
		{
			while( new_line_sec.depth <= temp_stack.back().depth )
			{
				temp_stack.pop_back();
			}
			cur_father = temp_stack.back();
			temp_stack.push_back( new_line_sec );
		}
		cur_father.sec->AddChild( new_line_sec.sec );
	}
}

bool IOFile_ygritte::ReadLineData( DataSectionHelper& out_rootSec )
{
	if( !m_fstream.is_open() )
		return false;

	const int bufsize = 128;
	static char buf[bufsize];
	m_fstream.getline( buf, bufsize );
	if( *buf ) // 粗略试一下
	{
		int idx_name = 0;
		for( ; idx_name < bufsize; ++idx_name )
		{
			if( buf[idx_name] != Tag_Space )
				break;
		}

		int idx_data = 0;
		for( ; idx_data < bufsize; ++idx_data )
		{
			if( buf[idx_data] == Tag_Name )
			{
				buf[idx_data] = 0;
				++ idx_data;
				break;
			}
		}
		out_rootSec.sec = new DataSection();
		out_rootSec.sec->SetName(buf + idx_name);
		out_rootSec.sec->SetData(buf + idx_data);
		out_rootSec.depth = idx_name;

		return true;
	}
	else
	{
		out_rootSec.sec = NULL;
		return false;
	}
}