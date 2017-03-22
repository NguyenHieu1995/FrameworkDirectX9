#ifndef __CFPSCONTROLLER_H__
#define __CFPSCONTROLLER_H__

#include "Header.h"
#include "CSingleton.h"

#define DEFAULT_LIMIT_FPS 60

namespace GameTutor
{
	class CFpsController : public CSingleton<CFpsController>
	{
		
		friend class CSingleton<CFpsController>;

	public:
		virtual ~CFpsController() {}

		void SetLimitFps(unsigned int limitFps); //set gioi han (fps default 1)
		void BeginCounter(); //Bat dau bo dem
		void EndCounter(); //Ket thuc bo dem

		double GetFrameDt() { return m_iFrameDt; } //Tra ve thoi gian 1 frame
		__INT32 GetRuntimeFps() { return (m_iFrameDt) ? int(1000.0f / m_iFrameDt) : 0; } //Tra ve fps thuc te

	protected:
		CFpsController(); 

	protected:
		__INT32 m_iLimitFps; //Gioi han Fps
		double m_iLimitFrameDt; //Gioi han thoi gian thuc hien 1 frame
		double m_iFrameDt; //Thoi gian thuc hien xong 1 frame
	
	protected:
		//__UINT64 m_iStartTime;
		LARGE_INTEGER m_iTimeStart;
		LARGE_INTEGER m_iTimeEnd;
		LARGE_INTEGER m_iFrequency;
		
	};
}

#endif