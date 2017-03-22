#include "CTexture.h"
#include "CGraphics.h"

CTexture::CTexture(std::string srcFile)
{
	this->Init();
}

CTexture::~CTexture()
{
	this->Destroy();
}

bool CTexture::Init()
{

	return true;
}

void CTexture::Destroy()
{
	SAFE_RELEASE(m_lpTexture);
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

	hr = D3DXCreateTextureFromFile(
		CGraphics::GetInstance()->GetDevice(),
		srcFile.c_str(),
		&m_lpTexture);

	if (FAILED(hr))
	{
		Trace("Create Texture Failed!");
		return;
	}
}

void CTexture::Render()
{

}

LPDIRECT3DTEXTURE9 CTexture::GetTexture()
{
	return m_lpTexture;
}