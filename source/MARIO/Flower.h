#pragma once
#include "MapObject.h"
#include "MyImg.h"
#include "Player.h"
//					  ¿À∑—∞°
class Flower : public MapObject
{
public:
	static MyImg* s_pSpirits[4];
	static void LoadRes(SDL_Renderer * pRenderer);
	static void FreeRes();
private:
	int    m_SpawnStartX;
	int    m_SpawnStartY;
	bool   m_bSpawn;
public:
	void Update(float dt);
	void CollisionWithPlayer();

public:
	Flower(TileMap * pTileMap, int x, int y);
	~Flower();
};

