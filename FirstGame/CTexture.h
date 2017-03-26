#ifndef __CTEXTURE_H__
#define __CTEXTURE_H__

#include "Header.h"
#include <string>

class CTexture
{
public:
	CTexture(std::string srcFile);
	~CTexture();

public:
	void LoadTexture(std::string srcFile);
	void Render();
	LPDIRECT3DTEXTURE9 GetTexture();

protected:
	bool Init();
	void Destroy();

protected:
	LPDIRECT3DTEXTURE9 m_lpTexture;
	D3DXIMAGE_INFO m_infoTexture;
	HRESULT hr;
	LPD3DXSPRITE m_lpSprite;
};

#endif