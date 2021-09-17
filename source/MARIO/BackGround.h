#pragma once
#include"MyImg.h"
class BackGround
{
public:
	static MyImg* m_pBackGround;
	static void LoadRes(SDL_Renderer * pRenderer);
	static void FreeRes();
	
private:
	int    m_x;
	int    m_y;
public:
	int  GetX() {
		return m_x;
	}
	int  GetY() {
		return m_y;
	}
	int  GetWidth() {
		return m_pBackGround->GetWidth();
	}
	int  GetHeight() {
		return m_pBackGround->GetHeight();
	}
	void SetX(int x) { m_x = x % (m_pBackGround->GetWidth() + 1); }
	void SetY(int y) { m_y = y; }
	void Render(SDL_Renderer* pRender);
public:
	BackGround();
	~BackGround();
};

