#include "Enemy.h"
#include"TileMap.h"

void Enemy::Render(SDL_Renderer * pRenderer)
{
	if (bOnScreen()) {
		if (m_bDead) {
			if (m_bFacingRight) {
				m_Animation.GetCurImage()->RenderHORVER(pRenderer, e_pTileMap->GetMapX() + (int)m_x, e_pTileMap->GetMapY() + (int)m_y);
			}
			else {
				m_Animation.GetCurImage()->RenderVER(pRenderer, e_pTileMap->GetMapX() + (int)m_x, e_pTileMap->GetMapY() + (int)m_y);
			}
		}
		else {
			if (m_bFacingRight) {
				m_Animation.GetCurImage()->RenderHOR(pRenderer, e_pTileMap->GetMapX() + (int)m_x, e_pTileMap->GetMapY() + (int)m_y);
			}
			else {
				m_Animation.GetCurImage()->Render(pRenderer, e_pTileMap->GetMapX() + (int)m_x, e_pTileMap->GetMapY() + (int)m_y);
			}
		}
	}
}

void Enemy::CollisionWithFireBall()
{
	for (size_t i = 0; i < e_pTileMap->m_FireBall.size(); i++)
	{
		if (m_bCollisionWithFireBall) {
			if (e_pTileMap->m_FireBall[i]->bIntersect(this)) {
				Kill();
				e_pTileMap->m_FireBall[i]->Remove();
				break;
			}
		}
	}
}

bool Enemy::bOnScreen()
{
	return
		(e_pTileMap->GetMapX() + (int)m_x + m_CX > -m_CWidth) &&
		(e_pTileMap->GetMapX() + (int)m_x + m_CX < Config::W_SCREEN) &&
		(e_pTileMap->GetMapY() + (int)m_y + m_CY > -m_CHeight) &&
		(e_pTileMap->GetMapY() + (int)m_y + m_CY < Config::H_SCREEN);
}
