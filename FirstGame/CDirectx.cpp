#include "CDirectx.h"

CDirectx::CDirectx(void)
{
	m_lpDirect3D = nullptr;
}

void CDirectx::Destroy(void)
{
	SAFE_RELEASE(m_lpDirect3D);
}

bool CDirectx::Init(void)
{
	this->m_lpDirect3D = Direct3DCreate9(D3D_SDK_VERSION);//Direct3DCreate9(D3D_SDK_VERSION);

	if (this->m_lpDirect3D)
	{
		return true;
	}

	return false;
}

