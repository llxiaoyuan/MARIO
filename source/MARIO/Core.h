#pragma once
#include<SDL.h>
#include"Config.h"
#include"TileMap.h"
#include"MyCtrl.h"
class Core
{
private:
	SDL_Window*		m_pWindow;
	SDL_Renderer*	m_pRender;
	SDL_Event*		m_pEvent;
	/////////////////////////
	//сно╥
	TileMap* m_pTileMap;
	MyCtrl*  m_pCtrl;
public:
	
	void MainLoop();

	
	void Input(MyCtrl* pCtrl);
	void Update(float   dt);
	void Render(SDL_Renderer* pRenderer);
public:

	void LoadRes();
	void FreeRes();
public:
	Core();
	~Core();
};

