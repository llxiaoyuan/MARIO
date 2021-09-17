#include "Star.h"
#include "TileMap.h"
#include "Player.h"
MyImg* Star::s_pSpirits[4] = { nullptr,nullptr,nullptr,nullptr };
void Star::LoadRes(SDL_Renderer * pRenderer)
{
	s_pSpirits[0] = new MyImg("res/images/star/star0.bmp", pRenderer);
	s_pSpirits[1] = new MyImg("res/images/star/star1.bmp", pRenderer);
	s_pSpirits[2] = new MyImg("res/images/star/star2.bmp", pRenderer);
	s_pSpirits[3] = new MyImg("res/images/star/star3.bmp", pRenderer);
}

void Star::FreeRes()
{
	delete s_pSpirits[0];
	delete s_pSpirits[1];
	delete s_pSpirits[2];
	delete s_pSpirits[3];
}
void Star::Update(float dt)
{
	if (m_bSpawn) {
		m_y -= dt * m_MoveSpeed;
		if ((int)m_y <  m_SpawnStartY - Config::TILE_SIZE) {
			m_y = float(m_SpawnStartY - Config::TILE_SIZE);
			m_bSpawn = false;
		}
	}
	else {
		Action();
		CalcMapOffset();
		m_x += dt * m_dx;
		HorCollisionWithMap();
		m_dy += dt * m_Gravity;
		m_y += dt * m_dy;
		VerCollisionWithMap();
		CollisionWithPlayer();
		OntheGroundTest();
	}
	AnimationAction();
}

void Star::CollisionWithPlayer()
{
	if (!m_bSpawn) {
		if (bIntersect(e_pTileMap->m_Player)) {
			m_bDelete = true;
			/////////////////////////////////////
			e_pTileMap->m_Player->EatStar();
		}
	}
}


Star::Star(TileMap * pTileMap, int x, int y)
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
	///////////////////////
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
	m_MoveSpeed = 100.0f;		    //��ʼ�ƶ��ٶ�
	m_MoveSpeedMax = 100.0f;	    //����ƶ��ٶ�
	m_MoveStopSpeed = 100.0f;		//�ɿ���ť�ļ���
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
	m_Animation.SetFrames(s_pSpirits, 0, 4, 50);
	CurState = 0;
	PreState = 0;
	m_bFacingRight = true;
	////////////////////////////
	m_SpawnStartX = x;
	m_SpawnStartY = y;
	m_bSpawn = true;
	////////////////////////////
	this->SetRight(true);
	this->SetJump(true);
}

Star::~Star()
{
}