#pragma once
#include "Enemy.h"
class EnemyKoopa : public Enemy
{
	static const int WALK    = 0;
	static const int TRAMPLE = 1;
	static const int ANABIOSIS     = 2;
	static const int FRAMENUM_WALK    = 2;
	static const int FRAMENUM_TRAMPLE = 1;
	static const int FRAMENUM_ANABIOSIS     = 2;

public:
	static MyImg** s_pSpirits[3];
	static void LoadRes(SDL_Renderer * pRenderer);
	static void FreeRes();
	////////////////////////////////////////////////
	bool m_bTrample;
	bool m_bGliding;
	////////////////////////////////////////////////
	bool    m_bAnabiosis1;
	MyTimer m_tAnabiosis1;
	////////////////////////////////////////////////
	bool    m_bAnabiosis2;
	MyTimer m_tAnabiosis2;

public:
	void Update(float dt);
	void AnimationAction();
	///////////////////////////////////////////////////
	void HorCollisionWithEnemy();
	void VerCollisionWithEnemy();
	void CollisionWithPlayer();
	//////////////////////////////
	void HorCollisionWithMap();
	//////////////////////////////
	void SetTrample();
	void RelTrample();
	void SetKickLeft();
	void SetKickRight();

public:
	EnemyKoopa(TileMap * pTileMap, int x, int y, bool bRight);
	~EnemyKoopa();
};

