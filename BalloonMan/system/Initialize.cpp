#include "Initialize.h"
#include "DxLib.h"

const char TITLE[] = "BalloonMan(仮)";

const int WIN_WIDTH = 600; //ウィンドウ横幅
const int WIN_HEIGHT = 400;//ウィンドウ縦幅


int DXlibInit() {
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	//ウィンドウサイズを手動では変更できず、かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// タイトルを変更
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//画面サイズの最大サイズ、カラービット数を設定（モニターの解像度に合わせる）
	SetWindowSizeExtendRate(1.0);				//画面サイズを設定（解像度との比率で設定）
	SetBackgroundColor(0x00, 0x00, 0xFF);		// 画面の背景色を設定する

	//Dxライブラリソロの初期化
	if (DxLib_Init() == -1) { return -1; }

	//（ダブルバッファ）描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);
	return 0;
}

int DXlibfina() {
	ScreenFlip();//（ダブルバッファ）裏面
	// 20ミリ秒待機（疑似60FPS）
	WaitTimer(20);
	if (ProcessMessage() == -1)
	{
		return -1;
	}
	return 0;
}
