#pragma once
#include "MapObject.h"
#include "Enemy.h"
class FireBall : public MapObject
{
public:
	static MyImg* s_pSpirits[4];
	static void LoadRes(SDL_Renderer * pRenderer);
	static void FreeRes();
public:
	void Update(float dt);
	void HorCollisionWithMap();

	void Remove();
public:
	FireBall(TileMap* pTileMap, int x, int y , bool bRight);
	~FireBall();
};

