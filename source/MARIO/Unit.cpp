#include "Unit.h"

bool Unit::bIntersect(const Unit * other)
{
	return
	((((int)m_x + m_CX) + m_CWidth > ((int)other->m_x + other->m_CX)&&
	((int)m_x + m_CX) < ((int)other->m_x + other->m_CX) + other->m_CWidth)&&
	(((int)m_y + m_CY) + m_CHeight > ((int)other->m_y + other->m_CY)&&
	((int)m_y + m_CY) < ((int)other->m_y + other->m_CY) + other->m_CHeight));
}

bool Unit::bIntersect(int x, int y, int width, int height)
{
	return 
	((((int)m_x + m_CX) + m_CWidth > x &&
	(  (int)m_x + m_CX) < x + width) &&
	(( (int)m_y + m_CY) + m_CHeight > y &&
	(  (int)m_y + m_CY) < y + height));
}
