#ifndef __FILE_READER_FILE_READER_H__
#define __FILE_READER_FILE_READER_H__

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include "file_reader/file_reader_ygritte.h"

extern LPDIRECT3DDEVICE9 g_d3ddevice;

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

	bool WriteFile_dataSec( const char* filename, DataSection* in_sec, bool ifNullRoot ){ return m_iofile_ygritte.WriteFile( filename, in_sec, ifNullRoot ); }
	bool ReadFile_dataSec( const char* filename, DataSection*& out_sec ){ return m_iofile_ygritte.ReadFile( filename, out_sec ); }

	bool ReadFile_texture( const char* filename, LPDIRECT3DTEXTURE9& out_ptex )
	{
		return SUCCEEDED( D3DXCreateTextureFromFileA( g_d3ddevice, filename, &out_ptex ) );
	}

private:
	void InitSelf(){}

	IOFile_ygritte m_iofile_ygritte;
};

#endif 