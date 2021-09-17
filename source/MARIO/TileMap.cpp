#include "TileMap.h"

MyImg*   TileMap::s_pImgGround = nullptr;
MyImg*   TileMap::s_pImgBrick = nullptr;
MyImg*   TileMap::s_pImgBox[3] = { nullptr ,nullptr,nullptr };
MyImg*   TileMap::s_pImgBoxUsed = nullptr;

void TileMap::LoadRes(SDL_Renderer * pRender)
{
	s_pImgGround = new MyImg("res/images/Ground_0.bmp", pRender);
	s_pImgBrick = new MyImg("res/images/Brick_0.bmp", pRender);
	s_pImgBox[0] = new MyImg("res/images/Box_0.bmp", pRender);
	s_pImgBox[1] = new MyImg("res/images/Box_1.bmp", pRender);
	s_pImgBox[2] = new MyImg("res/images/Box_2.bmp", pRender);
	s_pImgBoxUsed = new MyImg("res/images/BoxUsed_0.bmp", pRender);
}
void TileMap::FreeRes()
{
	delete  s_pImgGround;
	delete	s_pImgBrick;
	delete	s_pImgBox[0];
	delete  s_pImgBox[1];
	delete  s_pImgBox[2];
	delete  s_pImgBoxUsed;
}
void TileMap::Update(float dt)
{
	m_AnimationBox.Update();
	if (!m_Player->bPowerUping()) {
		CalcOffset();
		//更新蘑菇
		for (size_t i = 0; i < m_Mush.size(); i++) {
			m_Mush[i]->Update(dt);
		}
		//更新花
		for (size_t i = 0; i < m_Flower.size(); i++) {
			m_Flower[i]->Update(dt);
		}
		//更新星星
		for (size_t i = 0; i < m_Star.size(); i++) {
			m_Star[i]->Update(dt);
		}
		//更新砖块碎片
		for (size_t i = 0; i < m_BlockDebris.size(); i++) {
			m_BlockDebris[i]->Update(dt);
		}
		//更新跳跃的金币
		for (size_t i = 0; i < m_CoinJump.size(); i++) {
			m_CoinJump[i]->Update(dt);
		}
		//更新地图
		for (int row = m_iRowOffsetBeg; row < m_iRowOffsetEnd; row++) {
			for (int col = m_iColOffsetBeg; col < m_iColOffsetEnd; col++) {
				if (m_pMap[row][col]->GetID() != Tile::TILES_NULL) {
					m_pMap[row][col]->Update(dt);
				}
			}
		}
		//更新敌人
		for (size_t i = 0; i < m_Enemy.size(); i++) {
			m_Enemy[i]->Update(dt);
		}
		//更新火球
		for (size_t i = 0; i < m_FireBall.size(); i++) {
			m_FireBall[i]->Update(dt);
		}
		//更新爆炸
		for (size_t i = 0; i < m_FireBallWork.size(); i++) {
			m_FireBallWork[i]->Update(dt);
		}
		//蘑菇的删除
		for (auto iter = m_Mush.begin(); iter != m_Mush.end();)
		{
			if ((*iter)->bDelete()) {
				delete (*iter);
				iter = m_Mush.erase(iter);
				////////////////////////////////////////
			}
			else {
				iter++;
			}
		}
		//花的删除
		for (auto iter = m_Flower.begin(); iter != m_Flower.end();)
		{
			if ((*iter)->bDelete()) {
				delete (*iter);
				iter = m_Flower.erase(iter);
				////////////////////////////////////////
			}
			else {
				iter++;
			}
		}
		//星星的删除
		for (auto iter = m_Star.begin(); iter != m_Star.end();)
		{
			if ((*iter)->bDelete()) {
				delete (*iter);
				iter = m_Star.erase(iter);
				////////////////////////////////////////
			}
			else {
				iter++;
			}
		}

		//砖块碎片的删除
		for (auto iter = m_BlockDebris.begin(); iter != m_BlockDebris.end();)
		{
			if ((*iter)->bDelete()) {
				delete (*iter);
				iter = m_BlockDebris.erase(iter);
				////////////////////////////////////////
			}
			else {
				iter++;
			}
		}
		//跳跃金币的删除
		for (auto iter = m_CoinJump.begin(); iter != m_CoinJump.end();)
		{
			if ((*iter)->bDelete()) {
				delete (*iter);
				iter = m_CoinJump.erase(iter);
				////////////////////////////////////////
			}
			else {
				iter++;
			}
		}
		//敌人的删除
		for (auto iter = m_Enemy.begin(); iter != m_Enemy.end();)
		{
			if ((*iter)->bDelete()) {
				delete (*iter);
				iter = m_Enemy.erase(iter);
				////////////////////////////////////////
			}
			else {
				iter++;
			}
		}
		//火球的删除
		for (auto iter = m_FireBall.begin(); iter != m_FireBall.end();)
		{
			if ((*iter)->bDelete()) {
				delete (*iter);
				iter = m_FireBall.erase(iter);
				////////////////////////////////////////
			}
			else {
				iter++;
			}
		}
		//爆炸的删除
		for (auto iter = m_FireBallWork.begin(); iter != m_FireBallWork.end();)
		{
			if ((*iter)->bDelete()) {
				delete (*iter);
				iter = m_FireBallWork.erase(iter);
				////////////////////////////////////////
			}
			else {
				iter++;
			}
		}
		//玩家更新
		m_Player->Update(dt);
		m_pBackGround->SetX(m_x);
		m_pBackGround->SetY(0);
	}
	else {
		m_Player->AnimationAction();
	}


	if (m_Enemy.size() <= 1) {
		CreateEnemy();
	}

}

void TileMap::Render(SDL_Renderer * pRender)
{
	m_pBackGround->Render(pRender);
	//蘑菇的绘制
	for (size_t i = 0; i < m_Mush.size(); i++) {
		m_Mush[i]->Render(pRender);
	}
	//花的绘制
	for (size_t i = 0; i < m_Flower.size(); i++) {
		m_Flower[i]->Render(pRender);
	}
	//星星的绘制
	for (size_t i = 0; i < m_Star.size(); i++) {
		m_Star[i]->Render(pRender);
	}
	//方块碎片的绘制
	for (size_t i = 0; i < m_BlockDebris.size(); i++) {
		m_BlockDebris[i]->Render(pRender);
	}
	//跳跃金币的绘制
	for (size_t i = 0; i < m_CoinJump.size(); i++) {
		m_CoinJump[i]->Render(pRender);
	}
	//地图的绘制
	for (int row = m_iRowOffsetBeg; row < m_iRowOffsetEnd; row++) {
		for (int col = m_iColOffsetBeg; col < m_iColOffsetEnd; col++) {
			if (m_pMap[row][col]->GetID() != Tile::TILES_NULL) {
				if (m_pMap[row][col]->bVisible()) {
					if (m_pMap[row][col]->GetID() == Tile::TILES_GROUND) {
						s_pImgGround->Render(pRender, m_x + m_pMap[row][col]->GetX(), m_y + m_pMap[row][col]->GetY());
					}
					else if (m_pMap[row][col]->GetID() == Tile::TILES_BRICK) {
						s_pImgBrick->Render(pRender, m_x + m_pMap[row][col]->GetX(), m_y + m_pMap[row][col]->GetY());
					}
					else if (m_pMap[row][col]->GetID() == Tile::TILES_BOX) {

						m_AnimationBox.GetCurImage()->Render(pRender, m_x + m_pMap[row][col]->GetX(), m_y + m_pMap[row][col]->GetY());
					}
					else if (m_pMap[row][col]->GetID() == Tile::TILES_BOXUSED) {
						s_pImgBoxUsed->Render(pRender, m_x + m_pMap[row][col]->GetX(), m_y + m_pMap[row][col]->GetY());
					}
				}
			}
		}
	}
	//敌人的绘制
	for (size_t i = 0; i < m_Enemy.size(); i++) {
		m_Enemy[i]->Render(pRender);
	}
	//fireball
	for (size_t i = 0; i < m_FireBall.size(); i++) {
		m_FireBall[i]->Render(pRender);
	}
	//fireballwork
	for (size_t i = 0; i < m_FireBallWork.size(); i++) {
		m_FireBallWork[i]->Render(pRender);
	}
	//玩家的绘制
	m_Player->Render(pRender);
}


int TileMap::GetTileSize()
{
	return m_TileSize;
}

int TileMap::GetMapX()
{
	return m_x;
}

int TileMap::GetMapY()
{
	return m_y;
}

int TileMap::GetRowNum()
{
	return m_RowNum;
}

int TileMap::GetColNum()
{
	return m_ColNum;
}


void TileMap::CreateMush(int x, int y)
{
	m_Mush.push_back(new Mush(this, x, y));
}

void TileMap::CreateFlower(int x, int y)
{
	m_Flower.push_back(new Flower(this, x, y));
}

void TileMap::CreateStar(int x, int y)
{
	m_Star.push_back(new Star(this, x, y));
}

void TileMap::CreateBlockDebris(int x, int y)
{
	m_BlockDebris.push_back(new BlockDebris(this, x, y));
}

void TileMap::CreateCoinJump(int x, int y)
{
	m_CoinJump.push_back(new CoinJump(this, x, y));
}

void TileMap::CreateEnemy()
{
	for (size_t i = 0; i < 4; i++)
	{
		m_Enemy.push_back(new EnemyMush(this, i * 200, 200, true));
	}
	for (size_t i = 0; i < 4; i++)
	{
		m_Enemy.push_back(new EnemyKoopa(this, i * 200 + 500, 200, true));
	}
}

void TileMap::CreateFireBall(int x, int y, bool bRight)
{
	m_FireBall.push_back(new FireBall(this, x, y, bRight));
}

void TileMap::CreateFireBallWork(int x, int y) {
	m_FireBallWork.push_back(new FireBallWork(this, x, y));
}

void TileMap::SetNumRange(int * pNum, int nMin, int nMax)
{
	if (*pNum < nMin)  *pNum = nMin;
	else if (*pNum > nMax)  *pNum = nMax;
}

void TileMap::CalcOffset()
{
	m_iColOffsetBeg = (-m_x / m_TileSize) - 1;
	SetNumRange(&m_iColOffsetBeg, 0, m_ColNum);
	m_iRowOffsetBeg = (-m_y / m_TileSize) - 1;
	SetNumRange(&m_iRowOffsetBeg, 0, m_RowNum);
	m_iColOffsetEnd = (-m_x + (Config::W_SCREEN - 1)) / m_TileSize + 2;
	SetNumRange(&m_iColOffsetEnd, 0, m_ColNum);
	m_iRowOffsetEnd = (-m_y + (Config::H_SCREEN - 1)) / m_TileSize + 2;
	SetNumRange(&m_iRowOffsetEnd, 0, m_RowNum);
}
void TileMap::InitMap(std::string sFileName)
{
	std::ifstream ifsMapData;
	ifsMapData.open(sFileName, std::ios::in);
	ifsMapData >> m_ColNum;
	ifsMapData >> m_RowNum;
	//地图内存开辟
	m_pMap = new Tile**[m_RowNum];
	for (int row = 0; row < m_RowNum; row++)
	{
		m_pMap[row] = new Tile*[m_ColNum];
		/*for (int col = 0; col < m_ColNum; col++) {
			m_pMap[row][col] = new Tile();
		}*/
	}
	//读取
	int tempID = 0;
	for (int row = 0; row < m_RowNum; row++) {
		for (int col = 0; col < m_ColNum; col++) {
			ifsMapData >> tempID;
			m_pMap[row][col] = new Tile(this,
				col * Config::TILE_SIZE, row * Config::TILE_SIZE, tempID);
		}
	}
	ifsMapData.close();
}

TileMap::TileMap(std::string sFileName)
{
	m_AnimationBox.SetFrames(s_pImgBox, 0, 3, 300);
	////////////////////////////////////////////
	InitMap(sFileName);
	m_TileSize = Config::TILE_SIZE;

	m_x = 0;
	m_y = 0;
	m_xMin = Config::W_SCREEN - m_TileSize * m_ColNum;
	m_yMin = Config::H_SCREEN - m_TileSize * m_RowNum;
	m_xMax = 0;
	m_yMax = 0;
	if (m_xMin > m_xMax)m_xMin = m_xMax;//避免地图过小
	if (m_yMin > m_yMax)m_yMin = m_yMax;

	m_iColOffsetBeg = 0;
	m_iRowOffsetBeg = 0;
	m_iColOffsetEnd = m_ColNum;
	m_iRowOffsetEnd = m_RowNum;

	//放置道具
	m_pMap[9][21]->SetIDInside(Tile::INSIDE_STAR);
	m_pMap[9][23]->SetIDInside(Tile::INSIDE_LVUP);
	m_pMap[5][22]->SetIDInside(Tile::INSIDE_LVUP);
	m_pMap[9][21-5]->SetIDInside(Tile::INSIDE_COIN);

	////////////////////////////////////////////
	/*m_pMap[9][21]->SetVisible(false);
	m_pMap[9][23]->SetVisible(false);
	m_pMap[5][22]->SetVisible(false);*/
	m_pMap[9][21 - 5]->SetVisible(false);

	////////////////////////////////////////////

	m_Player = new Player(this);
	m_pBackGround = new BackGround();
	CreateEnemy();

}

TileMap::~TileMap()
{

	delete  m_Player;
	delete  m_pBackGround;
	/////////////////////////////////////////////////
	for (size_t i = 0; i < m_Mush.size(); i++)delete m_Mush[i]; m_Mush.clear();
	for (size_t i = 0; i < m_Flower.size(); i++)delete m_Flower[i]; m_Flower.clear();
	for (size_t i = 0; i < m_Star.size(); i++)delete m_Star[i]; m_Star.clear();
	for (size_t i = 0; i < m_BlockDebris.size(); i++) delete m_BlockDebris[i]; m_BlockDebris.clear();
	for (size_t i = 0; i < m_CoinJump.size(); i++) delete m_CoinJump[i]; m_CoinJump.clear();
	for (size_t i = 0; i < m_Enemy.size(); i++) delete m_Enemy[i]; m_Enemy.clear();
	for (size_t i = 0; i < m_FireBall.size(); i++) delete m_FireBall[i]; m_FireBall.clear();
	for (size_t i = 0; i < m_FireBallWork.size(); i++) delete m_FireBallWork[i]; m_FireBallWork.clear();
	////////////////////////////////////////////////////////////////////
	for (int i = 0; i < m_RowNum; i++)
	{
		for (int j = 0; j < m_ColNum; j++) {
			delete m_pMap[i][j];
		}
		delete m_pMap[i];
	}
	delete m_pMap;



}



