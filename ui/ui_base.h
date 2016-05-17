
#include <d3dx9.h>
#pragma comment( lib, "d3dx9.lib" )

#include "../render_object_base.h"

class UIBase : public RenderObjectBase
{
public:
	virtual void Config();
	virtual void PreRender( LPDIRECT3DDEVICE9 device );
	virtual void Render( LPDIRECT3DDEVICE9 device );
};