#pragma once
#include"Animation.h"

class TileMap;
class FireBallWork
{
public:
	static MyImg* s_pImgFireBallWork[3];
	static void LoadRes(SDL_Renderer * pRenderer);
	static void FreeRes();
private:
	TileMap * e_pTileMap;

	int m_x;
	int m_y;
	Animation m_Animation;
	bool m_bDelete;

public:
	void Update(float dt);
	void Render(SDL_Renderer* pRender);


public:
	bool bDelete();
public:
	FireBallWork(TileMap* pTileMap , int x , int y);
	~FireBallWork();
};

