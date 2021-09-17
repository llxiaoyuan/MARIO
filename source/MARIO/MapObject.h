#pragma once
#include "Animation.h"
#include "Config.h"
#include "MyImg.h"
#include "Unit.h"
class TileMap;
class MapObject : public Unit
{
protected:
	float m_dx;
	float m_dy;
	int m_iColOffsetBeg;
	int m_iRowOffsetBeg;
	int m_iColOffsetEnd;
	int m_iRowOffsetEnd;
	//控制
	bool m_bLeft;
	bool m_bRight;
	bool m_bUp;
	bool m_bDown;
	bool m_bJump;
	//移动属性
	float m_MoveSpeed;			//加速度
	float m_MoveSpeedMax;		//最大移动速度
	float m_MoveStopSpeed;		
	/////////////////////////
	bool  m_bTouch;        
	float m_JumpHeightMin;
	float m_JumpHeightMax;
	float m_TimeToJumpApex;
	float m_Gravity;
	float m_JumpVelocityMin;
	float m_JumpVelocityMax;
	/////////////////////////
	bool  m_bDelete;    //是否删除
	/////////////////////////
	Animation m_Animation;
	int  CurState;
	int  PreState;
	bool m_bFacingRight;
	////////////////////////
public:
	bool bDelete() { return m_bDelete; }
protected:
	void SetNumRange(int* pNum, int nMin, int nMax);
public:
	void Action();
	void AnimationAction();
	void Render(SDL_Renderer * pRenderer);
	void CalcMapOffset();
	void HorCollisionWithMap();
	void VerCollisionWithMap();
	void OntheGroundTest();
public:
	void SetDx(float dx) { m_dx = dx; }
	void SetDy(float dy) { m_dy = dy; }
public:
	float GetDx() { return  m_dx; }
	float GetDy() { return  m_dy; }
public:
	void SetLeft(bool b)  { m_bLeft = b; }
	void SetRight(bool b) { m_bRight = b; }
	void SetUp(bool b)    { m_bUp = b; }
	void SetDown(bool b)  { m_bDown = b; }
	void SetJump(bool b)  { m_bJump = b; }
	void SetTurn() {
		if (m_bLeft) { m_bRight = true; m_bLeft = false; }
		else if (m_bRight) { m_bRight = false; m_bLeft = true; }
	}
public:
	MapObject() {}
	~MapObject() {}
};

