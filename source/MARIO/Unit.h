#pragma once
class TileMap;
class Unit
{
protected:
	TileMap * e_pTileMap;
	float m_x;
	float m_y;
	int m_CX;
	int m_CY;
	int m_CWidth;
	int m_CHeight;
public:
	int GetX() { return (int)m_x; }
	int GetY() { return (int)m_y; }
	int GetCX() { return m_CX; }
	int GetCY() { return m_CY; }
	int GetCWidth() { return m_CWidth; }
	int GetCHeight() { return m_CHeight; }
public:
	void SetX(int x) { m_x = (float)x; }
	void SetY(int y) { m_y = (float)y; }
	void SetCX(int CX) { m_CX = CX; }
	void SetCY(int CY) { m_CY = CY; }
	void SetCWidth(int CWidth) { m_CWidth = CWidth; }
	void SetCHeight(int CHeight) {m_CHeight = CHeight;}

public:
	void SetOtherToSelfLeft(Unit* other) {
		other->SetX((int)m_x + m_CX - other->GetCWidth() - other->GetCX());
	}
	void SetOtherToSelfRight(Unit* other) {
		other->SetX((int)m_x + m_CX + m_CWidth - other->GetCX());
	}
	void SetOtherToSelfUp(Unit* other) {
		other->SetY((int)m_y + m_CY - other->GetCHeight() - other->GetCY());
	}
	void SetOtherToSelfDown(Unit* other) {
		other->SetY((int)m_y + m_CY + m_CHeight - other->GetCY());
	}
public:
	bool bIntersect(const Unit* other);
	bool bIntersect(int x, int y, int width, int height);

public:
	Unit() {}
	~Unit() {}
};
