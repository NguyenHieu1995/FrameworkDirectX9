#include "CVSView.h"
#include "CGame.h"
#include "CDevice.h"
#include <string.h>
#include <Strsafe.h>
#include "CDirectx.h"

#if (CONFIG_PLATFORM==PLATFORM_WIN32_VS)

namespace GameTutor
{
	CVSView* CVSView::s_pInstance = 0;

	//----------------------------------------
	// Constructor
	//----------------------------------------

	CVSView::CVSView(__INT32 w, __INT32 h, bool fullscreen, const char * name) :m_iWidth(w),
		m_iHeight(h), m_isFullScreen(fullscreen),
		m_hGLRC(NULL), m_hwndWindow(NULL), m_hGameWndDC(NULL)
	{
		s_pInstance = this;
		if (name)
		{
			m_strTitle = new char[strlen(name) + 1];
			//strcpy(m_strTitle, name);
			strcpy_s(m_strTitle, strlen(name) + 1, name);
		}
		else
		{
			char *xname = "Untitle";
			m_strTitle = new char[strlen(xname) + 1];
			strcpy_s(m_strTitle, strlen(xname) + 1, xname);
		}

		CDirectx::GetInstance()->Init();
		//CGraphics::GetInstance();

		InitClientWindow();
		CDevice::GetInstance()->SleepEx(1000); //sleep to avoid lag when launch game
	}

	//----------------------------------------
	// Destructor
	//----------------------------------------
	CVSView::~CVSView()
	{
		Destroy();
		SAFE_DELETE(m_strTitle);
	}

	//----------------------------------------
	// Init win32 client window
	//----------------------------------------
	void CVSView::InitClientWindow()
	{
		//get current instant
		HINSTANCE hInstance = GetModuleHandle(0);

		//----------------------------------
		// init WNDCLASSEX
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = NULL;
		wcex.cbWndExtra = NULL;
		wcex.hInstance = hInstance;
		wcex.hIcon = NULL;//LoadIcon(hInstance, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = "main";
		wcex.hIconSm = NULL;//LoadIcon(wcex.hInstance, IDI_APPLICATION);

		if (!RegisterClassEx(&wcex))
		{
			return; // ERR, SO QUIT
		}

		//----------------------------------
		// init HWND
		DWORD style;

		if (m_isFullScreen)
			style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
		else
			style = WS_OVERLAPPEDWINDOW;

		RECT clientSize;
		clientSize.top = 0;
		clientSize.left = 0;
		clientSize.right = m_iWidth;
		clientSize.bottom = m_iHeight;
		AdjustWindowRect(&clientSize, style, FALSE);

		const int realWidth = clientSize.right - clientSize.left;
		const int realHeight = clientSize.bottom - clientSize.top;

		int windowLeft = (GetSystemMetrics(SM_CXSCREEN) - realWidth) / 2;
		int windowTop = (GetSystemMetrics(SM_CYSCREEN) - realHeight) / 2;

		if (!m_isFullScreen)
		{
			m_hwndWindow = CreateWindow("main", m_strTitle,
				style, windowLeft, windowTop,
				realWidth, realHeight, NULL, NULL,
				hInstance, NULL);
		}
		else
		{
			m_hwndWindow = CreateWindow("main", m_strTitle,
				style, 0, 0,
				m_iWidth, m_iHeight, NULL, NULL,
				hInstance, NULL);
		}

		if (!m_hwndWindow)
			return;

		m_hGameWndDC = GetDC(m_hwndWindow);

		ShowWindow(m_hwndWindow, SW_SHOW);
		UpdateWindow(m_hwndWindow);

		if (!m_isFullScreen)
		{
			MoveWindow(m_hwndWindow, windowLeft,
				windowTop, realWidth, realHeight, TRUE);
		}
		SetActiveWindow(m_hwndWindow);
		SetForegroundWindow(m_hwndWindow);

		if (m_isFullScreen)
		{
			DEVMODE dm;
			memset(&dm, 0, sizeof(dm));
			dm.dmSize = sizeof(DEVMODE);
			dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
			dm.dmPelsWidth = m_iWidth;
			dm.dmPelsHeight = m_iHeight;
			dm.dmBitsPerPel = 32;
			ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
		}


		//
		// Init Graphics
		//
		CGraphics::GetInstance()->Init(m_iWidth, m_iHeight, m_hwndWindow, m_isFullScreen);

	}

	//----------------------------------------
	// update win32 message
	//----------------------------------------
	void CVSView::Update()
	{
		while (true)
		{
			//Xoa bo dem backbuffer
			CGraphics::GetInstance()->ClearBackbuffer();
			
			// handle win32 message
			MSG msg;
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				if (msg.hwnd == m_hwndWindow)
				{
					WndProc(m_hwndWindow, msg.message, msg.wParam, msg.lParam);
				}
			}
			CGame::GetInstance()->Update();

			if (!CGame::GetInstance()->IsAlive())
			{
				//Destroy Game
				if (CGame::IsAvailable())
				{
					CGame::FreeInstance();
				}

				return;
			}

			//update Graphics
			CGraphics::GetInstance()->ShowBackbuffer();
			DispatchMessage(&msg);
		}
	}

	//----------------------------------------
	// Destroy win32 window
	//----------------------------------------
	void CVSView::Destroy()
	{
		// Destroy Graphics
		CGraphics::GetInstance()->Destroy();

		CDirectx::GetInstance()->Destroy();
		delete CDirectx::GetInstance();

		if (m_isFullScreen)
		{
			ChangeDisplaySettings(NULL, 0);
		}
	}


	//----------------------------------------
	// Win32 Message Callback
	//----------------------------------------
	//TCHAR ch = ' ';    // Character entered

	LRESULT CALLBACK CVSView::WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		HDC hdc;                   // handle to device context 
		TEXTMETRIC tm;             // structure for text metrics	
		static DWORD dwCharX;      // average width of characters 
		static DWORD dwCharY;      // height of characters 
		static DWORD dwClientX;    // width of client area 
		static DWORD dwClientY;    // height of client area 
		static DWORD dwLineLen;    // line length 
		static DWORD dwLines;      // text lines in client area 
		static int nCaretPosX = 0; // horizontal position of caret 
		static int nCaretPosY = 0; // vertical position of caret 
		static int nCharWidth = 0; // width of a character 
		static int cch = 0;        // characters in buffer 
		static int nCurChar = 0;   // index of current character 
		static PTCHAR pchInputBuf; // input buffer 
		int i, j;                  // loop counters 
		int cCR = 0;               // count of carriage returns 
		int nCRIndex = 0;          // index of last carriage return 
		int nVirtKey;              // virtual-key code 
		TCHAR szBuf[128];          // temporary buffer 
		TCHAR ch;                  // current character 
		PAINTSTRUCT ps;            // required by BeginPaint 
		RECT rc;                   // output rectangle for DrawText 
		SIZE sz;                   // string dimensions 
		COLORREF crPrevText;       // previous text color 
		COLORREF crPrevBk;         // previous background color
		size_t *pcch;
		HRESULT hResult;

		switch (message)
		{
		case WM_CREATE:

			// Get the metrics of the current font
			hdc = GetDC(hwnd);
			GetTextMetrics(hdc, &tm);
			ReleaseDC(hwnd, hdc);

			// Save average character width and height
			dwCharX = tm.tmAveCharWidth;
			dwCharY = tm.tmHeight;

			// Allocate a buffer to store keyboard input
			pchInputBuf = (LPTSTR)GlobalAlloc(GPTR, BUFSIZE * sizeof(TCHAR));

			return 0;

		case WM_SIZE:
			// Save the new width and height of the client area. 
			dwClientX = LOWORD(lparam);
			dwClientY = HIWORD(lparam);

			// Calculate the maximum width of a line and the 
			// maximum number of lines in the client area. 
			dwLineLen = dwClientX - dwCharX;
			dwLines = dwClientY / dwCharY;
			break;

		case WM_SETFOCUS:
			// Create, position, and display the caret when the 
			// window receives the keyboard focus. 
			CreateCaret(hwnd, (HBITMAP)1, 0, dwCharY);
			SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
			ShowCaret(hwnd);
			break;

		case WM_KILLFOCUS:
			// Hide and destroy the caret when the window loses the 
			// keyboard focus. 
			HideCaret(hwnd);
			DestroyCaret();
			break;

		case WM_CHAR:
			// check if current location is close enough to the
			// end of the buffer that a buffer overflow may
			// occur. If so, add null and display contents. 
			if (cch > BUFSIZE - 5)
			{
				pchInputBuf[cch] = 0x00;
				SendMessage(hwnd, WM_PAINT, 0, 0);
			}
			switch (wparam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				return 0;

			case 0x08:  // backspace 
			case 0x0A:  // linefeed 
				MessageBeep((UINT)-1);
				return 0;

			case 0x09:  // tab 

						// Convert tabs to four consecutive spaces. 

				for (i = 0; i < 4; i++)
					SendMessage(hwnd, WM_CHAR, 0x20, 0);
				return 0;

			case 0x0D:  // carriage return 
						// Record the carriage return and position the 
						// caret at the beginning of the new line.

				pchInputBuf[cch++] = 0x0D;
				nCaretPosX = 0;
				nCaretPosY += 1;
				break;

			default:    // displayable character 
				ch = (TCHAR)wparam;
				HideCaret(hwnd);

				// Retrieve the character's width and output 
				// the character. 

				hdc = GetDC(hwnd);
				GetCharWidth32(hdc, (UINT)wparam, (UINT)wparam,
					&nCharWidth);
				TextOut(hdc, nCaretPosX, nCaretPosY * dwCharY,
					&ch, 1);
				ReleaseDC(hwnd, hdc);

				// Store the character in the buffer.

				pchInputBuf[cch++] = ch;

				// Calculate the new horizontal position of the 
				// caret. If the position exceeds the maximum, 
				// insert a carriage return and move the caret 
				// to the beginning of the next line. 

				nCaretPosX += nCharWidth;
				if ((DWORD)nCaretPosX > dwLineLen)
				{
					nCaretPosX = 0;
					pchInputBuf[cch++] = 0x0D;
					++nCaretPosY;
				}
				nCurChar = cch;
				ShowCaret(hwnd);
				break;
			}
			SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
			break;

		case WM_KEYDOWN:
			switch (wparam)
			{
			case VK_LEFT:   // LEFT ARROW 

							// The caret can move only to the beginning of 
							// the current line. 

				if (nCaretPosX > 0)
				{
					HideCaret(hwnd);

					// Retrieve the character to the left of 
					// the caret, calculate the character's 
					// width, then subtract the width from the 
					// current horizontal position of the caret 
					// to obtain the new position. 

					ch = pchInputBuf[--nCurChar];
					hdc = GetDC(hwnd);
					GetCharWidth32(hdc, ch, ch, &nCharWidth);
					ReleaseDC(hwnd, hdc);
					nCaretPosX = max(nCaretPosX - nCharWidth,
						0);
					ShowCaret(hwnd);
				}
				break;

			case VK_RIGHT:  // RIGHT ARROW 
							// Caret moves to the right or, when a carriage 
							// return is encountered, to the beginning of 
							// the next line. 

				if (nCurChar < cch)
				{
					HideCaret(hwnd);

					// Retrieve the character to the right of 
					// the caret. If it's a carriage return, 
					// position the caret at the beginning of 
					// the next line. 
					ch = pchInputBuf[nCurChar];
					if (ch == 0x0D)
					{
						nCaretPosX = 0;
						nCaretPosY++;
					}

					// If the character isn't a carriage 
					// return, check to see whether the SHIFT 
					// key is down. If it is, invert the text 
					// colors and output the character. 
					else
					{
						hdc = GetDC(hwnd);
						nVirtKey = GetKeyState(VK_SHIFT);
						if (nVirtKey & SHIFTED)
						{
							crPrevText = SetTextColor(hdc,
								RGB(255, 255, 255));
							crPrevBk = SetBkColor(hdc,
								RGB(0, 0, 0));
							TextOut(hdc, nCaretPosX,
								nCaretPosY * dwCharY,
								&ch, 1);
							SetTextColor(hdc, crPrevText);
							SetBkColor(hdc, crPrevBk);
						}

						// Get the width of the character and 
						// calculate the new horizontal 
						// position of the caret. 
						GetCharWidth32(hdc, ch, ch, &nCharWidth);
						ReleaseDC(hwnd, hdc);
						nCaretPosX = nCaretPosX + nCharWidth;
					}
					nCurChar++;
					ShowCaret(hwnd);
					break;
				}
				break;

			case VK_UP:     // UP ARROW 
			case VK_DOWN:   // DOWN ARROW 
				MessageBeep((UINT)-1);
				return 0;

			case VK_HOME:   // HOME 
							// Set the caret's position to the upper left 
							// corner of the client area. 

				nCaretPosX = nCaretPosY = 0;
				nCurChar = 0;
				break;

			case VK_END:    // END  

							// Move the caret to the end of the text. 

				for (i = 0; i < cch; i++)
				{
					// Count the carriage returns and save the 
					// index of the last one. 

					if (pchInputBuf[i] == 0x0D)
					{
						cCR++;
						nCRIndex = i + 1;
					}
				}
				nCaretPosY = cCR;

				// Copy all text between the last carriage 
				// return and the end of the keyboard input 
				// buffer to a temporary buffer. 
				for (i = nCRIndex, j = 0; i < cch; i++, j++)
					szBuf[j] = pchInputBuf[i];
				szBuf[j] = TEXT('\0');

				// Retrieve the text extent and use it 
				// to set the horizontal position of the 
				// caret. 
				hdc = GetDC(hwnd);
				pcch = new size_t;
				hResult = StringCchLength(szBuf, 128, pcch);
				if (FAILED(hResult))
				{
					// TODO: write error handler
				}
				GetTextExtentPoint32(hdc, szBuf, *pcch,
					&sz);
				nCaretPosX = sz.cx;
				ReleaseDC(hwnd, hdc);
				nCurChar = cch;
				delete pcch;
				break;

			default:
				break;
			}
			SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
			break;

		case WM_PAINT:
			if (cch == 0)       // nothing in input buffer 
				break;

			hdc = BeginPaint(hwnd, &ps);
			HideCaret(hwnd);

			// Set the clipping rectangle, and then draw the text 
			// into it. 

			SetRect(&rc, 0, 0, dwLineLen, dwClientY);
			DrawText(hdc, pchInputBuf, -1, &rc, DT_LEFT);

			ShowCaret(hwnd);
			EndPaint(hwnd, &ps);
			break;

		case WM_DESTROY: // killing the window
			CGame::GetInstance()->Exit();
			PostQuitMessage(0);
			GlobalFree((HGLOBAL)pchInputBuf);
			UnregisterHotKey(hwnd, 0xAAAA);
			return 0;

		default:
			return DefWindowProc(hwnd, message, wparam, lparam);
		}
		return NULL;	
	}

	//======================================================================== 
	// Handle lost graphics device 
	//======================================================================== 
	void CVSView::handleLostGraphicsDevice()
	{    // Test for and handle lost device    
		hr = CGraphics::GetInstance()->GetDeviceState();
		if (FAILED(hr))            // If graphics device is not in a valid state    
		{        // If the device is lost and not available for reset        
			if (hr == D3DERR_DEVICELOST)
			{
				Sleep(100);       // Yield CPU time (100 milliseconds)            
				return;
			}        // The device was lost but is now available for reset        
			else
				if (hr == D3DERR_DEVICENOTRESET)
				{
					releaseAll();
					hr = CGraphics::GetInstance()->Reset(); // Attempt to reset graphics device            
					if (FAILED(hr))          // If reset failed               
						return;
					resetAll();
				}
				else
					return;                 // Other device error    
		}
	}
	void CVSView::releaseAll()
	{
		CGraphics::GetInstance()->Destroy();
		CDirectx::GetInstance()->Destroy();
	}
	void CVSView::resetAll()
	{
		CDirectx::GetInstance()->Init();
		CGraphics::GetInstance()->Reset();
	}
}

#endif