#include<stdio.h>
#include "Core.h"
#include"MyImg.h"
#include"BackGround.h"
#include"Mush.h"
#include"Flower.h"
#include"Star.h"
#include"BlockDebris.h"
#include"CoinJump.h"
#include"EnemyMush.h"
#include"EnemyKoopa.h"
#include"FireBall.h"
#include"FireBallWork.h"
#include"MyCtrl.h"
void MySleep(int ms)
{
	static Uint32 oldclock = SDL_GetTicks();		// 静态变量，记录上一次 tick

	oldclock += ms * 1000 / 1000;	// 更新 tick

	if (SDL_GetTicks() > oldclock)					// 如果已经超时，无需延时
		oldclock = SDL_GetTicks();
	else
		while (SDL_GetTicks() < oldclock)			// 延时
			SDL_Delay(1);						// 释放 CPU 控制权，降低 CPU 占用率
}

void Core::MainLoop()
{
	m_pTileMap = new TileMap("res/map/map.txt");
	m_pCtrl = new MyCtrl();

	Uint32 t1 = SDL_GetTicks();
	Uint32 t2 = SDL_GetTicks();
	Uint32 dt = 16;
	bool bRuning = true;
	while (bRuning) {
	
		while (SDL_PollEvent(m_pEvent)) {
			switch (m_pEvent->type)
			{
			case SDL_QUIT:
				bRuning = false;
				break;
			case SDL_WINDOWEVENT:
				switch (m_pEvent->window.event)
				{
				case SDL_WINDOWEVENT_CLOSE:
					bRuning = false;
					break;
				}
				break;
			default:
				break;
			}
		}
		t1 = SDL_GetTicks();

		SDL_RenderClear(m_pRender);
		SDL_SetRenderDrawColor(m_pRender, 0, 0, 0, 255);
		SDL_RenderFillRect(m_pRender, NULL);
		//绘制
		//////////////////////////////
		//////////////////////////////
		//////////////////////////////
		Input(m_pCtrl);
		Update(dt/1000.0f);
		Render(m_pRender);
		//////////////////////////////
		//////////////////////////////
		//////////////////////////////
		SDL_RenderPresent(m_pRender);

		t2 = SDL_GetTicks();
		dt = t2 - t1;
		//MySleep(16);
	}

	delete m_pTileMap;
	delete m_pCtrl;
}


/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////

void Core::Input(MyCtrl * pCtrl)
{
	pCtrl->Update();

	if (pCtrl->m_KeyState[MyCtrl::CMD_UP] || pCtrl->m_KeyState[MyCtrl::CMD_SPACE] || pCtrl->m_KeyState[MyCtrl::CMD_K]) m_pTileMap->m_Player->SetJump(true);
	else m_pTileMap->m_Player->SetJump(false);

	if (pCtrl->m_KeyState[MyCtrl::CMD_DOWN])m_pTileMap->m_Player->SetDown(true);
	else m_pTileMap->m_Player->SetDown(false);

	if (pCtrl->m_KeyState[MyCtrl::CMD_LEFT])m_pTileMap->m_Player->SetLeft(true);
	else m_pTileMap->m_Player->SetLeft(false);

	if (pCtrl->m_KeyState[MyCtrl::CMD_RIGHT])m_pTileMap->m_Player->SetRight(true);
	else m_pTileMap->m_Player->SetRight(false);
	///////////////////////////////////////////////////////////
	if (pCtrl->m_KeyStateOnce[MyCtrl::CMD_J]) {
		m_pTileMap->m_Player->SetFire(true);
		pCtrl->m_KeyStateOnce[MyCtrl::CMD_J] = false;
	}
	else {
		m_pTileMap->m_Player->SetFire(false);
	}
}

void Core::Update(float   dt)
{
	m_pTileMap->Update(dt);
}

void Core::Render(SDL_Renderer* pRenderer)
{
	m_pTileMap->Render(pRenderer);
}
/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////
void Core::LoadRes()
{
	Player::LoadRes(m_pRender);
	TileMap::LoadRes(m_pRender);
	Mush::LoadRes(m_pRender);
	Flower::LoadRes(m_pRender);
	Star::LoadRes(m_pRender);
	BlockDebris::LoadRes(m_pRender);
	CoinJump::LoadRes(m_pRender);
	EnemyMush::LoadRes(m_pRender);
	EnemyKoopa::LoadRes(m_pRender);
	FireBall::LoadRes(m_pRender);
	FireBallWork::LoadRes(m_pRender);
	BackGround::LoadRes(m_pRender);
}

void Core::FreeRes()
{
	Player::FreeRes();
	TileMap::FreeRes();
	Mush::FreeRes();
	Flower::FreeRes();
	Star::FreeRes();
	BlockDebris::FreeRes();
	CoinJump::FreeRes();
	EnemyMush::FreeRes();
	EnemyKoopa::FreeRes();
	FireBall::FreeRes();
	FireBallWork::FreeRes();
	BackGround::FreeRes();
}

Core::Core()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);

	m_pWindow = SDL_CreateWindow("SuperMarioBro--Li", 
		30, 30,
		Config::W_SCREEN, Config::H_SCREEN, SDL_WINDOW_SHOWN);
	if (m_pWindow == nullptr) {
		printf("m_pWindow == nullptr\n");
	}
	m_pRender= SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	// ----- ICO
	SDL_Surface* icoSurface = SDL_LoadBMP("res/images/ico.bmp");
	SDL_SetColorKey(icoSurface, SDL_TRUE, SDL_MapRGB(icoSurface->format, 255, 0, 255));
	SDL_SetWindowIcon(m_pWindow, icoSurface);
	SDL_FreeSurface(icoSurface);
	//
	m_pEvent = new SDL_Event();


	LoadRes();
	
}


Core::~Core()
{
	FreeRes();

	delete m_pEvent;
	SDL_DestroyRenderer(m_pRender);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}
