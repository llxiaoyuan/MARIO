#pragma once
#include"Config.h"
#include"MyImg.h"
class TileMap;
class BlockDebris
{
public:
	static MyImg* s_pImgBlockDebris;
	static void LoadRes(SDL_Renderer * pRenderer);
	static void FreeRes();
	///////////////////////////////////////////
private:
	TileMap* e_pTileMap;
	///////////////////////////
	struct MyPoint {float x;float y;};
	MyPoint TL;
	MyPoint TR;
	MyPoint BL;
	MyPoint BR;
	float m_dx;
	float m_dy;

	bool m_bDelete;
public:
	void Update(float dt);
	void Render(SDL_Renderer * pRenderer);
public:
	bool bDelete();
public:
	BlockDebris(TileMap* pTileMap, int x, int y);
	~BlockDebris();
};

