#pragma once

#include "MapObject.h"
#include "MyImg.h"
#include "Player.h"
class Mush : public MapObject
{
public:
	static MyImg* s_pSpirits[1];
	static void LoadRes(SDL_Renderer * pRenderer);
	static void FreeRes();
private:
	///////////////////////////
	int    m_SpawnStartX;
	int    m_SpawnStartY;
	bool   m_bSpawn;
public:
	void Update(float dt);
	void CollisionWithPlayer();

public:
	Mush(TileMap* pTileMap, int x, int y);
	~Mush();
};

