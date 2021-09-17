#pragma once
#include "MapObject.h"
#include "MyImg.h"
#include "MyTimer.h"
class Player : public MapObject
{
public:
	static const int IDLE  = 0;
	static const int JUMP  = 1;
	static const int WALK  = 2;
	static const int STOP  = 3;
	static const int SQUAT = 4;
	static const int FIRE  = 5;

	static const int FRAMENUM_IDLE = 1;
	static const int FRAMENUM_JUMP = 1;
	static const int FRAMENUM_WALK = 3;
	static const int FRAMENUM_STOP = 1;
	static const int FRAMENUM_SQUAT = 1;
	static const int FRAMENUM_FIRE = 1;

	static const int FRAMENUM_IDLE_STAR  = 3;
	static const int FRAMENUM_JUMP_STAR  = 3;
	static const int FRAMENUM_WALK_STAR  = 3;
	static const int FRAMENUM_STOP_STAR  = 3;
	static const int FRAMENUM_SQUAT_STAR = 3;
	static const int FRAMENUM_FIRE_STAR  = 3;

	static MyImg** s_pSpiritsLV1[4];
	static MyImg** s_pSpiritsLV1Star[4];

	static MyImg** s_pSpiritsLV2[5];
	static MyImg** s_pSpiritsLV2Star[5];

	static MyImg** s_pSpiritsLV3[6];
	static MyImg** s_pSpiritsLV3Star[6];

	static const int POWERUP_1 = 0;
	static const int POWERUP_2_IDLE   = 0;
	static const int POWERUP_2_JUMP   = 1;
	static const int POWERUP_2_WALK_0 = 2;
	static const int POWERUP_2_WALK_1 = 3;
	static const int POWERUP_2_WALK_2 = 4;
	static const int POWERUP_2_STOP   = 5;
	static const int POWERUP_2_SQUAT  = 6;

	static const int FRAMENUM_POWERUP = 3;
	static MyImg** s_pSpiritsPowerUp1[1];//³ÔÄ¢¹½
	static MyImg** s_pSpiritsPowerUp2[7];//³Ô»¨

	static void LoadRes(SDL_Renderer * pRender);
	static void FreeRes();
private:
	bool    m_bStaring;
	MyTimer m_tStaring;
	////////////////////////
	//³ÔÄ¢¹½ ³Ô»¨ µÄ¶¯»­
	bool    m_bPowerUping;
	MyTimer m_tPowerUping;
	bool    m_bPowerUpAni;
	////////////////////////
	//×Óµ¯·¢Éä ¶¯»­
	bool    m_bFireing;
	MyTimer m_tFireing;
	////////////////////////
	bool    m_bCanFire;
	MyTimer m_tCanFire;
	bool    m_bFire;//key 
	/////////////////////
	int m_LV;
public:
	void Update(float dt);
	void Action();
	void AnimationAction();

	int  GetLV() {
		return m_LV;
	}
	void PowerUp() {
		if (m_LV == 1) {
			m_CY = 0;
			m_CHeight = 64 * 2;
			m_LV = 2;
		}
		else if (m_LV == 2){
			m_LV = 3;
		}
		m_bPowerUping = true;
		m_bPowerUpAni = true;
		m_tPowerUping.Init(1000);
	}
	void EatStar() {
		m_bStaring = true;
		m_tStaring.Init(5000);
	}

	bool bStaring() { return m_bStaring; }
	bool bPowerUping() { return m_bPowerUping; }
	bool bFireing() { return m_bFireing; }

	void SetFire(bool bFire) { m_bFire = bFire; }

	void Bounce() {
		m_bTouch = true;
		m_bJump = true;
	}

private:
	void HorCollisionWithMap();//¸²¸Ç
	void VerCollisionWithMap();//¸²¸Ç
public:
	Player(TileMap* pTileMap);
	~Player();
};

