#include"Core.h"



int main(int argc, char* argv[])
{
	Core* pCore = new Core();
	pCore->MainLoop();
	delete pCore;
	return 0;
}