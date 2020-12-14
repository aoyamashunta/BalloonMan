#include "GamePlay.h"
#include "DxLib.h"
#include "system/Initialize.h"
#include "Input.h"
#include "Player.h"

void GamePlay::game() {
	//変数の宣言
	int stageFlag = 0;
	
	int graph = LoadGraph("player.png");
	Player *player1 = new Player(200,300,graph); 
	
	while(1) {
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//
		//入力処理
		Input::Update();
		if(Input::isKeyTrigger(KEY_INPUT_1)) {
			stageFlag = 1;
		}

		if(Input::isKeyTrigger(KEY_INPUT_2)) {
			stageFlag = 2;
		}

		if(Input::isKeyTrigger(KEY_INPUT_3)) {
			stageFlag = 3;
		}

		if(Input::isKeyTrigger(KEY_INPUT_4)) {
			stageFlag = 4;
		}

		if(Input::isKeyTrigger(KEY_INPUT_Q)) {
			break;
		}

		//更新処理
		if(stageFlag == 1) {
			player1->Update();
			player1->Draw();
		}



		//描画処理
		DrawFormatString(0, 0, GetColor(255, 255, 255), "stageFlag : %d",stageFlag);
		DrawFormatString(0, 15, GetColor(255, 255, 255), "player.flame : %d",player1->airRemain);

		//---------  ここまでにプログラムを記述  ---------//
		if(DXlibfina() == -1) { break; }
	}
	delete player1;
}
