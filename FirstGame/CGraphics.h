#ifndef __CGRAPHICS_H__
#define __CGRAPHICS_H__

#ifdef _DEBUG 
#define D3D_DEBUG_INFO 
#endif

#include "Header.h"
#include "CGameError.h"
#include "CSingleton.h"
// Color defines 
#define COLOR_ARGB DWORD 
#define SETCOLOR_ARGB(a,r,g,b) \ ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff))) 

class CGraphics : public CSingleton<CGraphics>
{

	friend class CSingleton<CGraphics>;

public:
	CGraphics();
	virtual ~CGraphics();

public:
	bool Init(__INT32 width, __INT32 height, HWND hwnd, bool fullScreen); //Khoi tao
	void Destroy(); // Huy
	HRESULT ShowBackbuffer(); //load buffer
	void ClearBackbuffer();
	bool IsAdapterCompatible();
	bool InitD3dpp();
	HRESULT GetDeviceState();
	LPDIRECT3DDEVICE9 GetDevice();
	HRESULT Reset();

protected:
	LPDIRECT3DDEVICE9 m_lpDirect3DDevice;
	HRESULT result;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE pMode;

protected:
	__INT32 m_iWidth;
	__INT32 m_iHeight;
	bool m_isFullScreen;
	HWND m_hwnd;


};

#endif