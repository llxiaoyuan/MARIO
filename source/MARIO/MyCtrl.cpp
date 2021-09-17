#include "MyCtrl.h"

void MyCtrl::Update()
{
	//W
	if (e_keys[SDL_SCANCODE_W]) {
		if (m_KeyState[MyCtrl::CMD_UP] == false) {
			m_KeyStateOnce[MyCtrl::CMD_UP] = true;
		}
		m_KeyState[MyCtrl::CMD_UP] = true;
	}
	else {
		m_KeyState[MyCtrl::CMD_UP] = false;
	}
	//S
	if (e_keys[SDL_SCANCODE_S]) {
		if (m_KeyState[MyCtrl::CMD_DOWN] == false) {
			m_KeyStateOnce[MyCtrl::CMD_DOWN] = true;
		}
		m_KeyState[MyCtrl::CMD_DOWN] = true;
	}
	else {
		m_KeyState[MyCtrl::CMD_DOWN] = false;
	}
	//A
	if (e_keys[SDL_SCANCODE_A]){
		if (m_KeyState[MyCtrl::CMD_LEFT] == false) {
			m_KeyStateOnce[MyCtrl::CMD_LEFT] = true;
		}
		m_KeyState[MyCtrl::CMD_LEFT] = true;
	}
	else{
		m_KeyState[MyCtrl::CMD_LEFT] = false;
	}
	//D
	if (e_keys[SDL_SCANCODE_D]) {
		if (m_KeyState[MyCtrl::CMD_RIGHT] == false) {
			m_KeyStateOnce[MyCtrl::CMD_RIGHT] = true;
		}
		m_KeyState[MyCtrl::CMD_RIGHT] = true;
	}
	else {
		m_KeyState[MyCtrl::CMD_RIGHT] = false;
	}
	//J
	if (e_keys[SDL_SCANCODE_J]) {
		if (m_KeyState[MyCtrl::CMD_J] == false) {
			m_KeyStateOnce[MyCtrl::CMD_J] = true;
		}
		m_KeyState[MyCtrl::CMD_J] = true;
	}
	else {
		m_KeyState[MyCtrl::CMD_J] = false;
	}
	//K
	if (e_keys[SDL_SCANCODE_K]) {
		if (m_KeyState[MyCtrl::CMD_K] == false) {
			m_KeyStateOnce[MyCtrl::CMD_K] = true;
		}
		m_KeyState[MyCtrl::CMD_K] = true;
	}
	else {
		m_KeyState[MyCtrl::CMD_K] = false;
	}
	//////////////////////
	if (e_keys[SDL_SCANCODE_LSHIFT]) {
		if (m_KeyState[MyCtrl::CMD_LSHIFT] == false) {
			m_KeyStateOnce[MyCtrl::CMD_LSHIFT] = true;
		}
		m_KeyState[MyCtrl::CMD_LSHIFT] = true;
	}
	else {
		m_KeyState[MyCtrl::CMD_LSHIFT] = false;
	}
	//////////////////////
	if (e_keys[SDL_SCANCODE_SPACE]) {
		if (m_KeyState[MyCtrl::CMD_SPACE] == false) {
			m_KeyStateOnce[MyCtrl::CMD_SPACE] = true;
		}
		m_KeyState[MyCtrl::CMD_SPACE] = true;
	}
	else {
		m_KeyState[MyCtrl::CMD_SPACE] = false;
	}
	//////////////////////
	if (e_keys[SDL_SCANCODE_ESCAPE]) {
		if (m_KeyState[MyCtrl::CMD_ESC] == false) {
			m_KeyStateOnce[MyCtrl::CMD_ESC] = true;
		}
		m_KeyState[MyCtrl::CMD_ESC] = true;
	}
	else {
		m_KeyState[MyCtrl::CMD_ESC] = false;
	}




}

MyCtrl::MyCtrl()
{
	for (int i = 0; i < CMD_NUM; i++) {
		m_KeyState[i] = false;
		m_KeyStateOnce[i] = false;
	}

	e_keys = SDL_GetKeyboardState(NULL);
}
MyCtrl::~MyCtrl()
{
}
