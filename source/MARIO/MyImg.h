#pragma once
#include<SDL.h>
#include<string>
class MyImg
{
private:
	SDL_Texture* m_pImg;
	SDL_Rect     m_Rect;
public:
	void Render(SDL_Renderer* pRender, int x, int y);
	void RenderHOR(SDL_Renderer* pRender, int x, int y);
	void RenderVER(SDL_Renderer* pRender, int x, int y);
	void RenderHORVER(SDL_Renderer* pRender, int x, int y);
public:
	SDL_Texture* GetImg();
	SDL_Rect GetRect();
	int GetWidth() {
		return m_Rect.w;
	}
	int GetHeight() {
		return m_Rect.h;
	}
private:
	void SetImg(std::string strFileName, SDL_Renderer* pRender);
public:
	MyImg(std::string strFileName, SDL_Renderer* pRender);
	~MyImg();
};

