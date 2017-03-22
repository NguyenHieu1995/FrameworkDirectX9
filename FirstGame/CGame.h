#ifndef __CGAME_H__
#define __CGAME_H__

#include "CSingleton.h"
#include "Header.h"

namespace GameTutor
{
	enum EGameStatus {
		EGSTATUS_INIT = 0,
		EGSTATUS_RUNNING,
		EGSTATUS_PAUSED,
		EGSTATUS_EXIT
	};

	class CGame : public CAbsSingleton<CGame>
	{

	public:
		virtual ~CGame();
		virtual void Update();
		//virtual void Run(); // Quan ly vong lap chinh cua game
		virtual void Exit(); // Yeu cau ket thuc game. Duoc goi khi can ket thuc game
		virtual void Pause(); //Tam dung game
		virtual void Resume(); //Khoi phuc game sau khi tam dung
		bool IsAlive() { return (m_eStatus != EGSTATUS_EXIT); }
		bool IsPause() { return (m_eStatus == EGSTATUS_PAUSED); }

	protected:
		CGame();
		virtual void Init() = 0; // Thiet lap cac tham so cho game
		virtual void Destroy() = 0; // Huy game. Goi truoc khi ket thuc game, 
									// dung de thu hoi vung nho, giai phong thiet bi chiem giu, ...

	protected:
		bool m_isAlived; //cho biet game con song hay khong (do ham init va exit quan ly)
		bool m_isPaused; //cho biet game co dang pause khong (do ham pause va resume quan ly)
		bool m_isInit;

	protected:
		enum EGameStatus m_eStatus;

	public: //
		LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	};
}

#endif 