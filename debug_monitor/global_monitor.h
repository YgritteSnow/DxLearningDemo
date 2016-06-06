#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__DEBUG_MONITOR_GLOBAL_MONITOR_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__DEBUG_MONITOR_GLOBAL_MONITOR_H__

#include <vector>
#include <string>
#include <Windows.h>

#include "render_interface/update_base.h"

class GlobalMonitorBase : public UpdateBase
{
public:
	GlobalMonitorBase(){};
	virtual ~GlobalMonitorBase(){};

	virtual void Update( DWORD timeDelta ){};
	virtual const std::string& GetInfo(){return m_info;};
	virtual const std::string& GetName(){return name;}

protected:
	std::string name;
	std::string m_info;
};

interface GlobalMonitorBoardInterface
{
public:
	virtual void SetBoardText( std::string ) = 0;
};

class GlobalMonitorManager : public UpdateBase
{
public:
	GlobalMonitorManager();
	~GlobalMonitorManager(){};

	typedef void (*p_setTextFunc)(std::string);
	void SetDisplayBoard( GlobalMonitorBoardInterface* p_board );

	virtual void Update( DWORD timeDelta );
	void AppendMonitor( GlobalMonitorBase* monitor );

private:
	GlobalMonitorBoardInterface* m_pDisplayboard;
	std::vector< GlobalMonitorBase* > m_vec_monitors;
};

#endif 