#include "CStateLogo.h"
#include "CStateManagement.h"
#include "CGame.h"
#include "Header.h"
#include "CFpscontroller.h"
#include "CStatePoster.h"

CStateLogo::CStateLogo() : GameTutor::CState()
{
	m_iCount = 0;
}

void CStateLogo::Init()
{
	//printf("\nState Logo: Init!");
	Log("\nState Logo: Init");
	m_iCount = 0;
}

void CStateLogo::Update()
{
	m_iCount++;
	if (m_iCount >= 50)
	{
		GameTutor::CStateManagement::GetInstance()->SwitchState(new CStatePoster());
		//GameTutor::CGame::GetInstance()->Exit();
	}
}

void CStateLogo::Render()
{
	Log("State Logo: %d Fps = %d FrameDT = %.9f", 
		m_iCount, 
		GameTutor::CFpsController::GetInstance()->GetRuntimeFps(), 
		GameTutor::CFpsController::GetInstance()->GetFrameDt());

	Trace("State Logo: %d Fps = %d FrameDT = %.9f\n", 
		m_iCount, 
		GameTutor::CFpsController::GetInstance()->GetRuntimeFps(), 
		GameTutor::CFpsController::GetInstance()->GetFrameDt());
}

void CStateLogo::Exit()
{
	Log("\nState Logo: Exit!");
}
