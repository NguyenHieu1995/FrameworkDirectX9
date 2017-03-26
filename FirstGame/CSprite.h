#ifndef __CSPRITE_H__
#define __CSPRITE_H__

#include "Header.h"

class CSprite
{
public:
	CSprite();
	~CSprite();

public:
	bool Init();
	void Destroy();
	void Render();
	void Update();

protected:
	LPD3DXSPRITE m_lpSprite;

};

#endif