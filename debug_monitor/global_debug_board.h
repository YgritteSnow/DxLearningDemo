#ifndef __DEBUG_MONITOR_GLOBAL_DEBUG_BOARD_H__
#define __DEBUG_MONITOR_GLOBAL_DEBUG_BOARD_H__

#include "model_objects/text/textfont.h"
#include <map>
#include <string>

#include "debug_monitor/global_monitor.h"

class GlobalDebugBoard : public FontText, public GlobalMonitorBoardInterface
{
public:
	virtual void SetBoardText( std::string s )
	{
		SetText( s );
	}
};

#endif 