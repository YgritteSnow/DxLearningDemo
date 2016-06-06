
struct ModelVertex
{
	ModelVertex()
		:_x(0), _y(0), _z(0), 
		_nx(0), _ny(0), _nz(0), 
		_color(0x0), 
		_u(0), _v(0)
	{}

	float _x, _y, _z;
	float _nx, _ny, _nz;
	DWORD _color;
	float _u, _v;
	static DWORD FVF;
};

struct MtlTexVertex
{
	MtlTexVertex():_x(0), _y(0), _z(0), 
		_nx(0), _ny(0), _nz(0), 
		_color(0), 
		_u(0), _v(0){}

	float _x, _y, _z;
	float _nx, _ny, _nz;
	DWORD _color;
	float _u, _v;
	static DWORD FVF;
};