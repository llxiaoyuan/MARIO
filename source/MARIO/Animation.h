#pragma once
#include"MyImg.h"
class Animation
{
public:
	MyImg** e_pFrames;  
	Uint32  m_iBegFrame;
	Uint32  m_iEndFrame;
	Uint32  m_iCurFrame;
	Uint32  m_t1;
	Uint32  m_t2;
	Uint32  m_dt;
	bool    m_bAlready;
	Uint32  m_nCycle;
public:
	void	SetFrames(MyImg** pFrames, int iBegFrame, int iEndFrame, Uint32 dt,int nCycle = 1);

	MyImg*  GetCurImage();
	int     GetCurFrame();
	void	Update();

	bool	bAlready();
public:
	Animation();
	~Animation();
};

