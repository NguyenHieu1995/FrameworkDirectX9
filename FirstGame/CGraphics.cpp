#include "CGraphics.h"
#include "CDirectx.h"
#include "CGameError.h"

CGraphics::CGraphics()
{
	m_lpDirect3DDevice = NULL;
	result = E_FAIL;
}

CGraphics::~CGraphics()
{

}

bool CGraphics::Init(__INT32 width, __INT32 height, HWND hwnd, bool fullScreen)
{
	//
	// Init D3D presentation parameters 
	//
	if (!hwnd)
		return false;

	m_iWidth = width;
	m_iHeight = height;
	m_hwnd = hwnd;
	m_isFullScreen = fullScreen;

	InitD3dpp();
	                                                                       
	// Determine if graphics card supports harware texturing and lighting     
	// and vertex shaders                                                     
	D3DCAPS9 caps;                                                            
	DWORD behavior;                                                           
	result = CDirectx::GetInstance()->GetDirectX()->GetDeviceCaps(D3DADAPTER_DEFAULT,                                                       
		D3DDEVTYPE_HAL, &caps);                  
	// If device doesn't support HW T&L or doesn't support 1.1 vertex         
	// shaders in hardware, then switch to software vertex processing.        
	if( (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||                       
		caps.VertexShaderVersion < D3DVS_VERSION(1,1) )                        
		// Use software-only processing                                           
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;                       
	else                                                                          
		// Use hardware-only processing                                           
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING; 

	result = CDirectx::GetInstance()->GetDirectX()->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		behavior,
		&d3dpp,
		&m_lpDirect3DDevice);

	if (FAILED(result))
		throw(CGameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D device"));

	if (FAILED(this->m_lpDirect3DDevice))
	{
		return false;
	}
	return true;
}


void CGraphics::Destroy()
{
	SAFE_RELEASE(this->m_lpDirect3DDevice);
}

//
// Dislay the backbuffer
//
HRESULT CGraphics::ShowBackbuffer()
{
	result = E_FAIL;    // Default to fail, replace on success    
						// (This function will be moved in later versions)    
						// Clear the backbuffer to lime green    
	result = m_lpDirect3DDevice->Present(NULL, NULL, NULL, NULL);
	return result;
}

void CGraphics::ClearBackbuffer()
{
	m_lpDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 0), 0.0f, 0); // Display backbuffer to screen   
}

//======================================================================== 
// Checks the adapter to see if it is compatible with the BackBuffer 
// height, width, and refresh rate specified in d3dpp. Fills in the pMode 
// structure with the format of the compatible mode, if found. 
// Pre: d3dpp is initialized. 
// Post: Returns true if compatible mode found and pMode structure is 
// filled. // Returns false if no compatible mode found. 
//======================================================================== 
bool CGraphics::IsAdapterCompatible()
{
	UINT modes = CDirectx::GetInstance()->GetDirectX()->GetAdapterModeCount(D3DADAPTER_DEFAULT, d3dpp.BackBufferFormat);
	for (int i = 0; i < (modes - 1); i++)
	{
		result = CDirectx::GetInstance()->GetDirectX()->EnumAdapterModes(D3DADAPTER_DEFAULT, d3dpp.BackBufferFormat, i, &pMode);
		if (pMode.Height == d3dpp.BackBufferHeight &&            
			pMode.Width == d3dpp.BackBufferWidth &&            
			pMode.RefreshRate >= d3dpp.FullScreen_RefreshRateInHz)            
			return true;
	}    return false;
}

bool CGraphics::InitD3dpp()
{
	try
	{
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.BackBufferCount = 1;

		if (m_isFullScreen)// If fullscreen
		{
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;  // 24-bit color        
		}
		else
		{
			d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;   // Use desktop  
		}

		d3dpp.BackBufferHeight = m_iHeight;
		d3dpp.BackBufferWidth = m_iWidth;
		d3dpp.Windowed = (!m_isFullScreen);
		d3dpp.hDeviceWindow = m_hwnd;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	catch (...)
	{
		throw(CGameError(gameErrorNS::FATAL_ERROR, "Error initializing D3D presentation parameters"));
		return false;
	}

	if (m_isFullScreen)      // If fullscreen mode                                 
	{
		if (IsAdapterCompatible())   // Is the adapter compatible                      
									 // Set the refresh rate with a compatible one                             
			d3dpp.FullScreen_RefreshRateInHz = pMode.RefreshRate;
		else
		{
			throw(CGameError(gameErrorNS::FATAL_ERROR,
				"The graphics device does not support the specified resolution and/or format."));
			return false;
		}
	}

	return true;
}

HRESULT CGraphics::GetDeviceState()
{
	result = E_FAIL;    // Default to fail, replace on success    
	if (m_lpDirect3DDevice == NULL)        
		return  result;    
	result = m_lpDirect3DDevice->TestCooperativeLevel();    
	return result; 
}

HRESULT CGraphics::Reset()
{
	result = E_FAIL;
	InitD3dpp();
	result = m_lpDirect3DDevice->Reset(&d3dpp);
	return E_NOTIMPL;
}


LPDIRECT3DDEVICE9 CGraphics::GetDevice()
{
	return m_lpDirect3DDevice;
}