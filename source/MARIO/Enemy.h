#pragma once
#include "MyImg.h"

#include"MapObject.h"
#include"Player.h"
class Enemy : public MapObject
{
protected:
	bool m_bActive;
	bool m_bCollisionWithEnemy;
	bool m_bCollisionWithFireBall;
	bool m_bCollisionWithPlayer;

	bool m_bDead;	   //±»»ðÇò »ò±» ¹ê¿Ç
	/////////////////////////////////////////
public:
	virtual void Update(float dt) = 0;
	void Render(SDL_Renderer * pRenderer);
	virtual void HorCollisionWithEnemy() = 0;
	virtual void VerCollisionWithEnemy() = 0;
	virtual void CollisionWithPlayer() = 0;
	virtual void CollisionWithFireBall();
public:
	void Kill() {
		m_bCollisionWithEnemy    = false;
		m_bCollisionWithFireBall = false;
		m_bCollisionWithPlayer   = false;
		m_bDead = true; 
	}
	bool bCollisionWithEnemy() { return m_bCollisionWithEnemy; }
	bool bCollisionWithFireBall() { return m_bCollisionWithFireBall; }
	bool bCollisionWithPlayer() { return m_bCollisionWithPlayer; }

	bool bOnScreen();
public:
	Enemy(){}
	~Enemy(){}
};

