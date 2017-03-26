#include "CTexture.h"
#include "CGraphics.h"

CTexture::CTexture(std::string srcFile)
{
	if (this->Init())
	{
		LoadTexture(srcFile);
	}
}

CTexture::~CTexture()
{
	this->Destroy();
}

bool CTexture::Init()
{
	this->m_lpSprite = nullptr;
	hr = D3DXCreateSprite(CGraphics::GetInstance()->GetDevice(),
		&this->m_lpSprite);

	if (FAILED(hr))
		return false;

	return true;
}

void CTexture::Destroy()
{
	SAFE_RELEASE(m_lpTexture);
	SAFE_RELEASE(m_lpSprite);
}

void CTexture::LoadTexture(std::string srcFile)
{
	hr = E_FAIL;

	ZeroMemory(&m_infoTexture, sizeof(m_infoTexture));
	hr = D3DXGetImageInfoFromFile(srcFile.c_str(), &m_infoTexture); //Lay thong tin hinh anh

	if (FAILED(hr))
	{
		Trace("Load anh Texture Failed!");
		return;
	}

	hr = D3DXCreateTextureFromFileEx(
		CGraphics::GetInstance()->GetDevice(),
		srcFile.c_str(),
		m_infoTexture.Width,
		m_infoTexture.Height,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, 
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		NULL,
		NULL,
		&m_lpTexture);

	if (FAILED(hr))
	{
		Trace("Create Texture Failed!");
		return;
	}
}

void CTexture::Render()
{
	if (SUCCEEDED(this->m_lpSprite->Begin(D3DXSPRITE_ALPHABLEND)))
	{

		hr = this->m_lpSprite->Draw(
			this->m_lpTexture,
			NULL,
			NULL,
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255)
			);

		if (FAILED(hr))
			MessageBox(NULL, "Draw Texture Failed", NULL, NULL);

		this->m_lpSprite->End();
	}
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture()
{
	return m_lpTexture;
}