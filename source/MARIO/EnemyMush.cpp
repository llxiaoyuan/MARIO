#include "EnemyMush.h"
#include"TileMap.h"
MyImg** EnemyMush::s_pSpirits[2] = { nullptr, nullptr };

void EnemyMush::LoadRes(SDL_Renderer * pRenderer)
{
	s_pSpirits[WALK] = new MyImg*[FRAMENUM_WALK];
	s_pSpirits[WALK][0] = new MyImg("res/images/enemy/mush/walk0.bmp", pRenderer);
	s_pSpirits[WALK][1] = new MyImg("res/images/enemy/mush/walk1.bmp", pRenderer);

	s_pSpirits[TRAMPLE] = new MyImg*[FRAMENUM_TRAMPLE];
	s_pSpirits[TRAMPLE][0] = new MyImg("res/images/enemy/mush/dead0.bmp", pRenderer);
}

void EnemyMush::FreeRes()
{
	for (int i = 0; i < FRAMENUM_WALK; i++)delete s_pSpirits[WALK][i];delete[] s_pSpirits[WALK];
	for (int i = 0; i < FRAMENUM_TRAMPLE; i++)delete s_pSpirits[TRAMPLE][i]; delete[] s_pSpirits[TRAMPLE];
}

void EnemyMush::Update(float dt)
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
		///////////////////////////////////
		if ((int)m_y + m_CY >= Config::H_SCREEN) {
			m_bDelete = true;
		}
		///////////////////////////////////
		if (m_bTrample) {
			m_bDelete = m_tDelete.Update();
		}
	}
	else {
		if (bOnScreen())m_bActive = true;
	}
	
}

void EnemyMush::AnimationAction()
{
	
	PreState = CurState;
	if (!m_bTrample) {
		CurState = WALK;
	}
	else {
		CurState = TRAMPLE;
	}
	if(CurState == WALK){
		m_Animation.SetFrames(s_pSpirits[WALK], 0, FRAMENUM_WALK, 200);
	}
	else if (CurState == TRAMPLE) {
		m_Animation.SetFrames(s_pSpirits[TRAMPLE], 0, FRAMENUM_TRAMPLE, 200);
	}
	m_Animation.Update();
}

void EnemyMush::HorCollisionWithEnemy()
{
	if (m_bCollisionWithEnemy) {
		for (size_t i = 0; i < e_pTileMap->m_Enemy.size(); i++)
		{
			if (e_pTileMap->m_Enemy[i] != this) {
				if (e_pTileMap->m_Enemy[i]->bCollisionWithEnemy()) {
					if (e_pTileMap->m_Enemy[i]->bIntersect(this)) {
						if (m_dx > 0.0f) {
							e_pTileMap->m_Enemy[i]->SetOtherToSelfLeft(this);
						}
						else if (m_dx < 0.0f) {
							e_pTileMap->m_Enemy[i]->SetOtherToSelfRight(this);
						}
						m_dx = 0.0f;
						SetTurn();
					}
				}
			}
		}
	}
}

void EnemyMush::VerCollisionWithEnemy()
{
	if (m_bCollisionWithEnemy) {
		for (size_t i = 0; i < e_pTileMap->m_Enemy.size(); i++)
		{
			if (e_pTileMap->m_Enemy[i] != this) {
				if (e_pTileMap->m_Enemy[i]->bCollisionWithEnemy()) {
					if (e_pTileMap->m_Enemy[i]->bIntersect(this)) {
						if (m_dy > 0.0f) {
							e_pTileMap->m_Enemy[i]->SetOtherToSelfUp(this);
						}
						else if (m_dy < 0.0f) {
							e_pTileMap->m_Enemy[i]->SetOtherToSelfDown(this);
						}
						m_dy = 0.0f;
					}
				}
			}
		}
	}
}

void EnemyMush::CollisionWithPlayer()
{
	if (m_bCollisionWithPlayer) {
		if (bIntersect(e_pTileMap->m_Player)) {
			if (e_pTileMap->m_Player->bStaring()) {
				Kill();
			}
			else {
				if (e_pTileMap->m_Player->GetDy() > 0.0f) {
					SetTrample();
					e_pTileMap->m_Player->Bounce();
				}
				else {
					printf("被Mushroom撞到\n");
				}
			}
			
		}
	}
}

//被踩
void EnemyMush::SetTrample()
{
	m_bLeft = false;
	m_bRight = false;
	m_dx = 0.0f;

	m_bCollisionWithFireBall = false;
	m_bCollisionWithPlayer = false;
	m_bTrample = true;
	m_tDelete.Init(2000);
}


EnemyMush::EnemyMush(TileMap * pTileMap, int x, int y, bool bRight)
{
	////////////////
	this->e_pTileMap = pTileMap;
	m_x = (float)x;
	m_y = (float)y;
	m_dx = 0.0f;
	m_dy = 0.0f;
	//collision box
	m_CX = 0;
	m_CY = 0;
	m_CWidth = Config::TILE_SIZE;
	m_CHeight = Config::TILE_SIZE;
	//////////////////////////////////
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
	m_MoveSpeed = 100.0f;		//初始移动速度
	m_MoveSpeedMax = 100.0f;	    //最大移动速度
	m_MoveStopSpeed = 100.0f;		//松开按钮的减速
	/////////////////////////////////////////////////
	m_bTouch = false;
	m_JumpHeightMin = 100.0f;
	m_JumpHeightMax = 400.0f;
	m_TimeToJumpApex = 0.6f;
	m_Gravity = (2.0f * m_JumpHeightMax) / (m_TimeToJumpApex*m_TimeToJumpApex);
	m_JumpVelocityMin = -sqrtf(2.0f * m_Gravity * m_JumpHeightMin);
	m_JumpVelocityMax = -(m_Gravity * m_TimeToJumpApex);
	//////////////////////////////////////////////////////
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
	///////////////////////
	m_bTrample  = false;
	///////////////////
	if (bRight)
		this->SetRight(true);
	else
		this->SetLeft(true);
}
EnemyMush::~EnemyMush()
{
}
