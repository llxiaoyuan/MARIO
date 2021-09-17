#include "FireBall.h"
#include "TileMap.h"

MyImg* FireBall::s_pSpirits[4] = { nullptr,nullptr,nullptr,nullptr };


void FireBall::LoadRes(SDL_Renderer * pRenderer)
{
	s_pSpirits[0] = new MyImg("res/images/fireball/fireball0.bmp", pRenderer);
	s_pSpirits[1] = new MyImg("res/images/fireball/fireball1.bmp", pRenderer);
	s_pSpirits[2] = new MyImg("res/images/fireball/fireball2.bmp", pRenderer);
	s_pSpirits[3] = new MyImg("res/images/fireball/fireball3.bmp", pRenderer);
}

void FireBall::FreeRes()
{
	delete s_pSpirits[0];
	delete s_pSpirits[1];
	delete s_pSpirits[2];
	delete s_pSpirits[3];
}

void FireBall::Update(float dt)
{
	Action();
	AnimationAction();
	CalcMapOffset();
	m_x += dt * m_dx;
	HorCollisionWithMap();
	m_dy += dt * m_Gravity;
	m_y += dt * m_dy;
	VerCollisionWithMap();
	OntheGroundTest();
}
void FireBall::HorCollisionWithMap()
{
	//地图边界
	if ((int)m_x + m_CX < 0) {
		m_x = -(float)m_CX;
		m_dx = 0.0f;
		Remove();
	}
	else if ((int)m_x + m_CX > (e_pTileMap->GetColNum()*e_pTileMap->GetTileSize()) - m_CWidth) {
		m_x = (float)((e_pTileMap->GetColNum()*e_pTileMap->GetTileSize()) - m_CWidth - m_CX);
		m_dx = 0.0f;
		Remove();
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
							Remove();
						}
					}
				}
			}
		}
	}
					
}

void FireBall::Remove()
{
	m_bDelete = true;
	e_pTileMap->CreateFireBallWork((int)m_x - Config::TILE_SIZE / 4, (int)m_y - Config::TILE_SIZE / 4);

}

FireBall::FireBall(TileMap * pTileMap, int x, int y, bool bRight)
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
	m_CWidth  = Config::TILE_SIZE / 2;
	m_CHeight = Config::TILE_SIZE / 2;
	///////////////////////
	m_iColOffsetBeg = 0;
	m_iRowOffsetBeg = 0;
	m_iColOffsetEnd = 0;
	m_iRowOffsetEnd = 0;
	//movement
	m_bLeft  = false;
	m_bRight = false;
	m_bUp    = false;
	m_bDown  = false;
	m_bJump  = false;
	/////////////////////////////////////////////////
	m_MoveSpeed = 800.0f;		   //初始移动速度
	m_MoveSpeedMax = 800.0f;	    //最大移动速度
	m_MoveStopSpeed = 800.0f;		//松开按钮的减速
	/////////////////////////////////////////////////
	m_bTouch = false;
	m_JumpHeightMin = 80.0f;
	m_JumpHeightMax = 80.0f;
	m_TimeToJumpApex = 0.15f;
	m_Gravity = (2.0f * m_JumpHeightMax) / (m_TimeToJumpApex*m_TimeToJumpApex);
	m_JumpVelocityMin = -sqrtf(2.0f * m_Gravity * m_JumpHeightMin);
	m_JumpVelocityMax = -(m_Gravity * m_TimeToJumpApex);
	////////////////////////////////////////////////////
	m_bDelete = false;
	//////////////////////////////////////////////////////
	m_Animation.SetFrames(s_pSpirits, 0, 4, 50);
	CurState = 0;
	PreState = 0;
	m_bFacingRight = true;
	////////////////////////////
	SetJump(true);
	if(bRight)
		this->SetRight(true);
	else 
		this->SetLeft(true);
}

FireBall::~FireBall()
{
}
