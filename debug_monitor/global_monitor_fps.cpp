#include "debug_monitor/global_monitor_fps.h"
#include <time.h>

void GlobalMonitor_fps::Update( DWORD timeDelta )
{
	m_cur_time += timeDelta;
	++ m_fps_count;
	if( m_cur_time > 500 )
	{
		char temp_char[16];
		sprintf_s( temp_char, "%.2f", (float)m_fps_count / m_cur_time * 1000.f );
		m_info = temp_char;

		m_cur_time = 0;
		m_fps_count = 0;
	}
}