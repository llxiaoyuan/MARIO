#include "EnemyKoopa.h"
#include "TileMap.h"
MyImg** EnemyKoopa::s_pSpirits[3] = { nullptr, nullptr , nullptr };

void EnemyKoopa::LoadRes(SDL_Renderer * pRenderer)
{
	s_pSpirits[WALK] = new MyImg*[FRAMENUM_WALK];
	s_pSpirits[WALK][0] = new MyImg("res/images/enemy/koopa/koopa_0.bmp", pRenderer);
	s_pSpirits[WALK][1] = new MyImg("res/images/enemy/koopa/koopa_1.bmp", pRenderer);

	s_pSpirits[TRAMPLE] = new MyImg*[FRAMENUM_TRAMPLE];
	s_pSpirits[TRAMPLE][0] = new MyImg("res/images/enemy/koopa/dead0.bmp", pRenderer);

	s_pSpirits[ANABIOSIS] = new MyImg*[FRAMENUM_ANABIOSIS];
	s_pSpirits[ANABIOSIS][0] = new MyImg("res/images/enemy/koopa/dead0.bmp", pRenderer);
	s_pSpirits[ANABIOSIS][1] = new MyImg("res/images/enemy/koopa/rel0.bmp", pRenderer);
}

void EnemyKoopa::FreeRes()
{
	for (int i = 0; i < FRAMENUM_WALK; i++) delete s_pSpirits[WALK][i];delete[] s_pSpirits[WALK];
	for (int i = 0; i < FRAMENUM_TRAMPLE; i++)delete s_pSpirits[TRAMPLE][i];delete[] s_pSpirits[TRAMPLE];
	for (int i = 0; i < FRAMENUM_ANABIOSIS; i++)delete s_pSpirits[ANABIOSIS][i]; delete[] s_pSpirits[ANABIOSIS];

}
/////////////////////////////////////////////////////////////////////////////////////
void EnemyKoopa::Update(float dt)
{
	if (m_bActive) {
	
		Action();
		AnimationAction();
		/////////////////////////////
		if (!m_bDead) {
			CalcMapOffset();
			m_x += dt * m_dx;
			HorCollisionWithMap();
			HorCollisionWithEnemy();
			m_dy += dt * m_Gravity;
			m_y += dt * m_dy;
			VerCollisionWithMap();
			VerCollisionWithEnemy();
			CollisionWithPlayer();
			CollisionWithFireBall();
			OntheGroundTest();
		}
		else {
			m_x += dt * m_dx;
			m_dy += dt * 5000;
			m_y += dt * (m_dy - 500.f);
		}
		if ((int)m_y + m_CY >= Config::H_SCREEN) {
			m_bDelete = true;
		}
	}
	else {
		if (bOnScreen())m_bActive = true;
	}

}

void EnemyKoopa::AnimationAction()
{
	m_bAnabiosis1 = !m_tAnabiosis1.Update();
	m_bAnabiosis2 = !m_tAnabiosis2.Update();

	if (!m_bGliding && m_bTrample) {
		if (m_bAnabiosis2 == false) {
			RelTrample();
		}
	}
	if (m_bAnabiosis1) {
		m_Animation.SetFrames(s_pSpirits[TRAMPLE], 0, FRAMENUM_TRAMPLE, 200);
	}
	else if (m_bAnabiosis2 && !m_bGliding && m_bTrample) {
		m_Animation.SetFrames(s_pSpirits[ANABIOSIS], 0, FRAMENUM_ANABIOSIS, 200);
	}
	else {
		if (!m_bTrample) {
			m_Animation.SetFrames(s_pSpirits[WALK], 0, FRAMENUM_WALK, 200);
		}
		else {
			m_Animation.SetFrames(s_pSpirits[TRAMPLE], 0, FRAMENUM_TRAMPLE, 200);
		}
	}

	
	m_Animation.Update();
}

void EnemyKoopa::HorCollisionWithEnemy()
{

	if (m_bCollisionWithEnemy) {
		for (size_t i = 0; i < e_pTileMap->m_Enemy.size(); i++)
		{
			if (e_pTileMap->m_Enemy[i] != this) {
				if (e_pTileMap->m_Enemy[i]->bCollisionWithEnemy()) {
					if (e_pTileMap->m_Enemy[i]->bIntersect(this)) {
						if (!m_bGliding) {
							if (m_dx > 0.0f) {
								e_pTileMap->m_Enemy[i]->SetOtherToSelfLeft(this);
							}
							else if (m_dx < 0.0f) {
								e_pTileMap->m_Enemy[i]->SetOtherToSelfRight(this);
							}
							m_dx = 0.0f;
							SetTurn();
						}
						else {
							e_pTileMap->m_Enemy[i]->Kill();
						}
						
					}
				}
			}
		}
	}
}

void EnemyKoopa::VerCollisionWithEnemy()
{

	if (m_bCollisionWithEnemy) {
		for (size_t i = 0; i < e_pTileMap->m_Enemy.size(); i++)
		{
			if (e_pTileMap->m_Enemy[i] != this) {
				if (e_pTileMap->m_Enemy[i]->bCollisionWithEnemy()) {
					if (e_pTileMap->m_Enemy[i]->bIntersect(this)) {
						if (!m_bGliding){
							if (m_dy > 0.0f) {
								e_pTileMap->m_Enemy[i]->SetOtherToSelfUp(this);
							}
							else if (m_dy < 0.0f) {
								e_pTileMap->m_Enemy[i]->SetOtherToSelfDown(this);
							}
							m_dy = 0.0f;
						}
						else {
							e_pTileMap->m_Enemy[i]->Kill();
						}
					}
				}
			}
		}
	}
}
void EnemyKoopa::CollisionWithPlayer()
{
	if (m_bCollisionWithPlayer) {
		if (bIntersect(e_pTileMap->m_Player)) {
			if (e_pTileMap->m_Player->bStaring()) {
				Kill();
			}
			else {
				//行走
				if (!m_bTrample && !m_bGliding) {
					if (e_pTileMap->m_Player->GetDy() > 0.0f)
					{
						SetTrample();
						SetOtherToSelfUp(e_pTileMap->m_Player);
						e_pTileMap->m_Player->Bounce();
					}
					else {
						printf("被koopa撞到\n");
					}
				}
				//在壳里 原地
				else if (m_bTrample && !m_bGliding)
				{
					m_bCollisionWithPlayer = false;
					if (e_pTileMap->m_Player->GetX() + e_pTileMap->m_Player->GetCX() > (int)m_x + m_CX) {
						SetKickLeft();
					}
					else {
						SetKickRight();
					}
				}
				//在壳里 && 滑行
				else if (m_bTrample && m_bGliding) {
					if (e_pTileMap->m_Player->GetDy() > 0.0f)
					{
						SetTrample();
						SetOtherToSelfUp(e_pTileMap->m_Player);
						e_pTileMap->m_Player->Bounce();
					}
					else {
						printf("被koopa壳撞到\n");
					}
				}
			}

		}
	}
}

void EnemyKoopa::HorCollisionWithMap()
{
	//地图边界
	if ((int)m_x + m_CX < 0) {
		m_x = -(float)m_CX;
		m_dx = 0.0f;
		SetTurn();
		m_bCollisionWithPlayer = true;
	}
	else if ((int)m_x + m_CX > (e_pTileMap->GetColNum()*e_pTileMap->GetTileSize()) - m_CWidth) {
		m_x = (float)((e_pTileMap->GetColNum()*e_pTileMap->GetTileSize()) - m_CWidth - m_CX);
		m_dx = 0.0f;
		SetTurn();
		m_bCollisionWithPlayer = true;

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
							m_bCollisionWithPlayer = true;

						}
					}
				}
			}
		}
	}

}

void EnemyKoopa::SetTrample()
{
	m_tAnabiosis1.Init(2000);
	m_tAnabiosis2.Init(4000);
	m_bLeft = false;
	m_bRight = false;
	m_dx = 0.0f;
	////////////////////////////////////////////////////////////
	m_bTrample = true;
	m_bGliding = false;
}

void EnemyKoopa::RelTrample()
{
	if (m_bFacingRight) {
		m_bLeft = false;
		m_bRight = true;
	}
	else {
		m_bLeft = true;
		m_bRight = false;
	}
	m_MoveSpeed		= 100.0f;
	m_MoveSpeedMax  = 100.0f;
	m_MoveStopSpeed = 100.0f;
	m_bTrample = false;
	m_bGliding = false;
}

void EnemyKoopa::SetKickLeft()
{
	m_MoveSpeed		= 600.0f;
	m_MoveSpeedMax	= 600.0f;
	m_MoveStopSpeed = 600.0f;
	m_bLeft = true;
	m_bRight = false;
	m_bGliding = true;
}

void EnemyKoopa::SetKickRight()
{
	m_MoveSpeed      = 600.0f;
	m_MoveSpeedMax   = 600.0f;
	m_MoveStopSpeed  = 600.0f;
	m_bLeft = false;
	m_bRight = true;
	m_bGliding = true;
}

EnemyKoopa::EnemyKoopa(TileMap * pTileMap, int x, int y, bool bRight)
{
	this->e_pTileMap = pTileMap;
	m_x = (float)x;
	m_y = (float)y;
	m_dx = 0.0f;
	m_dy = 0.0f;
	//collision box
	m_CX =  0;
	m_CY = 28;
	m_CWidth = Config::TILE_SIZE;
	m_CHeight = Config::TILE_SIZE;
	//////////////////////////
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
	m_MoveSpeed     = 100.0f;		//初始移动速度
	m_MoveSpeedMax  = 100.0f;	    //最大移动速度
	m_MoveStopSpeed = 100.0f;		//松开按钮的减速
	/////////////////////////////////////////////////
	m_bTouch = false;
	m_JumpHeightMin = 100.0f;
	m_JumpHeightMax = 400.0f;
	m_TimeToJumpApex = 0.6f;
	m_Gravity = (2.0f * m_JumpHeightMax) / (m_TimeToJumpApex*m_TimeToJumpApex);
	m_JumpVelocityMin = -sqrtf(2.0f * m_Gravity * m_JumpHeightMin);
	m_JumpVelocityMax = -(m_Gravity * m_TimeToJumpApex);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_bDelete = false;
	//////////////////////////////////////////////////////
	m_Animation.SetFrames(s_pSpirits[WALK], 0, FRAMENUM_WALK, 100);
	CurState = WALK;
	PreState = WALK;
	m_bFacingRight = true;
	//////////////
	m_bActive = false;
	m_bCollisionWithEnemy = true;
	m_bCollisionWithFireBall = true;
	m_bCollisionWithPlayer = true;
	m_bDead = false;	   //被火球 或被 龟壳
	///////////////////////////
	m_bTrample = false;    //被踩
	m_bGliding = false;
	/////////////////////
	m_bAnabiosis1 = false;
	////////////////////////////////////////////////
	m_bAnabiosis2 = false;
	///////////////////////
	if (bRight)
		this->SetRight(true);
	else
		this->SetLeft(true);
	
}

EnemyKoopa::~EnemyKoopa()
{
}
