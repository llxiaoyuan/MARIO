#pragma once
#include "Enemy.h"
#include"MyTimer.h"
class EnemyMush : public Enemy
{
	static const int WALK    = 0;
	static const int TRAMPLE = 1;
	static const int FRAMENUM_WALK = 2;
	static const int FRAMENUM_TRAMPLE = 1;
public:
	static MyImg** s_pSpirits[2];
	static void LoadRes(SDL_Renderer * pRenderer);
	static void FreeRes();
public:
	void Update(float dt);
	void AnimationAction();

	void HorCollisionWithEnemy();
	void VerCollisionWithEnemy();
	void CollisionWithPlayer();
private:
	bool    m_bTrample;

	MyTimer m_tDelete;

	void SetTrample();
public:
	EnemyMush(TileMap* pTileMap, int x, int y, bool bRight);
	~EnemyMush();
};

