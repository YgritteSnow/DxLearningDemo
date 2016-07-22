#ifndef __RENDER_INTERFACE_EVENT_HANDLE_BASE_H__
#define __RENDER_INTERFACE_EVENT_HANDLE_BASE_H__

#include "Windows.h"

// maybe useful later
class EventHandlerBase
{
public:
	EventHandlerBase():m_cur_pos_x(0), m_cur_pos_y(0), m_inited(false), m_isMouseDown(false){};
	virtual ~EventHandlerBase(){};

	virtual bool HandleMouseDown( bool isDown )
	{
		m_isMouseDown = isDown;
		return false;
	};

	virtual bool HandleMouseMove( int pos_x, int pos_y )
	{
		if( m_isMouseDown )
		{
			if( m_inited )
			{
				OnMouseDownMove( pos_x - m_cur_pos_x, pos_y - m_cur_pos_y );
			}
		}
		m_cur_pos_x = pos_x;
		m_cur_pos_y = pos_y;

		m_inited = true;

		return false;
	}
	
	virtual bool OnMouseDownMove( int x, int y ){return false;};
	virtual bool OnKeyDown( WPARAM wParam ){return false;};

private:
	bool m_inited;
	bool m_isMouseDown;
	int m_cur_pos_x;
	int m_cur_pos_y;
};

#endif 