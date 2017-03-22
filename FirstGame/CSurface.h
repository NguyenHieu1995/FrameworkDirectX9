#ifndef __CSURFACE_H__
#define __CSURFACE_H__

#include "Header.h"
#include <string>

#define SURFACE_WIDTH  640
#define SURFACE_HEIGHT  480

class CSurface
{
public:
	CSurface(std::string srcFile, int w = SURFACE_WIDTH, int h = SURFACE_HEIGHT);
	virtual ~CSurface();

public:
	void LoadSurface(
		CONST RECT* destRect,	//Rect Dich
		std::string srcFile,	//Source File Image
		CONST RECT* srcRect,	//Rect Nguon
		D3DCOLOR colorKey = 0); //Mau trong suot cua image
	void Render(
		CONST RECT* srcRect,	//Rect Nguon
		CONST RECT* destRect	//Rect Dich
		);
	IDirect3DSurface9* GetSurface();

protected:
	bool Init(std::string srcFile);
	void Destroy();

private:
	//Kich thuoc Surface
	int m_iWidth; 
	int m_iHeight; 

	IDirect3DSurface9* m_pBackBuffer; //backbuffer
	IDirect3DSurface9* m_pSurface; //Surface
	HRESULT hr;
	D3DXIMAGE_INFO m_ImageInfo;
};

#endif