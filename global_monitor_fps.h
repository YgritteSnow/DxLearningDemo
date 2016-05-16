#ifndef __GLOBAL_MONITOR_FPS_H__
#define __GLOBAL_MONITOR_FPS_H__

#include "global_monitor.h"
#include <Windows.h>

class GlobalMonitor_fps : public GlobalMonitorBase
{
public:
	GlobalMonitor_fps()
		:m_cur_time(0)
		,m_fps_count(0)
	{name = "FPS";}

	virtual void Update( DWORD timeDelta );

private:
	DWORD m_cur_time;
	DWORD m_fps_count;

};
#endif