#include "GamePlay.h"
#include "DxLib.h"
#include "system/Initialize.h"

void GamePlay::game() {
	while (1)
	{
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//
		//更新処理
		if(CheckHitKey(KEY_INPUT_A))
		{
			break;
		}



		//描画処理
		DrawCircle(200,300,16,GetColor(255,255,255));



		//---------  ここまでにプログラムを記述  ---------//
		if(DXlibfina() == -1) { break; }
	}
	
}
