#include "FireBallWork.h"
#include "TileMap.h"
MyImg* FireBallWork::s_pImgFireBallWork[3] = { nullptr,nullptr ,nullptr };
void FireBallWork::LoadRes(SDL_Renderer * pRenderer)
{
	s_pImgFireBallWork[0] = new MyImg("res/images/fireballwork/fireballwork0.bmp", pRenderer);
	s_pImgFireBallWork[1] = new MyImg("res/images/fireballwork/fireballwork1.bmp", pRenderer);
	s_pImgFireBallWork[2] = new MyImg("res/images/fireballwork/fireballwork2.bmp", pRenderer);
}

void FireBallWork::FreeRes()
{
	delete s_pImgFireBallWork[0];
	delete s_pImgFireBallWork[1];
	delete s_pImgFireBallWork[2];
}

void FireBallWork::Update(float dt)
{
	m_Animation.Update();
	if (m_Animation.bAlready()) {
		m_bDelete = true;
	}
}

void FireBallWork::Render(SDL_Renderer * pRender)
{
	m_Animation.GetCurImage()->Render(pRender,e_pTileMap->GetMapX() + m_x, e_pTileMap->GetMapY() + m_y);
}

bool FireBallWork::bDelete()
{
	return m_bDelete;
}

FireBallWork::FireBallWork(TileMap * pTileMap, int x, int y)
{
	e_pTileMap = pTileMap;
	m_x = x;
	m_y = y;
	m_Animation.SetFrames(s_pImgFireBallWork, 0, 3, 80);
	m_bDelete = false;
}

FireBallWork::~FireBallWork()
{
}
