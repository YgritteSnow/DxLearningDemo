#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__GLOBAL_DEBUG_BOARD_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__GLOBAL_DEBUG_BOARD_H__

#include "textfont.h"
#include <map>
#include <string>

#include "global_monitor.h"

class GlobalDebugBoard : public FontText, public GlobalMonitorBoardInterface
{
public:
	virtual void SetBoardText( std::string s )
	{
		SetText( s );
	}
};


 #endif 