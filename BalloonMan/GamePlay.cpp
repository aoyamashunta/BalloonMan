#include "GamePlay.h"
#include "DxLib.h"
#include "system/Initialize.h"
#include "Input.h"
#include "BackGround.h"
#include "SceneTrans.h"

enum gameplay {
	START,
	MAINMENU,
	PLAY
};


void GamePlay::Game() {
	gameEnd = false;
	
	while(1) {
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//
		//入力処理
		Input::Update();
		if(sceneFlag == START) {

		}
		else if(sceneFlag == MAINMENU) {

		}
		else if(sceneFlag == PLAY) {
			if(Input::isKeyTrigger(KEY_INPUT_1)) {
				stageFlag = 1;
				const char *stageName = { "stage.csv" };
				PlayIni(stageName);
			}
		}

		//更新・描画処理
		if(sceneFlag == START) {

		}
		else if(sceneFlag == MAINMENU) {

		}
		else if(sceneFlag == PLAY) {
			Play();
		}


		//描画処理
		SceneTrans::TransDraw();
		if(SceneTrans::ReturnError()){ gameEnd = true; }
		
		//debug
		//DrawFormatString(0, 0, GetColor(255, 255, 255), "stageFlag : %d",stageFlag);
		//DrawFormatString(0, 15, GetColor(255, 255, 255), "player.Y : %d",player->RplayerY());

		//---------  ここまでにプログラムを記述  ---------//
		if(gameEnd == true) { break; }
		if(DXlibfina() == -1) { break; }
	}
}

bool GamePlay::PlayIni(const char *mapName) {
	stage = new BackGround(mapName);
	if(stage->LoadFail()) { return false; }

	stage->LoadPlayerIni();
	player = new Player(stage->ReturnXIni(),
						stage->ReturnYIni());
	return true;
}

bool GamePlay::Play() {
	bool flag = false;
	if(stageFlag == 1) {
		if(!player->ReturnClear()) {
			player->Update(*stage);
			DrawFormatString(0, 15, GetColor(255, 255, 255),
							 "player.Y : %lf", player->RplayerY());
		}
		else if(player->ReturnClear()) {
			//debug
			DrawFormatString(200, 200, GetColor(255, 255, 255),
							 "gameclear");
			DrawFormatString(90, 215, GetColor(255, 255, 255),
							 "いずれかのキーを押してください");

			if(CheckHitKeyAll()) {
				flag = true;
				//delete stage;
				//delete player;
				//stageFlag = 0;
			}
			if(flag)
			{
				if(SceneTrans::TransC())
				{
					delete stage;
					delete player;
					stageFlag = 0;
					flag = false;
				}
			}
		}
		stage->MapChip();
		player->Draw();
	}
	return true;
}
