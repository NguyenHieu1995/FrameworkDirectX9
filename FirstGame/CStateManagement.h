#ifndef __CSTATEMANAGEMENT_H__
#define __CSTATEMANAGEMENT_H__

#include "CState.h"
#include "CSingleton.h"

namespace GameTutor
{
	class CStateManagement : public CSingleton<CStateManagement>
	{
		friend class CSingleton<CStateManagement>;
		
	protected:
		CState* m_pCurrentState;
		CState* m_pNextState;

	public:
		void Update(bool isPause);
		void SwitchState(CState* nextState);
		
	protected:
		CStateManagement() : m_pCurrentState(nullptr), m_pNextState(nullptr) {}

	};
}

#endif 