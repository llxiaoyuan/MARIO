#pragma once
#include<vector>
#include"Mush.h"
#include"Flower.h"
#include"Star.h"
#include"Tile.h"
#include"Config.h"
#include"Player.h"
#include"BlockDebris.h"
#include"CoinJump.h"
#include"EnemyMush.h"
#include"EnemyKoopa.h"
#include"FireBall.h"
#include"FireBallWork.h"
#include"BackGround.h"
class TileMap
{
public:
	static MyImg*    s_pImgGround;
	static MyImg*    s_pImgBrick;
	static MyImg*    s_pImgBox[3];
	static MyImg*    s_pImgBoxUsed;
	static void LoadRes(SDL_Renderer * pRender);
	static void FreeRes();
private:
	Animation m_AnimationBox;

public:
	///////////////////////////////
	BackGround* m_pBackGround;
	Player* m_Player;
	std::vector<Mush*> m_Mush;
	std::vector<Flower*> m_Flower;
	std::vector<Star*> m_Star;
	std::vector<BlockDebris*> m_BlockDebris;
	std::vector<CoinJump*> m_CoinJump;
	std::vector<Enemy*>    m_Enemy;
	std::vector<FireBall*> m_FireBall;
	std::vector<FireBallWork*> m_FireBallWork;
	///////////////////////////////
private:
	Tile*** m_pMap;
	int m_RowNum;
	int m_ColNum;
	int m_TileSize; // Config::TILE_SIZE   64
	////////////////////////////////////////////////
	int m_x;
	int m_y;
	int m_xMin;
	int m_yMin;
	int m_xMax;
	int m_yMax;
	////////////////////////////////////////////////
private:
	int m_iColOffsetBeg;
	int m_iRowOffsetBeg;
	int m_iColOffsetEnd;
	int m_iRowOffsetEnd;
public:
	void Render(SDL_Renderer* pRender);
	void Update(float dt);
public:
	void SetMapX(int x) {
		m_x = x;
		SetNumRange(&m_x, m_xMin, m_xMax);
	}
	void SetMapY(int y) {
		m_y = y;
		SetNumRange(&m_y, m_yMin, m_yMax);
	}

	int  GetTileSize();
	Tile*GetTile(int row, int col) { return m_pMap[row][col]; };

	int  GetMapX();
	int  GetMapY();
	int  GetRowNum();
	int  GetColNum();

	void CreateMush(int x, int y);
	void CreateFlower(int x, int y);
	void CreateStar(int x, int y);

	void CreateBlockDebris(int x, int y);
	void CreateCoinJump(int x, int y);
	void CreateEnemy();
	void CreateFireBall(int x,int y,bool bRight);
	void CreateFireBallWork(int x, int y);
private:
	void SetNumRange(int* pNum, int nMin, int nMax);
	void CalcOffset();
private:
	void InitMap(std::string sFileName);
public:
	TileMap(std::string sFileName);
	~TileMap();
};

