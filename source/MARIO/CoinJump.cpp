#include "CoinJump.h"
#include"TileMap.h"

MyImg* CoinJump::s_pImgCoinJump[4] = { nullptr ,nullptr ,nullptr ,nullptr };

void CoinJump::LoadRes(SDL_Renderer * pRenderer)
{
	s_pImgCoinJump[0] = new MyImg("res/images/coin/coinjump0.bmp", pRenderer);
	s_pImgCoinJump[1] = new MyImg("res/images/coin/coinjump1.bmp", pRenderer);
	s_pImgCoinJump[2] = new MyImg("res/images/coin/coinjump2.bmp", pRenderer);
	s_pImgCoinJump[3] = new MyImg("res/images/coin/coinjump3.bmp", pRenderer);
}

void CoinJump::FreeRes()
{
	delete s_pImgCoinJump[0];
	delete s_pImgCoinJump[1];
	delete s_pImgCoinJump[2];
	delete s_pImgCoinJump[3];
}

void CoinJump::Update(float dt) {
	if (m_bJump) {
		if (m_bUp) {
			m_y -= dt * m_dy;
			if ((int)m_y < m_JumpStartY - Config::TILE_SIZE * 4) {
				m_y = float(m_JumpStartY - Config::TILE_SIZE * 4);
				m_bUp = false;
				m_bDown = true;
			}
		}
		else if (m_bDown) {
			m_y += dt * m_dy;
			if ((int)m_y > m_JumpStartY) {
				m_y = float(m_JumpStartY);
				m_bUp = true;
				m_bDown = false;

				m_bJump = false;
				m_bDelete = true;
			}
		}
	}
	m_Animation.Update();
}

void CoinJump::Render(SDL_Renderer * pRenderer)
{
	m_Animation.GetCurImage()->Render(pRenderer, e_pTileMap->GetMapX() + (int)m_x, e_pTileMap->GetMapY() + (int)m_y);
}

bool CoinJump::bDelete()
{
	return m_bDelete;
}

CoinJump::CoinJump(TileMap * pTileMap, int x, int y)
{
	this->e_pTileMap = pTileMap;
	m_JumpStartX = x;
	m_JumpStartY = y;
	m_bJump = true;
	m_bUp   = true;
	m_bDown = false;

	///////////////////////////////////
	m_x = (float)x;
	m_y = (float)y;
	m_dx = 0.0f;
	m_dy = 800.0f;
	m_bDelete = false;
	m_Animation.SetFrames(s_pImgCoinJump, 0, 4, 80);
}


CoinJump::~CoinJump()
{
}
