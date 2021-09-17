#include "Player.h"
#include "TileMap.h"
#include "MyImg.h"

MyImg** Player::s_pSpiritsLV1[4] = { nullptr,nullptr ,nullptr ,nullptr };
MyImg** Player::s_pSpiritsLV1Star[4] = { nullptr,nullptr ,nullptr ,nullptr };
MyImg** Player::s_pSpiritsLV2[5] = { nullptr,nullptr ,nullptr ,nullptr,nullptr };
MyImg** Player::s_pSpiritsLV2Star[5] = { nullptr,nullptr ,nullptr ,nullptr,nullptr };
MyImg** Player::s_pSpiritsLV3[6] = { nullptr,nullptr ,nullptr ,nullptr,nullptr,nullptr };
MyImg** Player::s_pSpiritsLV3Star[6] = { nullptr,nullptr ,nullptr ,nullptr,nullptr,nullptr };
MyImg** Player::s_pSpiritsPowerUp1[1] = { nullptr };
MyImg** Player::s_pSpiritsPowerUp2[7] = { nullptr, nullptr,nullptr ,nullptr ,nullptr,nullptr,nullptr };

void Player::HorCollisionWithMap() {
	//地图边界
	if ((int)m_x + m_CX < 0) {
		m_x = -(float)m_CX;
		m_dx = 0.0f;

	}
	else if ((int)m_x + m_CX > (e_pTileMap->GetColNum()*e_pTileMap->GetTileSize()) - m_CWidth) {
		m_x = (float)((e_pTileMap->GetColNum()*e_pTileMap->GetTileSize()) - m_CWidth - m_CX);
		m_dx = 0.0f;
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
						}
					}
				}
			}
		}
	}
}

void Player::VerCollisionWithMap()
{
	for (int row = m_iRowOffsetBeg; row < m_iRowOffsetEnd; row++) {
		for (int col = m_iColOffsetBeg; col < m_iColOffsetEnd; col++) {
			if (e_pTileMap->GetTile(row, col)->GetID() != Tile::TILES_NULL) {
				if (e_pTileMap->GetTile(row, col)->bIntersect(this)) {
					{
						if (e_pTileMap->GetTile(row, col)->bVisible()) {
							if (m_dy > 0.0f) {
								e_pTileMap->GetTile(row, col)->SetOtherToSelfUp(this);
							}
							else if (m_dy < 0.0f) {
								e_pTileMap->GetTile(row, col)->SetOtherToSelfDown(this);
								e_pTileMap->GetTile(row, col)->SetStrike();
							}
							m_dy = 0.0f;
						}
						else {
							if (m_dy < 0.0f) {
								e_pTileMap->GetTile(row, col)->SetOtherToSelfDown(this);
								e_pTileMap->GetTile(row, col)->SetStrike();
								m_dy = 0.0f;
							}
						}

					}
				}
			}
		}
	}
}

void Player::LoadRes(SDL_Renderer * pRender)
{
	////////////////////////////////////////////////////
	s_pSpiritsLV1[IDLE] = new MyImg*[FRAMENUM_IDLE];
	s_pSpiritsLV1[IDLE][0] = new MyImg("res/images/mario/small/idle0.bmp", pRender);
	s_pSpiritsLV1[JUMP] = new MyImg*[FRAMENUM_JUMP];
	s_pSpiritsLV1[JUMP][0] = new MyImg("res/images/mario/small/jump0.bmp", pRender);
	s_pSpiritsLV1[WALK] = new MyImg*[FRAMENUM_WALK];
	s_pSpiritsLV1[WALK][0] = new MyImg("res/images/mario/small/walk0.bmp", pRender);
	s_pSpiritsLV1[WALK][1] = new MyImg("res/images/mario/small/walk1.bmp", pRender);
	s_pSpiritsLV1[WALK][2] = new MyImg("res/images/mario/small/walk2.bmp", pRender);
	s_pSpiritsLV1[STOP] = new MyImg*[FRAMENUM_STOP];
	s_pSpiritsLV1[STOP][0] = new MyImg("res/images/mario/small/stop0.bmp", pRender);
	////////////////////////////////////////////////////
	s_pSpiritsLV1Star[IDLE] = new MyImg*[FRAMENUM_IDLE_STAR];
	s_pSpiritsLV1Star[IDLE][0] = new MyImg("res/images/mario/eatstar/small/idle0_0.bmp", pRender);
	s_pSpiritsLV1Star[IDLE][1] = new MyImg("res/images/mario/eatstar/small/idle0_1.bmp", pRender);
	s_pSpiritsLV1Star[IDLE][2] = new MyImg("res/images/mario/eatstar/small/idle0_2.bmp", pRender);
	s_pSpiritsLV1Star[JUMP] = new MyImg*[FRAMENUM_JUMP_STAR];
	s_pSpiritsLV1Star[JUMP][0] = new MyImg("res/images/mario/eatstar/small/jump0_0.bmp", pRender);
	s_pSpiritsLV1Star[JUMP][1] = new MyImg("res/images/mario/eatstar/small/jump0_1.bmp", pRender);
	s_pSpiritsLV1Star[JUMP][2] = new MyImg("res/images/mario/eatstar/small/jump0_2.bmp", pRender);
	s_pSpiritsLV1Star[WALK] = new MyImg*[FRAMENUM_WALK_STAR];
	s_pSpiritsLV1Star[WALK][0] = new MyImg("res/images/mario/eatstar/small/walk0_0.bmp", pRender);
	s_pSpiritsLV1Star[WALK][1] = new MyImg("res/images/mario/eatstar/small/walk0_1.bmp", pRender);
	s_pSpiritsLV1Star[WALK][2] = new MyImg("res/images/mario/eatstar/small/walk0_2.bmp", pRender);
	s_pSpiritsLV1Star[STOP] = new MyImg*[FRAMENUM_STOP_STAR];
	s_pSpiritsLV1Star[STOP][0] = new MyImg("res/images/mario/eatstar/small/stop0_0.bmp", pRender);
	s_pSpiritsLV1Star[STOP][1] = new MyImg("res/images/mario/eatstar/small/stop0_1.bmp", pRender);
	s_pSpiritsLV1Star[STOP][2] = new MyImg("res/images/mario/eatstar/small/stop0_2.bmp", pRender);
	////////////////////////////////////////////////////
	s_pSpiritsLV2[IDLE] = new MyImg*[FRAMENUM_IDLE];
	s_pSpiritsLV2[IDLE][0] = new MyImg("res/images/mario/big/idle0.bmp", pRender);
	s_pSpiritsLV2[JUMP] = new MyImg*[FRAMENUM_JUMP];
	s_pSpiritsLV2[JUMP][0] = new MyImg("res/images/mario/big/jump0.bmp", pRender);
	s_pSpiritsLV2[WALK] = new MyImg*[FRAMENUM_WALK];
	s_pSpiritsLV2[WALK][0] = new MyImg("res/images/mario/big/walk0.bmp", pRender);
	s_pSpiritsLV2[WALK][1] = new MyImg("res/images/mario/big/walk1.bmp", pRender);
	s_pSpiritsLV2[WALK][2] = new MyImg("res/images/mario/big/walk2.bmp", pRender);
	s_pSpiritsLV2[STOP] = new MyImg*[FRAMENUM_STOP];
	s_pSpiritsLV2[STOP][0] = new MyImg("res/images/mario/big/stop0.bmp", pRender);
	s_pSpiritsLV2[SQUAT] = new MyImg*[FRAMENUM_SQUAT];
	s_pSpiritsLV2[SQUAT][0] = new MyImg("res/images/mario/big/squat0.bmp", pRender);
	////////////////////////////////////////////////////
	s_pSpiritsLV2Star[IDLE] = new MyImg*[FRAMENUM_IDLE_STAR];
	s_pSpiritsLV2Star[IDLE][0] = new MyImg("res/images/mario/eatstar/big/idle0_0.bmp", pRender);
	s_pSpiritsLV2Star[IDLE][1] = new MyImg("res/images/mario/eatstar/big/idle0_1.bmp", pRender);
	s_pSpiritsLV2Star[IDLE][2] = new MyImg("res/images/mario/eatstar/big/idle0_2.bmp", pRender);
	s_pSpiritsLV2Star[JUMP] = new MyImg*[FRAMENUM_JUMP_STAR];
	s_pSpiritsLV2Star[JUMP][0] = new MyImg("res/images/mario/eatstar/big/jump0_0.bmp", pRender);
	s_pSpiritsLV2Star[JUMP][1] = new MyImg("res/images/mario/eatstar/big/jump0_1.bmp", pRender);
	s_pSpiritsLV2Star[JUMP][2] = new MyImg("res/images/mario/eatstar/big/jump0_2.bmp", pRender);
	s_pSpiritsLV2Star[WALK] = new MyImg*[FRAMENUM_WALK_STAR];
	s_pSpiritsLV2Star[WALK][0] = new MyImg("res/images/mario/eatstar/big/walk0_0.bmp", pRender);
	s_pSpiritsLV2Star[WALK][1] = new MyImg("res/images/mario/eatstar/big/walk0_1.bmp", pRender);
	s_pSpiritsLV2Star[WALK][2] = new MyImg("res/images/mario/eatstar/big/walk0_2.bmp", pRender);
	s_pSpiritsLV2Star[STOP] = new MyImg*[FRAMENUM_STOP_STAR];
	s_pSpiritsLV2Star[STOP][0] = new MyImg("res/images/mario/eatstar/big/stop0_0.bmp", pRender);
	s_pSpiritsLV2Star[STOP][1] = new MyImg("res/images/mario/eatstar/big/stop0_1.bmp", pRender);
	s_pSpiritsLV2Star[STOP][2] = new MyImg("res/images/mario/eatstar/big/stop0_2.bmp", pRender);
	s_pSpiritsLV2Star[SQUAT] = new MyImg*[FRAMENUM_SQUAT_STAR];
	s_pSpiritsLV2Star[SQUAT][0] = new MyImg("res/images/mario/eatstar/big/squat0_0.bmp", pRender);
	s_pSpiritsLV2Star[SQUAT][1] = new MyImg("res/images/mario/eatstar/big/squat0_1.bmp", pRender);
	s_pSpiritsLV2Star[SQUAT][2] = new MyImg("res/images/mario/eatstar/big/squat0_2.bmp", pRender);
	//////////////////////////////////////////////////
	s_pSpiritsLV3[IDLE] = new MyImg*[FRAMENUM_IDLE];
	s_pSpiritsLV3[IDLE][0] = new MyImg("res/images/mario/fire/idle0.bmp", pRender);
	s_pSpiritsLV3[JUMP] = new MyImg*[FRAMENUM_JUMP];
	s_pSpiritsLV3[JUMP][0] = new MyImg("res/images/mario/fire/jump0.bmp", pRender);
	s_pSpiritsLV3[WALK] = new MyImg*[FRAMENUM_WALK];
	s_pSpiritsLV3[WALK][0] = new MyImg("res/images/mario/fire/walk0.bmp", pRender);
	s_pSpiritsLV3[WALK][1] = new MyImg("res/images/mario/fire/walk1.bmp", pRender);
	s_pSpiritsLV3[WALK][2] = new MyImg("res/images/mario/fire/walk2.bmp", pRender);
	s_pSpiritsLV3[STOP] = new MyImg*[FRAMENUM_STOP];
	s_pSpiritsLV3[STOP][0] = new MyImg("res/images/mario/fire/stop0.bmp", pRender);
	s_pSpiritsLV3[SQUAT] = new MyImg*[FRAMENUM_SQUAT];
	s_pSpiritsLV3[SQUAT][0] = new MyImg("res/images/mario/fire/squat0.bmp", pRender);
	s_pSpiritsLV3[FIRE] = new MyImg*[FRAMENUM_FIRE];
	s_pSpiritsLV3[FIRE][0] = new MyImg("res/images/mario/fire/fire0.bmp", pRender);
	//////////////////////////////////////////////////////////////////////
	s_pSpiritsLV3Star[IDLE] = new MyImg*[FRAMENUM_IDLE_STAR];
	s_pSpiritsLV3Star[IDLE][0] = new MyImg("res/images/mario/eatstar/fire/idle0_0.bmp", pRender);
	s_pSpiritsLV3Star[IDLE][1] = new MyImg("res/images/mario/eatstar/fire/idle0_1.bmp", pRender);
	s_pSpiritsLV3Star[IDLE][2] = new MyImg("res/images/mario/eatstar/fire/idle0_2.bmp", pRender);
	s_pSpiritsLV3Star[JUMP] = new MyImg*[FRAMENUM_JUMP_STAR];
	s_pSpiritsLV3Star[JUMP][0] = new MyImg("res/images/mario/eatstar/fire/jump0_0.bmp", pRender);
	s_pSpiritsLV3Star[JUMP][1] = new MyImg("res/images/mario/eatstar/fire/jump0_1.bmp", pRender);
	s_pSpiritsLV3Star[JUMP][2] = new MyImg("res/images/mario/eatstar/fire/jump0_2.bmp", pRender);
	s_pSpiritsLV3Star[WALK] = new MyImg*[FRAMENUM_WALK_STAR];
	s_pSpiritsLV3Star[WALK][0] = new MyImg("res/images/mario/eatstar/fire/walk0_0.bmp", pRender);
	s_pSpiritsLV3Star[WALK][1] = new MyImg("res/images/mario/eatstar/fire/walk0_1.bmp", pRender);
	s_pSpiritsLV3Star[WALK][2] = new MyImg("res/images/mario/eatstar/fire/walk0_2.bmp", pRender);
	s_pSpiritsLV3Star[STOP] = new MyImg*[FRAMENUM_STOP_STAR];
	s_pSpiritsLV3Star[STOP][0] = new MyImg("res/images/mario/eatstar/fire/stop0_0.bmp", pRender);
	s_pSpiritsLV3Star[STOP][1] = new MyImg("res/images/mario/eatstar/fire/stop0_1.bmp", pRender);
	s_pSpiritsLV3Star[STOP][2] = new MyImg("res/images/mario/eatstar/fire/stop0_2.bmp", pRender);
	s_pSpiritsLV3Star[SQUAT] = new MyImg*[FRAMENUM_SQUAT_STAR];
	s_pSpiritsLV3Star[SQUAT][0] = new MyImg("res/images/mario/eatstar/fire/squat0_0.bmp", pRender);
	s_pSpiritsLV3Star[SQUAT][1] = new MyImg("res/images/mario/eatstar/fire/squat0_1.bmp", pRender);
	s_pSpiritsLV3Star[SQUAT][2] = new MyImg("res/images/mario/eatstar/fire/squat0_2.bmp", pRender);
	s_pSpiritsLV3Star[FIRE] = new MyImg*[FRAMENUM_FIRE_STAR];
	s_pSpiritsLV3Star[FIRE][0] = new MyImg("res/images/mario/eatstar/fire/fire0_0.bmp", pRender);
	s_pSpiritsLV3Star[FIRE][1] = new MyImg("res/images/mario/eatstar/fire/fire0_1.bmp", pRender);
	s_pSpiritsLV3Star[FIRE][2] = new MyImg("res/images/mario/eatstar/fire/fire0_2.bmp", pRender);
	/////////////////////////////////////////////////////////////
	s_pSpiritsPowerUp1[POWERUP_1] = new MyImg*[FRAMENUM_POWERUP];
	s_pSpiritsPowerUp1[POWERUP_1][0] = new MyImg("res/images/mario/eatmush/eatmush0.bmp", pRender);
	s_pSpiritsPowerUp1[POWERUP_1][1] = new MyImg("res/images/mario/eatmush/eatmush1.bmp", pRender);
	s_pSpiritsPowerUp1[POWERUP_1][2] = new MyImg("res/images/mario/eatmush/eatmush2.bmp", pRender);
	////////////////////////////////////
	s_pSpiritsPowerUp2[POWERUP_2_IDLE] = new MyImg*[FRAMENUM_POWERUP];
	s_pSpiritsPowerUp2[POWERUP_2_IDLE][0] = new MyImg("res/images/mario/eatflower/idle0_0.bmp", pRender);
	s_pSpiritsPowerUp2[POWERUP_2_IDLE][1] = new MyImg("res/images/mario/eatflower/idle0_1.bmp", pRender);
	s_pSpiritsPowerUp2[POWERUP_2_IDLE][2] = new MyImg("res/images/mario/eatflower/idle0_2.bmp", pRender);

	s_pSpiritsPowerUp2[POWERUP_2_JUMP] = new MyImg*[FRAMENUM_POWERUP];
	s_pSpiritsPowerUp2[POWERUP_2_JUMP][0] = new MyImg("res/images/mario/eatflower/jump0_0.bmp", pRender);
	s_pSpiritsPowerUp2[POWERUP_2_JUMP][1] = new MyImg("res/images/mario/eatflower/jump0_1.bmp", pRender);
	s_pSpiritsPowerUp2[POWERUP_2_JUMP][2] = new MyImg("res/images/mario/eatflower/jump0_2.bmp", pRender);

	s_pSpiritsPowerUp2[POWERUP_2_WALK_0] = new MyImg*[FRAMENUM_POWERUP];
	s_pSpiritsPowerUp2[POWERUP_2_WALK_0][0] = new MyImg("res/images/mario/eatflower/walk0_0.bmp", pRender);
	s_pSpiritsPowerUp2[POWERUP_2_WALK_0][1] = new MyImg("res/images/mario/eatflower/walk0_1.bmp", pRender);
	s_pSpiritsPowerUp2[POWERUP_2_WALK_0][2] = new MyImg("res/images/mario/eatflower/walk0_2.bmp", pRender);

	s_pSpiritsPowerUp2[POWERUP_2_WALK_1] = new MyImg*[FRAMENUM_POWERUP];
	s_pSpiritsPowerUp2[POWERUP_2_WALK_1][0] = new MyImg("res/images/mario/eatflower/walk1_0.bmp", pRender);
	s_pSpiritsPowerUp2[POWERUP_2_WALK_1][1] = new MyImg("res/images/mario/eatflower/walk1_1.bmp", pRender);
	s_pSpiritsPowerUp2[POWERUP_2_WALK_1][2] = new MyImg("res/images/mario/eatflower/walk1_2.bmp", pRender);

	s_pSpiritsPowerUp2[POWERUP_2_WALK_2] = new MyImg*[FRAMENUM_POWERUP];
	s_pSpiritsPowerUp2[POWERUP_2_WALK_2][0] = new MyImg("res/images/mario/eatflower/walk2_0.bmp", pRender);
	s_pSpiritsPowerUp2[POWERUP_2_WALK_2][1] = new MyImg("res/images/mario/eatflower/walk2_1.bmp", pRender);
	s_pSpiritsPowerUp2[POWERUP_2_WALK_2][2] = new MyImg("res/images/mario/eatflower/walk2_2.bmp", pRender);

	s_pSpiritsPowerUp2[POWERUP_2_STOP] = new MyImg*[FRAMENUM_POWERUP];
	s_pSpiritsPowerUp2[POWERUP_2_STOP][0] = new MyImg("res/images/mario/eatflower/stop0_0.bmp", pRender);
	s_pSpiritsPowerUp2[POWERUP_2_STOP][1] = new MyImg("res/images/mario/eatflower/stop0_1.bmp", pRender);
	s_pSpiritsPowerUp2[POWERUP_2_STOP][2] = new MyImg("res/images/mario/eatflower/stop0_2.bmp", pRender);

	s_pSpiritsPowerUp2[POWERUP_2_SQUAT] = new MyImg*[FRAMENUM_POWERUP];
	s_pSpiritsPowerUp2[POWERUP_2_SQUAT][0] = new MyImg("res/images/mario/eatflower/squat0_0.bmp", pRender);
	s_pSpiritsPowerUp2[POWERUP_2_SQUAT][1] = new MyImg("res/images/mario/eatflower/squat0_1.bmp", pRender);
	s_pSpiritsPowerUp2[POWERUP_2_SQUAT][2] = new MyImg("res/images/mario/eatflower/squat0_2.bmp", pRender);

}

void Player::FreeRes()
{
	for (int i = 0; i < FRAMENUM_IDLE; i++) delete s_pSpiritsLV1[IDLE][i]; delete[] s_pSpiritsLV1[IDLE];
	for (int i = 0; i < FRAMENUM_JUMP; i++) delete s_pSpiritsLV1[JUMP][i]; delete[] s_pSpiritsLV1[JUMP];
	for (int i = 0; i < FRAMENUM_WALK; i++) delete s_pSpiritsLV1[WALK][i]; delete[] s_pSpiritsLV1[WALK];
	for (int i = 0; i < FRAMENUM_STOP; i++) delete s_pSpiritsLV1[STOP][i]; delete[] s_pSpiritsLV1[STOP];
	//////////////
	for (int i = 0; i < FRAMENUM_IDLE_STAR; i++) delete s_pSpiritsLV1Star[IDLE][i]; delete[] s_pSpiritsLV1Star[IDLE];
	for (int i = 0; i < FRAMENUM_JUMP_STAR; i++) delete s_pSpiritsLV1Star[JUMP][i]; delete[] s_pSpiritsLV1Star[JUMP];
	for (int i = 0; i < FRAMENUM_WALK_STAR; i++) delete s_pSpiritsLV1Star[WALK][i]; delete[] s_pSpiritsLV1Star[WALK];
	for (int i = 0; i < FRAMENUM_STOP_STAR; i++) delete s_pSpiritsLV1Star[STOP][i]; delete[] s_pSpiritsLV1Star[STOP];
	//////////////
	for (int i = 0; i < FRAMENUM_IDLE; i++) delete s_pSpiritsLV2[IDLE][i]; delete[] s_pSpiritsLV2[IDLE];
	for (int i = 0; i < FRAMENUM_JUMP; i++) delete s_pSpiritsLV2[JUMP][i]; delete[] s_pSpiritsLV2[JUMP];
	for (int i = 0; i < FRAMENUM_WALK; i++) delete s_pSpiritsLV2[WALK][i]; delete[] s_pSpiritsLV2[WALK];
	for (int i = 0; i < FRAMENUM_STOP; i++) delete s_pSpiritsLV2[STOP][i]; delete[] s_pSpiritsLV2[STOP];
	for (int i = 0; i < FRAMENUM_SQUAT; i++) delete s_pSpiritsLV2[SQUAT][i]; delete[] s_pSpiritsLV2[SQUAT];
	//////////////
	for (int i = 0; i < FRAMENUM_IDLE_STAR; i++) delete s_pSpiritsLV2Star[IDLE][i]; delete[] s_pSpiritsLV2Star[IDLE];
	for (int i = 0; i < FRAMENUM_JUMP_STAR; i++) delete s_pSpiritsLV2Star[JUMP][i]; delete[] s_pSpiritsLV2Star[JUMP];
	for (int i = 0; i < FRAMENUM_WALK_STAR; i++) delete s_pSpiritsLV2Star[WALK][i]; delete[] s_pSpiritsLV2Star[WALK];
	for (int i = 0; i < FRAMENUM_STOP_STAR; i++) delete s_pSpiritsLV2Star[STOP][i]; delete[] s_pSpiritsLV2Star[STOP];
	for (int i = 0; i < FRAMENUM_SQUAT_STAR; i++) delete s_pSpiritsLV2Star[SQUAT][i]; delete[] s_pSpiritsLV2Star[SQUAT];
	//////////////
	for (int i = 0; i < FRAMENUM_IDLE; i++) delete s_pSpiritsLV3[IDLE][i]; delete[] s_pSpiritsLV3[IDLE];
	for (int i = 0; i < FRAMENUM_JUMP; i++) delete s_pSpiritsLV3[JUMP][i]; delete[] s_pSpiritsLV3[JUMP];
	for (int i = 0; i < FRAMENUM_WALK; i++) delete s_pSpiritsLV3[WALK][i]; delete[] s_pSpiritsLV3[WALK];
	for (int i = 0; i < FRAMENUM_STOP; i++) delete s_pSpiritsLV3[STOP][i]; delete[] s_pSpiritsLV3[STOP];
	for (int i = 0; i < FRAMENUM_SQUAT; i++) delete s_pSpiritsLV3[SQUAT][i]; delete[] s_pSpiritsLV3[SQUAT];
	for (int i = 0; i < FRAMENUM_FIRE; i++) delete s_pSpiritsLV3[FIRE][i]; delete[] s_pSpiritsLV3[FIRE];
	//////////////
	for (int i = 0; i < FRAMENUM_IDLE_STAR; i++) delete s_pSpiritsLV3Star[IDLE][i]; delete[] s_pSpiritsLV3Star[IDLE];
	for (int i = 0; i < FRAMENUM_JUMP_STAR; i++) delete s_pSpiritsLV3Star[JUMP][i]; delete[] s_pSpiritsLV3Star[JUMP];
	for (int i = 0; i < FRAMENUM_WALK_STAR; i++) delete s_pSpiritsLV3Star[WALK][i]; delete[] s_pSpiritsLV3Star[WALK];
	for (int i = 0; i < FRAMENUM_STOP_STAR; i++) delete s_pSpiritsLV3Star[STOP][i]; delete[] s_pSpiritsLV3Star[STOP];
	for (int i = 0; i < FRAMENUM_SQUAT_STAR; i++) delete s_pSpiritsLV3Star[SQUAT][i]; delete[] s_pSpiritsLV3Star[SQUAT];
	for (int i = 0; i < FRAMENUM_FIRE_STAR; i++) delete s_pSpiritsLV3Star[FIRE][i]; delete[] s_pSpiritsLV3Star[FIRE];
	////////////////////////
	for (int i = 0; i < FRAMENUM_POWERUP; i++) delete s_pSpiritsPowerUp1[POWERUP_1][i]; delete[] s_pSpiritsPowerUp1[POWERUP_1];
	///////////////////////////
	for (int i = 0; i < FRAMENUM_POWERUP; i++) delete s_pSpiritsPowerUp2[POWERUP_2_IDLE][i]; delete[] s_pSpiritsPowerUp2[POWERUP_2_IDLE];
	for (int i = 0; i < FRAMENUM_POWERUP; i++) delete s_pSpiritsPowerUp2[POWERUP_2_JUMP][i]; delete[] s_pSpiritsPowerUp2[POWERUP_2_JUMP];
	for (int i = 0; i < FRAMENUM_POWERUP; i++) delete s_pSpiritsPowerUp2[POWERUP_2_WALK_0][i]; delete[] s_pSpiritsPowerUp2[POWERUP_2_WALK_0];
	for (int i = 0; i < FRAMENUM_POWERUP; i++) delete s_pSpiritsPowerUp2[POWERUP_2_WALK_1][i]; delete[] s_pSpiritsPowerUp2[POWERUP_2_WALK_1];
	for (int i = 0; i < FRAMENUM_POWERUP; i++) delete s_pSpiritsPowerUp2[POWERUP_2_WALK_2][i]; delete[] s_pSpiritsPowerUp2[POWERUP_2_WALK_2];
	for (int i = 0; i < FRAMENUM_POWERUP; i++) delete s_pSpiritsPowerUp2[POWERUP_2_STOP][i]; delete[] s_pSpiritsPowerUp2[POWERUP_2_STOP];
	for (int i = 0; i < FRAMENUM_POWERUP; i++) delete s_pSpiritsPowerUp2[POWERUP_2_SQUAT][i]; delete[] s_pSpiritsPowerUp2[POWERUP_2_SQUAT];

}

void Player::Update(float dt)
{
	Action();
	AnimationAction();
	/////////////////////////////
	CalcMapOffset();
	m_x += dt * m_dx;
	HorCollisionWithMap();
	m_dy += dt * m_Gravity;
	m_y += dt * m_dy;
	VerCollisionWithMap();
	OntheGroundTest();
	/////////////////////
	e_pTileMap->SetMapX(Config::W_SCREEN / 2 - ((int)m_x + m_CWidth / 2));
	e_pTileMap->SetMapY(Config::H_SCREEN / 2 - ((int)m_y + m_CHeight / 2));

}


void Player::Action()
{
	MapObject::Action();
	///////////////////////////////////////
	m_bCanFire = m_tCanFire.Update();
	if (m_bFire) {
		if (m_bCanFire && m_LV == 3) {
			m_tCanFire.Init(300);
			e_pTileMap->CreateFireBall((int)m_x + m_CX + (m_bFacingRight ? 64 : -32), (int)m_y + 32, m_bFacingRight);
			/////////////////////////
			m_bFireing = true;
			m_tFireing.Init(150);
		}
	}
}

void Player::AnimationAction()
{
	///////////////////////////////////////
	m_bStaring = !m_tStaring.Update();
	m_bPowerUping = !m_tPowerUping.Update();
	m_bFireing = !m_tFireing.Update();
	///////////////////////////////////////

	PreState = CurState;
	if (m_bTouch == false) {
		if (m_dy < 0.0f || (m_dy > 0.0f && PreState == JUMP)) {
			CurState = JUMP;
		}
		else if (m_dy > 0.0f) {
			//挖个坟
			//CurState = IDLE;
			CurState = JUMP;
		}
	}
	else {
		if (m_dx != 0.0f) {
			if ((m_bLeft&& m_dx > 0.0f) || (m_bRight&&m_dx < 0.0f)) {
				CurState = STOP;
			}
			else {
				CurState = WALK;
			}
		}
		else if (m_bDown) {
			CurState = SQUAT;
		}
		else {
			CurState = IDLE;
		}
	}

	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	if (m_bPowerUping) {
		if (m_bPowerUpAni) {
			m_bPowerUpAni = false;
			if (m_LV == 2) {
				m_Animation.SetFrames(s_pSpiritsPowerUp1[POWERUP_1], 0, FRAMENUM_POWERUP, 100);
			}
			else if (m_LV == 3) {
				if (CurState == JUMP) {
					m_Animation.SetFrames(s_pSpiritsPowerUp2[POWERUP_2_JUMP], 0, FRAMENUM_POWERUP, 100);
				}
				else if (CurState == STOP) {
					m_Animation.SetFrames(s_pSpiritsPowerUp2[POWERUP_2_STOP], 0, FRAMENUM_POWERUP, 100);
				}
				else if (CurState == WALK) {
					if (m_Animation.GetCurFrame() == 0) {
						m_Animation.SetFrames(s_pSpiritsPowerUp2[POWERUP_2_WALK_0], 0, FRAMENUM_POWERUP, 100);
					}
					else if (m_Animation.GetCurFrame() == 1) {
						m_Animation.SetFrames(s_pSpiritsPowerUp2[POWERUP_2_WALK_1], 0, FRAMENUM_POWERUP, 100);
					}
					else if (m_Animation.GetCurFrame() == 2) {
						m_Animation.SetFrames(s_pSpiritsPowerUp2[POWERUP_2_WALK_2], 0, FRAMENUM_POWERUP, 100);
					}
				}
				else if (CurState == SQUAT) {
					m_Animation.SetFrames(s_pSpiritsPowerUp2[POWERUP_2_SQUAT], 0, FRAMENUM_POWERUP, 100);
				}
				else if (CurState == IDLE) {
					m_Animation.SetFrames(s_pSpiritsPowerUp2[POWERUP_2_IDLE], 0, FRAMENUM_POWERUP, 100);
				}
			}
		}

	}
	else {
		if (m_bFireing) {
			m_Animation.SetFrames(s_pSpiritsLV3[FIRE], 0, FRAMENUM_FIRE, 100);
		}
		else {
			if (CurState == JUMP) {
				if (m_LV == 1) {
					if (m_bStaring) {
						m_Animation.SetFrames(s_pSpiritsLV1Star[JUMP], 0, FRAMENUM_JUMP_STAR, 100);
					}
					else {
						m_Animation.SetFrames(s_pSpiritsLV1[JUMP], 0, FRAMENUM_JUMP, 100);
					}
				}
				else if (m_LV == 2) {
					if (m_bStaring) {
						m_Animation.SetFrames(s_pSpiritsLV2Star[JUMP], 0, FRAMENUM_JUMP_STAR, 100);
					}
					else {
						m_Animation.SetFrames(s_pSpiritsLV2[JUMP], 0, FRAMENUM_JUMP, 100);
					}
				}
				else if (m_LV == 3) {
					if (m_bStaring) {
						m_Animation.SetFrames(s_pSpiritsLV3Star[JUMP], 0, FRAMENUM_JUMP_STAR, 100);
					}
					else {
						m_Animation.SetFrames(s_pSpiritsLV3[JUMP], 0, FRAMENUM_JUMP, 100);
					}
				}
			}
			else if (CurState == STOP) {
				if (m_LV == 1) {
					if (m_bStaring) {
						m_Animation.SetFrames(s_pSpiritsLV1Star[STOP], 0, FRAMENUM_STOP_STAR, 100);
					}
					else {
						m_Animation.SetFrames(s_pSpiritsLV1[STOP], 0, FRAMENUM_STOP, 100);
					}
				}
				else if (m_LV == 2) {
					if (m_bStaring) {
						m_Animation.SetFrames(s_pSpiritsLV2Star[JUMP], 0, FRAMENUM_JUMP_STAR, 100);
					}
					else {
						m_Animation.SetFrames(s_pSpiritsLV2[JUMP], 0, FRAMENUM_JUMP, 100);
					}
				}
				else if (m_LV == 3) {
					if (m_bStaring) {
						m_Animation.SetFrames(s_pSpiritsLV3Star[JUMP], 0, FRAMENUM_JUMP_STAR, 100);
					}
					else {
						m_Animation.SetFrames(s_pSpiritsLV3[JUMP], 0, FRAMENUM_JUMP, 100);
					}
				}



			}
			else if (CurState == WALK) {

				if (m_LV == 1) {
					if (m_bStaring) {
						m_Animation.SetFrames(s_pSpiritsLV1Star[WALK], 0, FRAMENUM_WALK_STAR, 100);
					}
					else {
						m_Animation.SetFrames(s_pSpiritsLV1[WALK], 0, FRAMENUM_WALK, 100);
					}
				}
				else if (m_LV == 2) {
					if (m_bStaring) {
						m_Animation.SetFrames(s_pSpiritsLV2Star[WALK], 0, FRAMENUM_WALK_STAR, 100);
					}
					else {
						m_Animation.SetFrames(s_pSpiritsLV2[WALK], 0, FRAMENUM_WALK, 100);

					}
				}
				else if (m_LV == 3) {
					if (m_bStaring) {
						m_Animation.SetFrames(s_pSpiritsLV3Star[WALK], 0, FRAMENUM_WALK_STAR, 100);
					}
					else {
						m_Animation.SetFrames(s_pSpiritsLV3[WALK], 0, FRAMENUM_WALK, 100);

					}
				}

			}
			else if (CurState == SQUAT) {

				if (m_LV == 1) {
					if (m_bStaring) {
						m_Animation.SetFrames(s_pSpiritsLV1Star[IDLE], 0, FRAMENUM_IDLE_STAR, 100);
					}
					else {
						m_Animation.SetFrames(s_pSpiritsLV1[IDLE], 0, FRAMENUM_IDLE, 100);
					}
				}
				else if (m_LV == 2) {
					if (m_bStaring) {
						m_Animation.SetFrames(s_pSpiritsLV2Star[SQUAT], 0, FRAMENUM_SQUAT_STAR, 100);

					}
					else {
						m_Animation.SetFrames(s_pSpiritsLV2[SQUAT], 0, FRAMENUM_SQUAT, 100);

					}

				}
				else if (m_LV == 3) {
					if (m_bStaring) {
						m_Animation.SetFrames(s_pSpiritsLV3Star[SQUAT], 0, FRAMENUM_SQUAT_STAR, 100);

					}
					else {
						m_Animation.SetFrames(s_pSpiritsLV3[SQUAT], 0, FRAMENUM_SQUAT, 100);

					}

				}

			}
			else if (CurState == IDLE) {

				if (m_LV == 1) {
					if (m_bStaring) {
						m_Animation.SetFrames(s_pSpiritsLV1Star[IDLE], 0, FRAMENUM_IDLE_STAR, 100);
					}
					else {
						m_Animation.SetFrames(s_pSpiritsLV1[IDLE], 0, FRAMENUM_IDLE, 100);

					}
				}
				else if (m_LV == 2) {
					if (m_bStaring) {
						m_Animation.SetFrames(s_pSpiritsLV2Star[IDLE], 0, FRAMENUM_IDLE_STAR, 100);

					}
					else {
						m_Animation.SetFrames(s_pSpiritsLV2[IDLE], 0, FRAMENUM_IDLE, 100);

					}
				}
				else if (m_LV == 3) {
					if (m_bStaring) {
						m_Animation.SetFrames(s_pSpiritsLV3Star[IDLE], 0, FRAMENUM_IDLE_STAR, 100);
					}
					else {
						m_Animation.SetFrames(s_pSpiritsLV3[IDLE], 0, FRAMENUM_IDLE, 100);
					}
				}
			}
		}

	}
	m_Animation.Update();

}

Player::Player(TileMap * pTileMap)
{
	this->e_pTileMap = pTileMap;
	m_x = 100.0f;
	m_y = 100.0f;
	m_dx = 0.0f;
	m_dy = 0.0f;
	m_CX = 5;
	m_CY = 64;
	m_CWidth = Config::TILE_SIZE - m_CX * 2;
	m_CHeight = Config::TILE_SIZE;
	/////////////////////////////////
	m_iColOffsetBeg = 0;
	m_iRowOffsetBeg = 0;
	m_iColOffsetEnd = 0;
	m_iRowOffsetEnd = 0;
	//movement
	m_bLeft = false;
	m_bRight = false;
	m_bUp = false;
	m_bDown = false;
	m_bJump = false;
	/////////////////////////////////////////////////
	m_MoveSpeed = 1.5f;		    //初始移动速度
	m_MoveSpeedMax = 240.0f;	    //最大移动速度
	m_MoveStopSpeed = 1.5f;		//松开按钮的减速
	/////////////////////////////////////////////////
	m_bTouch = false;
	m_JumpHeightMin = 100.0f;
	m_JumpHeightMax = 400.0f;
	m_TimeToJumpApex = 0.6f;
	m_Gravity = (2.0f * m_JumpHeightMax) / (m_TimeToJumpApex*m_TimeToJumpApex);
	m_JumpVelocityMin = -sqrtf(2.0f * m_Gravity * m_JumpHeightMin);
	m_JumpVelocityMax = -(m_Gravity * m_TimeToJumpApex);
	//////////////////////////////////////////////
	//////////////////////////////////////////////////////
	m_bDelete = false;
	//////////////////////////////////////////////////////
	m_Animation.SetFrames(s_pSpiritsLV1[IDLE], 0, FRAMENUM_IDLE, 0);
	CurState = 0;
	PreState = 0;
	m_bFacingRight = true;
	////////////////////
	m_bStaring = false;
	////////////////////////
	m_bPowerUping = false;
	m_bPowerUpAni = false;
	////////////////////////
	m_bFireing = false;
	////////////////////////
	m_bCanFire = false;
	m_bFire = false;//key 
	/////////////////////
	m_LV = 1;
}

Player::~Player()
{
}

