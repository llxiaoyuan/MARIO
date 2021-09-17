#ifndef __MYCONTROL_H__
#define __MYCONTROL_H__
#include<SDL.h>
class MyCtrl
{
	static const int CMD_NUM = 9;
public:
	static const int CMD_UP			= 0;
	static const int CMD_DOWN		= 1;
	static const int CMD_LEFT		= 2;
	static const int CMD_RIGHT		= 3;

	static const int CMD_J			= 4;
	static const int CMD_K			= 5;
	static const int CMD_LSHIFT		= 6;
	static const int CMD_SPACE		= 7; 
	static const int CMD_ESC		= 8;

public:
	bool m_KeyState[CMD_NUM];
	bool m_KeyStateOnce[CMD_NUM];//相应之后要 ctl.m_KeyStateOnce[id]=false;
private:
	const Uint8* e_keys;
public:
	void Update();
public:
	MyCtrl();
	~MyCtrl();
};

#endif // !__MYCONTROL_H__