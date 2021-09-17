#include "BackGround.h"
#include "Config.h"

MyImg* BackGround::m_pBackGround = nullptr;
void BackGround::LoadRes(SDL_Renderer * pRender)
{
	m_pBackGround = new MyImg("res/images/BackGround.bmp", pRender);
}

void BackGround::FreeRes()
{
	delete m_pBackGround;
}

void BackGround::Render(SDL_Renderer * pRender)
{

	m_pBackGround->Render(pRender, m_x, m_y);
	if (m_x < -(m_pBackGround->GetWidth() - Config::W_SCREEN))
		m_pBackGround->Render(pRender, m_pBackGround->GetWidth() + m_x , m_y);
}

BackGround::BackGround()
{
	m_x = 0;
	m_y = 0;
}

BackGround::~BackGround()
{
}
