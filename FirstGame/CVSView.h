#ifndef __CVSVIEW_H__
#define __CVSVIEW_H__

#include "Header.h"
#include "CDirectx.h"
#include "CGraphics.h"

#if (CONFIG_PLATFORM==PLATFORM_WIN32_VS)

namespace GameTutor
{
	class CVSView
	{
	public:
		CVSView(__INT32 w, __INT32 h, bool fullscreen = false, const char*name = 0);
		virtual ~CVSView();
		void Update();
		static CVSView* s_pInstance;

		__INT32 GetWidth() { return m_iWidth; }
		__INT32 GetHeight() { return m_iHeight; }
		__INT32 IsFullScreen() { return m_isFullScreen; }

		void handleLostGraphicsDevice();
		void releaseAll();
		void resetAll();

	protected:
		__INT32 m_iWidth;
		__INT32 m_iHeight;
		bool m_isFullScreen;
		char *m_strTitle;
		void InitClientWindow();
		void Destroy();

	public:
		HGLRC m_hGLRC;
		HWND m_hwndWindow;
		HDC m_hGameWndDC;
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	protected:
		HRESULT hr;
	};
}
#endif //(CONFIG_PLATFORM==PLATFORM_WIN32_VS)
#endif