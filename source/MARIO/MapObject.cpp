#include "MapObject.h"

#include"Animation.h"
#include"TileMap.h"


void MapObject::SetNumRange(int * pNum, int nMin, int nMax)
{
	if (*pNum < nMin)  *pNum = nMin;
	else if (*pNum > nMax)  *pNum = nMax;
}
void MapObject::Action()
{
	if (m_bLeft || m_bRight)
	{
		if (m_bLeft) {
			m_dx -= /*dt **/ m_MoveSpeed;
			if (m_dx < -m_MoveSpeedMax) {
				m_dx = -m_MoveSpeedMax;
			}
			if (m_dx < 0.0f)
				m_bFacingRight = false;
		}
		if (m_bRight)
		{
			m_dx += /*dt **/ m_MoveSpeed;
			if (m_dx > m_MoveSpeedMax) {
				m_dx = m_MoveSpeedMax;
			}
			if (m_dx > 0.0f)
				m_bFacingRight = true;
		}
	}
	else {
		if (m_dx > 0.0f) {
			m_dx -= /*dt **/ m_MoveStopSpeed;
			if (m_dx < 0.0f) {
				m_dx = 0.0f;
			}
		}
		else if (m_dx < 0.0f) {
			m_dx += /*dt * */m_MoveStopSpeed;
			if (m_dx > 0.0f) {
				m_dx = 0.0f;
			}
		}
	}


	if (m_bJump) {
		if (m_bTouch) {
			m_dy = m_JumpVelocityMax;
		}
	}
	else {
		if (m_dy < m_JumpVelocityMin) {
			m_dy = m_JumpVelocityMin;

		}
	}

}

void MapObject::AnimationAction()
{
	m_Animation.Update();
}

void MapObject::Render(SDL_Renderer * pRenderer)
{
	if (m_bFacingRight) {
		m_Animation.GetCurImage()->Render(pRenderer, e_pTileMap->GetMapX() + (int)m_x, e_pTileMap->GetMapY() + (int)m_y);
	}
	else {
		m_Animation.GetCurImage()->RenderHOR(pRenderer, e_pTileMap->GetMapX() + (int)m_x, e_pTileMap->GetMapY() + (int)m_y);
	}
}


void MapObject::CalcMapOffset()
{
	m_iColOffsetBeg = (((int)m_x + m_CX) / e_pTileMap->GetTileSize()) - 1;
	SetNumRange(&m_iColOffsetBeg, 0, e_pTileMap->GetColNum());
	m_iRowOffsetBeg = (((int)m_y + m_CY) / e_pTileMap->GetTileSize()) - 1;
	SetNumRange(&m_iRowOffsetBeg, 0, e_pTileMap->GetRowNum());

	m_iColOffsetEnd = ((((int)m_x + m_CX )+ (m_CWidth  - 1)) / e_pTileMap->GetTileSize()) + 2;//+1(因为右边多判断一个) +1(col < m_iColOffsetEnd)是< 不是<= 所以一共+2
	SetNumRange(&m_iColOffsetEnd, 0, e_pTileMap->GetColNum());
	m_iRowOffsetEnd = ((((int)m_y + m_CY )+ (m_CHeight - 1)) / e_pTileMap->GetTileSize()) + 2;
	SetNumRange(&m_iRowOffsetEnd, 0, e_pTileMap->GetRowNum());
}

void MapObject::HorCollisionWithMap()
{
	//地图边界
	if ((int)m_x + m_CX < 0) {
		m_x = -(float)m_CX;
		m_dx = 0.0f;
		SetTurn();
	}
	else if ((int)m_x + m_CX > (e_pTileMap->GetColNum()*e_pTileMap->GetTileSize()) - m_CWidth) {
		m_x = (float)((e_pTileMap->GetColNum()*e_pTileMap->GetTileSize()) - m_CWidth - m_CX);
		m_dx = 0.0f;
		SetTurn();
	}
	else
	{
		for (int row = m_iRowOffsetBeg; row < m_iRowOffsetEnd; row++) {
			for (int col = m_iColOffsetBeg; col < m_iColOffsetEnd; col++) {
				if (e_pTileMap->GetTile(row, col)->GetID() != Tile::TILES_NULL) {
					if (e_pTileMap->GetTile(row, col)->bVisible()) {
						if (e_pTileMap->GetTile(row, col)->bIntersect(this)) {
							if (m_dx > 0.0f) {
								e_pTileMap->GetTile(row, col)->SetOtherToSelfLeft(this);
							}
							else if (m_dx < 0.0f) {
								e_pTileMap->GetTile(row, col)->SetOtherToSelfRight(this);
							}
							m_dx = 0.0f;
							SetTurn();
						}
					}
				}
			}
		}
	}
}

void MapObject::VerCollisionWithMap()
{
	if ((int)m_y + m_CY >= Config::H_SCREEN) {
		m_bDelete = true;
	}
	for (int row = m_iRowOffsetBeg; row < m_iRowOffsetEnd; row++) {
		for (int col = m_iColOffsetBeg; col < m_iColOffsetEnd; col++) {
			if (e_pTileMap->GetTile(row, col)->GetID() != Tile::TILES_NULL) {
				if (e_pTileMap->GetTile(row, col)->bVisible()) {
					if (e_pTileMap->GetTile(row, col)->bIntersect(this)) {
						if (m_dy > 0.0f) {
							e_pTileMap->GetTile(row, col)->SetOtherToSelfUp(this);
						}
						else if (m_dy < 0.0f) {
							e_pTileMap->GetTile(row, col)->SetOtherToSelfDown(this);
						}
						m_dy = 0.0f;
					}
				}
			}
		}
	}
}

void MapObject::OntheGroundTest()
{
	int row = (((int)m_y + m_CY + 1) + (m_CHeight - 1)) / Config::TILE_SIZE;
	SetNumRange(&row, 0, e_pTileMap->GetRowNum() - 1);//只是确保安全
	for (int col = m_iColOffsetBeg; col < m_iColOffsetEnd; col++) {
		if (e_pTileMap->GetTile(row, col)->GetID() != Tile::TILES_NULL) {
			if (e_pTileMap->GetTile(row, col)->bVisible()) {
				if (e_pTileMap->GetTile(row, col)->bIntersect((int)m_x + m_CX, (int)m_y + m_CY + 1, m_CWidth, m_CHeight))
				{
					m_dy = 0.0f;
					m_bTouch= true;
					return;
				}
			}

		}
	}
	m_bTouch = false;
}

