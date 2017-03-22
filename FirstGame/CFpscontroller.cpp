#include "CFpsController.h"
#include "CDevice.h"

namespace GameTutor
{
	CFpsController::CFpsController() : m_iLimitFps(0), m_iLimitFrameDt(0.0f), m_iFrameDt(0.0f)
	{
		SetLimitFps(DEFAULT_LIMIT_FPS);
		//m_iStartTime = 0;
	}

	void CFpsController::SetLimitFps(unsigned int limitFps)
	{
		m_iLimitFps = limitFps;
		m_iLimitFrameDt = 1000.0f / limitFps;
	}

	void CFpsController::BeginCounter()
	{
		//m_iStartTime = CDevice::GetInstance()->GetTimer();
		QueryPerformanceCounter(&m_iTimeStart);
		QueryPerformanceFrequency(&m_iFrequency);
	}

	void CFpsController::EndCounter()
	{
		QueryPerformanceCounter(&m_iTimeEnd);
		//long Endtime = CDevice::GetInstance()->GetTimer();

		//int Dt = int(Endtime - m_iStartTime);
		double Dt = (((double)m_iTimeEnd.QuadPart - (double)m_iTimeStart.QuadPart) / m_iFrequency.QuadPart) * 1000.0f;

		if (Dt < m_iLimitFrameDt)
		{
			m_iFrameDt = m_iLimitFrameDt;
			CDevice::GetInstance()->SleepEx(m_iLimitFrameDt - Dt);
		}
		else
		{
			m_iFrameDt = Dt;
			CDevice::GetInstance()->SleepEx(1);
		}

	}
}

