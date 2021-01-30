#include "DxLib.h"
#include "Initialize.h"
#include "GamePlay.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	if(DXlibInit() == -1) { return -1; }
	
	GamePlay *game = new GamePlay;
	delete game;
	
	//Dxƒ‰ƒCƒuƒ‰ƒŠI—¹ˆ—
	DxLib_End();

	return 0;
}