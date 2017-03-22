#ifndef __CSTATELOGO_H__
#define __CSTATELOGO_H__

#include "CState.h"
#include "Header.h"

class CStateLogo : public GameTutor::CState
{
public:
	CStateLogo();
	~CStateLogo() {}

	void Init();
	void Update();
	void Render();
	void Exit();

private:
	__INT32 m_iCount;
};

#endif 