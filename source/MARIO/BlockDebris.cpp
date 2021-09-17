#include "BlockDebris.h"
#include"TileMap.h"

MyImg*  BlockDebris::s_pImgBlockDebris = nullptr;

void BlockDebris::LoadRes(SDL_Renderer * pRenderer)
{
	s_pImgBlockDebris = new MyImg("res/images/BlockDebris0.bmp", pRenderer);
}

void BlockDebris::FreeRes()
{
	delete s_pImgBlockDebris;
}
void BlockDebris::Update(float dt)
{
	TL.x-= dt * (m_dx + 100.0f);
	TL.y+= dt * (m_dy - 800.0f);

	TR.x+= dt * (m_dx + 100.0f);
	TR.y+= dt * (m_dy - 800.0f);

	BL.x-= dt * m_dx;
	BL.y+= dt * (m_dy - 400.0f);

	BR.x+= dt * m_dx;
	BR.y+= dt * (m_dy - 400.0f);

	m_dx += dt * 100;
	m_dy += dt * 3000;

	if (TL.y > Config::H_SCREEN) {
		m_bDelete = true;
	}
}
void BlockDebris::Render(SDL_Renderer * pRenderer)
{
	s_pImgBlockDebris->Render(pRenderer, e_pTileMap->GetMapX() + (int)TL.x, e_pTileMap->GetMapY() + (int)TL.y);
	s_pImgBlockDebris->RenderHOR(pRenderer, e_pTileMap->GetMapX() + (int)TR.x, e_pTileMap->GetMapY() + (int)TR.y);
	s_pImgBlockDebris->Render(pRenderer, e_pTileMap->GetMapX() + (int)BL.x, e_pTileMap->GetMapY() + (int)BL.y);
	s_pImgBlockDebris->RenderHOR(pRenderer, e_pTileMap->GetMapX() + (int)BR.x, e_pTileMap->GetMapY() + (int)BR.y);
}
bool BlockDebris::bDelete()
{
	return m_bDelete;
}
BlockDebris::BlockDebris(TileMap * pTileMap, int x, int y)
{
	e_pTileMap = pTileMap;
	TL = { (float)x							,(float)y };
	TR = { (float)x + Config::TILE_SIZE / 2	,(float)y };
	BL = { (float)x							,(float)y + Config::TILE_SIZE / 2 };
	BR = { (float)x + Config::TILE_SIZE / 2	,(float)y + Config::TILE_SIZE / 2 };

	m_dx = 150.0f;
	m_dy = 100.0f;

	m_bDelete = false;
}
//////////////////////////////////////////////////////////////////////////////
BlockDebris::~BlockDebris()
{
}
