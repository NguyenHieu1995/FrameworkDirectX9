//Khoi tao bien DirectX 9
#ifndef __CDIRECTX9_H__
#define __CDIRECTX9_H__

#include "Header.h"
#include "CSingleton.h"

class CDirectx : public CSingleton<CDirectx>
{
	friend class CSingleton<CDirectx>;

public:
	CDirectx(void);
	virtual ~CDirectx(void) {}

public:
	bool Init(void); //Khoi tao bien directX
	void Destroy(void); //Giai phong bien DirectX
	LPDIRECT3D9 GetDirectX() { return m_lpDirect3D; } //tra ve bien directx


protected:
	LPDIRECT3D9 m_lpDirect3D;

};

#endif 