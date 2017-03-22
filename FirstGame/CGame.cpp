#include "CGame.h"
#include "CStateManagement.h"
#include "Header.h"
#include "CDevice.h"
#include "CFpscontroller.h"
#include "CViewController.h"

GameTutor::CGame::CGame() : m_eStatus(EGSTATUS_INIT)
{
	SetInstance(this);
	m_isInit = false;
}

LRESULT GameTutor::CGame::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_isInit)     // Do not process messages if not initialized    
	{
		switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);    // Tell Windows to kill this program                
			return 0;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:	// Key down                
			//input->keyDown(wParam);
			return 0;
		case WM_KEYUP:
		case WM_SYSKEYUP: // Key up                
			//input->keyUp(wParam);
			return 0;
		case WM_CHAR:
			// Character entered                
			//input->keyIn(wParam);
			return 0;
		case WM_MOUSEMOVE: // Mouse moved                
			//input->mouseIn(lParam);
			return 0;
		case WM_INPUT: // Raw mouse data in                
			//input->mouseRawIn(lParam);
			return 0;
		case WM_LBUTTONDOWN: // Left mouse button down                
			//input->setMouseLButton(true);
			//input->mouseIn(lParam);
			return 0;
		case WM_LBUTTONUP: // Left mouse button up                
			//input->setMouseLButton(false);
			//input->mouseIn(lParam);
			return 0;
		case WM_MBUTTONDOWN:                // Middle mouse button down                
			//input->setMouseMButton(true);
			//input->mouseIn(lParam);
			return 0;
		case WM_MBUTTONUP:                  // Middle mouse button up                
			//input->setMouseMButton(false);
			//input->mouseIn(lParam);
			return 0;
		case WM_RBUTTONDOWN:                // Right mouse button down                
			//input->setMouseRButton(true);
			//input->mouseIn(lParam);
			return 0;
		case WM_RBUTTONUP:                  // Right mouse button up                
			//input->setMouseRButton(false);
			//input->mouseIn(lParam);
			return 0;
		case WM_XBUTTONDOWN: case WM_XBUTTONUP: // Mouse X button down/up                
			//input->setMouseXButton(wParam);
			//input->mouseIn(lParam);
			return 0;
		case WM_DEVICECHANGE:               // Check for controllers                
			//input->checkControllers();
			return 0;
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam); // Let Windows                                                        // handle it 
	return LRESULT();
}

GameTutor::CGame::~CGame()
{
}

void GameTutor::CGame::Update()
{
	switch (m_eStatus)
	{
	case EGSTATUS_INIT:
		this->Init();
		m_eStatus = EGSTATUS_RUNNING;
		break;

	case EGSTATUS_RUNNING:
	case EGSTATUS_PAUSED:
		CFpsController::GetInstance()->BeginCounter();
		CStateManagement::GetInstance()->Update(m_eStatus == EGSTATUS_PAUSED);
		CFpsController::GetInstance()->EndCounter();
		break;

	case EGSTATUS_EXIT:
		//force clean up current state
		CStateManagement::GetInstance()->SwitchState(0);
		CStateManagement::GetInstance()->Update(false);
		Destroy();
		break;

	default:
		break;
	}
}

/*
void GameTutor::CGame::Run()
{
	this->Init();

	// Init DirectX
	CDirectx::GetInstance()->Init();

	//init view
	if (!GameTutor::CViewController<VIEWCLASS>::GetInstance())
	{
		CViewController<VIEWCLASS>::GetInstance()->CreateView(640, 480);
	}

	while (m_isAlived)
	{
		CFpsController::GetInstance()->BeginCounter();

		if (m_isPaused)
		{
			CStateManagement::GetInstance()->Update(true);
		}
		else
		{
			CStateManagement::GetInstance()->Update(false);
		}

		CViewController<VIEWCLASS>::GetInstance()->GetView()->Update();

		CFpsController::GetInstance()->EndCounter();
	}

	//force clean up current state
	CStateManagement::GetInstance()->SwitchState(0);
	CStateManagement::GetInstance()->Update(false);

	//Destroy view
	delete CViewController<VIEWCLASS>::GetInstance();

	//Destroy DirectX
	CDirectx::GetInstance()->Destroy();
	delete CDirectx::GetInstance();

	this->Destroy();
}
*/

void GameTutor::CGame::Pause()
{
	m_eStatus = EGSTATUS_PAUSED;
}

void GameTutor::CGame::Resume()
{
	m_eStatus = EGSTATUS_RUNNING;
}

void GameTutor::CGame::Exit()
{
	m_eStatus = EGSTATUS_EXIT;
}