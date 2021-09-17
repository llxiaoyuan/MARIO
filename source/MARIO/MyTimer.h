#pragma once
#include<SDL.h>
class MyTimer
{
	Uint32 m_t1;
	Uint32 m_t2;
	Uint32 m_dt;
public:
	void Init(Uint32 dt){
		m_t1 = m_t2 = SDL_GetTicks();
		m_dt = dt;
	}
	bool Update() {
		m_t2 = SDL_GetTicks();
		return m_t2 - m_t1 >= m_dt;
	}
public:
	MyTimer() { m_t1 = m_t2 = 0; m_dt = 0; }
	~MyTimer(){}
};

