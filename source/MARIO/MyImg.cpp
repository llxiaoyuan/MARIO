#include "MyImg.h"

void MyImg::Render(SDL_Renderer * pRender, int x, int y)
{
	m_Rect.x = x;
	m_Rect.y = y;
	SDL_RenderCopy(pRender, m_pImg, NULL, &m_Rect);
}

void MyImg::RenderHOR(SDL_Renderer * pRender, int x, int y)
{
	m_Rect.x = x;
	m_Rect.y = y;
	SDL_RenderCopyEx(pRender, m_pImg, NULL, &m_Rect, 180.0, NULL, SDL_FLIP_VERTICAL);
}

void MyImg::RenderVER(SDL_Renderer * pRender, int x, int y)
{
	m_Rect.x = x;
	m_Rect.y = y;
	SDL_RenderCopyEx(pRender, m_pImg, NULL, &m_Rect, 180.0, NULL, SDL_FLIP_HORIZONTAL);
}

void MyImg::RenderHORVER(SDL_Renderer * pRender, int x, int y)
{
	m_Rect.x = x;
	m_Rect.y = y;
	SDL_RenderCopyEx(pRender, m_pImg, NULL, &m_Rect, 180.0, NULL, SDL_FLIP_NONE);
}

void MyImg::SetImg(std::string strFileName, SDL_Renderer* pRender)
{
	SDL_Surface* loadedSurface = SDL_LoadBMP(strFileName.c_str());
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 255));

	m_pImg = SDL_CreateTextureFromSurface(pRender, loadedSurface);
	//获取纹理宽高
	int nWidth, nHeight;
	SDL_QueryTexture(m_pImg, NULL, NULL, &nWidth, &nHeight);
	m_Rect.x = 0;
	m_Rect.y = 0;
	m_Rect.w = nWidth;
	m_Rect.h = nHeight;
	SDL_FreeSurface(loadedSurface);
}

SDL_Texture * MyImg::GetImg()
{
	return m_pImg;
}

SDL_Rect MyImg::GetRect()
{
	return m_Rect;
}

MyImg::MyImg(std::string strFileName, SDL_Renderer * pRender)
{
	SetImg(strFileName, pRender);
}

MyImg::~MyImg()
{
	SDL_DestroyTexture(m_pImg);
}
