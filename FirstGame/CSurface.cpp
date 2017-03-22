#include "CSurface.h"
#include "CGraphics.h"

CSurface::CSurface(std::string srcFile, int w, int h)
{
	this->m_iWidth = w;
	this->m_iHeight = h;
	this->Init(srcFile);
}

CSurface::~CSurface()
{
	this->Destroy();
}

bool CSurface::Init(std::string srcFile)
{
	hr = E_FAIL;
	hr = CGraphics::GetInstance()->GetDevice()->CreateOffscreenPlainSurface(
		this->m_iWidth, 
		this->m_iHeight, 
		D3DFMT_X8R8G8B8, 
		D3DPOOL_DEFAULT, 
		&m_pSurface, 
		NULL);

	if (FAILED(hr))
		return false;

	CGraphics::GetInstance()->GetDevice()->GetBackBuffer(
		0, 
		0, 
		D3DBACKBUFFER_TYPE_MONO, 
		&m_pBackBuffer);

	if (FAILED(hr))
		return false;

	/*hr = D3DXGetImageInfoFromFile(srcFile.c_str(), &m_pImageInfo);

	if (FAILED(hr))
		return false;*/

	LoadSurface(NULL, srcFile, NULL, 0);

	return true;
}

void CSurface::LoadSurface(CONST RECT* destRect, std::string srcFile, CONST RECT* srcRect, D3DCOLOR colorKey)
{
	hr = E_FAIL;
	ZeroMemory(&m_ImageInfo, sizeof(m_ImageInfo));
	hr = D3DXLoadSurfaceFromFile(
		m_pSurface,		// con tro quan ly surface
		NULL,			// mac dinh NULL
		destRect,			// hinh chu nhat Dich
		srcFile.c_str(),		// source File anh
		srcRect,			// hinh chu nhat Nguon
		D3DX_DEFAULT,	//
		colorKey,				// Gia tri mau trong suot
		&m_ImageInfo);			// Gia tri chua thong tin cua anh

	if (FAILED(hr))
	{
		Trace("Load Surface Failed!");
	}
	else
	{
		Trace("Load Surface Succeeded!");
	}
}

void CSurface::Render(CONST RECT* srcRect, CONST RECT* destRect)
{
	hr = CGraphics::GetInstance()->GetDevice()->StretchRect(
		m_pSurface, 
		srcRect, 
		m_pBackBuffer, 
		destRect, 
		D3DTEXF_NONE);	
}

void CSurface::Destroy()
{
	//SAFE_RELEASE(m_pBackBuffer);
	m_pBackBuffer = NULL;
	SAFE_RELEASE(m_pSurface);
}

IDirect3DSurface9* CSurface::GetSurface()
{
	return m_pSurface;
}