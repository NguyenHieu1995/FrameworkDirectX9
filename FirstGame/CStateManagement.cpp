#include "CStateManagement.h"
#include "Header.h"

void GameTutor::CStateManagement::Update(bool isPause)
{
	//Check if need switch state
	if (m_pCurrentState != m_pNextState)
	{
		if (m_pCurrentState != nullptr)
		{
			m_pCurrentState->Exit();
			delete m_pCurrentState;
		}

		if (m_pNextState != nullptr)
		{
			m_pNextState->Init();
		}
		m_pCurrentState = m_pNextState;
	}

	//update state
	if (m_pCurrentState != nullptr)
	{
		if (isPause == false)
		{
			m_pCurrentState->Update();
		}
		m_pCurrentState->Render();
	}
}

void GameTutor::CStateManagement::SwitchState(CState * nextState)
{
	m_pNextState = nextState;
}

