#include "WindowMain.h"
#include <fbxsdk.h>
#include <iostream>
int main()
{
	fbxsdk::FbxManager* fbx_manager = fbxsdk::FbxManager::Create();
	fbx_manager->Destroy();

	WindowMain& windowMain = WindowMain::getInstance();
	windowMain.initWindowMain();
	windowMain.executeEventLoop();
	return 0;
}