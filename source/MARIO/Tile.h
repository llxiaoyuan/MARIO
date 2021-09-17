#pragma once
#include<string>
#include<fstream>
#include<iostream>
#include<SDL.h>
#include"Config.h"
#include"MyImg.h"
#include"Unit.h"
class TileMap;
class Tile : public Unit
{

public:
	static const int TILES_NULL		= 0;
	static const int TILES_GROUND	= 1;
	static const int TILES_BRICK	= 2;
	static const int TILES_BOX		= 3;
	static const int TILES_BOXUSED	= 4;
public:
	static const int INSIDE_NULL	= 0;
	static const int INSIDE_COIN	= 1;
	static const int INSIDE_LVUP	= 2;
	static const int INSIDE_STAR	= 3;
public:
	static const int BOUNCE_HEIGHT = 16;
	static const int BOUNCE_SPEED = 100;
private:
	TileMap* e_pTileMap;
	int  m_ID;
	int  m_IDInside;
	int  m_BounceStartX;
	int  m_BounceStartY;
	bool m_bBounce;
	bool m_bBounceUp;
	bool m_bBounceDown;
	bool m_bVisible;
public:
	void SetID(int ID) { m_ID = ID; }
	void SetIDInside(int IDInside) { m_IDInside = IDInside; }
	//////////////////////////////////////////
	int  GetID() { return m_ID; }
	int  GetIDInside() { return m_IDInside; }
	//////////////////////////////////////////
	void SetStrike();
	//////////////////////////////////////////
	void Update(float dt);
	//////////////////////////////////////////
	void SetVisible(bool bVisible) { m_bVisible = bVisible; }
	bool bVisible() { return m_bVisible; }
public:
	Tile(TileMap* pTileMap,int x, int y, int ID);
	~Tile();
};

