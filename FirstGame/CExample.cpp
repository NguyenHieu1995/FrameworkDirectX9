#include "CExample.h"
#include <stdio.h>
#include "CStateManagement.h"
#include "CStateLogo.h"
#include "Header.h"

void CExample::Init()
{
	//Init Game
	printf("\nInit Game!");

	// Init State
	CStateManagement::GetInstance()->GetInstance()->SwitchState(new CStateLogo());
	m_isInit = true;
}

void CExample::Destroy()
{
	//Destroy Game
	printf("\nDestroy Game!");

	// Destroy State
	if(CStateManagement::IsAvailable())
		CStateManagement::FreeInstance();
}
