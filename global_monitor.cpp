#include "global_monitor.h"
#include "global_monitor_fps.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

GlobalMonitorManager::GlobalMonitorManager()
	:m_pDisplayboard(NULL)
{
	AppendMonitor( new GlobalMonitor_fps() );
}

void GlobalMonitorManager::SetDisplayBoard( GlobalMonitorBoardInterface* p_board )
{
	m_pDisplayboard = p_board;
}


void GlobalMonitorManager::AppendMonitor( GlobalMonitorBase* monitor )
{
	m_vec_monitors.push_back( monitor );
}

void GlobalMonitorManager::Update( DWORD timeDelta )
{
	std::string res;
	for( auto it = m_vec_monitors.begin(); it != m_vec_monitors.end(); ++it )
	{
		(*it)->Update( timeDelta );
		res += (*it)->GetName();
		res += ": ";
		res += (*it)->GetInfo();
	}

	if( m_pDisplayboard )
	{
		m_pDisplayboard->SetBoardText( res );
	}
}