#include "config/config.h"
#include "file_reader/file_reader.h"

#include <iostream>

#if USE_DEBUG
int main()
#else
int ygritte_main()
#endif
{
	//DataSection* root_sec = new DataSection();
	//root_sec->name = "root";
	//root_sec->data = "data";


	//DataSection* child1 = new DataSection();
	//child1->name = "child1";
	//child1->data = "data1";

	//DataSection* child2 = new DataSection();
	//child2->name = "child2";
	//child2->data = "data2";

	//child1->AddChild(child2);

	//root_sec->AddChild(child1);
	//root_sec->AddChild(child2);

	//f.WriteFile_addRoot( "F:\\a.txt", root_sec );

	DataSection* newRoot = NULL;
	FileReaderManager::GetFileReaderManager().ReadFile_dataSec( "F:\\a.txt", newRoot );
	FileReaderManager::GetFileReaderManager().WriteFile_dataSec( "F:\\a.txt", newRoot, true );

	return 0;
}