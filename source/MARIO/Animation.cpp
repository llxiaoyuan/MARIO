#include "Animation.h"

void Animation::SetFrames(MyImg ** pFrames, int iBegFrame, int iEndFrame, Uint32 dwDelay, int nCycle)
{
	e_pFrames   = pFrames;
	m_iBegFrame = iBegFrame;
	m_iEndFrame = iEndFrame;
	if (m_iCurFrame < m_iBegFrame || m_iCurFrame >= m_iEndFrame) {
		m_iCurFrame = m_iBegFrame;
	}
	m_dt = dwDelay;
	m_bAlready = false;
	m_nCycle = nCycle;
}

MyImg* Animation::GetCurImage()
{
	return e_pFrames[m_iCurFrame];
}

int Animation::GetCurFrame()
{
	return m_iCurFrame;
}

void Animation::Update()
{
	m_t2 = SDL_GetTicks();
	if (m_t2 - m_t1 >= m_dt) {
		m_t1 = m_t2;
		m_iCurFrame++;
		if (m_iCurFrame >= m_iEndFrame) {
			m_iCurFrame = m_iBegFrame;

			m_nCycle--;
			if (m_nCycle == 0) {
				m_bAlready = true;
			}
		}
	}
}

bool Animation::bAlready()
{
	return m_bAlready;
}


Animation::Animation()
{
	m_iCurFrame = 0;
	m_t1 = m_t2 = SDL_GetTicks();
}


Animation::~Animation()
{
}
