#pragma once
#include"Config.h"
#include"MyImg.h"
#include"Animation.h"
class TileMap;
class CoinJump
{
public:
	static MyImg* s_pImgCoinJump[4];
	static void LoadRes(SDL_Renderer * pRenderer);
	static void FreeRes();
private:
	TileMap* e_pTileMap;
	//////////////////////////////////
	int  m_JumpStartX;
	int  m_JumpStartY;
	///////////////////////////////////
	float m_x;
	float m_y;
	float m_dx;
	float m_dy;
	///////////////////////////////////
	bool  m_bUp;
	bool  m_bDown;
	bool  m_bJump;
	bool  m_bDelete;
	///////////////////////////////////
	Animation m_Animation;
public:
	void Update(float dt);
	void Render(SDL_Renderer* pRenderer);
public:
	bool bDelete();
public:
	CoinJump(TileMap* pTileMap,int x,int y);
	~CoinJump();
};

