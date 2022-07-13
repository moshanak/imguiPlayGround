#include "WindowMain.h"
#include <iostream>

int main()
{
	WindowMain& windowMain = WindowMain::getInstance();
	windowMain.initWindowMain();
	windowMain.executeEventLoop();
	return 0;
}