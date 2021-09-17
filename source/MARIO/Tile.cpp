#include "Tile.h"
#include"TileMap.h"

void Tile::SetStrike()
{
	m_bVisible = true;
	////test
	//if (m_IDInside == INSIDE_COIN && m_ID == TILES_BRICK) {
	//	e_pTileMap->CreateCoinJump((int)m_x, (int)m_y - Config::TILE_SIZE);
	//	//方块的跳跃
	//	m_bBounce = m_bBounceUp = true;
	//	return;
	//}
	//////////////////////////////////////
	if (m_IDInside == INSIDE_LVUP) {
		SetIDInside(Tile::INSIDE_NULL);
		SetID(Tile::TILES_BOXUSED);
		if (e_pTileMap->m_Player->GetLV() == 1) {
			e_pTileMap->CreateMush((int)m_x, (int)m_y);
		}
		else {
			e_pTileMap->CreateFlower((int)m_x, (int)m_y);
		}
		m_bBounce = m_bBounceUp= true;
	}
	else if (m_IDInside == INSIDE_COIN) {
		SetIDInside(Tile::INSIDE_NULL);
		SetID(Tile::TILES_BOXUSED);
		e_pTileMap->CreateCoinJump((int)m_x, (int)m_y - Config::TILE_SIZE);
		//方块的跳跃

		m_bBounce = m_bBounceUp = true;
	}
	else if (m_IDInside == INSIDE_STAR) {
		SetIDInside(Tile::INSIDE_NULL);
		SetID(Tile::TILES_BOXUSED);
		e_pTileMap->CreateStar((int)m_x, (int)m_y);
		//方块的跳跃

		m_bBounce = m_bBounceUp = true;
	}
	else if (m_IDInside == INSIDE_NULL && m_ID == TILES_BRICK) {
		if (e_pTileMap->m_Player->GetLV() == 1) {
			m_bBounce = m_bBounceUp = true;
		}
		else
		{
			SetID(Tile::TILES_NULL);
			e_pTileMap->CreateBlockDebris((int)m_x, (int)m_y - Config::TILE_SIZE);
		}
		
	}
}

void Tile::Update(float dt)
{
	if (m_bBounce) {
		if (m_bBounceUp) {
			m_y -= dt * BOUNCE_SPEED;
			if ((int)m_y < m_BounceStartY  - BOUNCE_HEIGHT) {
				m_y = float(m_BounceStartY - BOUNCE_HEIGHT);
				m_bBounceUp = false;
				m_bBounceDown = true;
			}
		}
		else if (m_bBounceDown) {
			m_y += dt * BOUNCE_SPEED;
			if ((int)m_y > m_BounceStartY) {
				m_y = float(m_BounceStartY);
				m_bBounceUp = false;
				m_bBounceDown = false;

				m_bBounce = false;
			}
		}
	}
}

Tile::Tile(TileMap* pTileMap,int x, int y, int ID)
{
	m_x = (float)x;
	m_y = (float)y;
	m_CX = 0;
	m_CY = 0;
	m_CWidth = Config::TILE_SIZE;
	m_CHeight = Config::TILE_SIZE;
	this->e_pTileMap = pTileMap;
	///////////////////////////////////
	m_ID = ID;
	m_IDInside = INSIDE_NULL;
	m_BounceStartX = x;
	m_BounceStartY = y;
	m_bBounce      = false;
	m_bBounceUp    = false;
	m_bBounceDown  = false;
	m_bVisible		= true;
}

Tile::~Tile()
{
	
}
