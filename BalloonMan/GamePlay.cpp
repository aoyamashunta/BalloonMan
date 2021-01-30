#include "GamePlay.h"
#include "DxLib.h"
#include "Initialize.h"
#include "Input.h"
#include "BackGround.h"
//#include "SceneTrans.h"

enum gameplay {
	START,
	TUTORIAL,
	MAINMENU,
	PLAY
};


GamePlay::GamePlay() :
	gameEnd(false),
	stageFlag(0),
	sceneFlag(START),
	stageEnd(),
	pauseSwitch(false) {
	Game();
}

void GamePlay::Game() {

	while(1) {
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//
		//入力処理
		Input::Update();
		if(sceneFlag == START) {
			if(Input::isKeyTrigger(KEY_INPUT_SPACE)) {
				sceneFlag = MAINMENU;
			}
		}
		else if(sceneFlag == TUTORIAL) {

		}
		else if(sceneFlag == MAINMENU) {
			if(Input::isKeyTrigger(KEY_INPUT_1)) {
				stageFlag = 1;
			}
		}
		else if(sceneFlag == PLAY) {

		}

		//更新・描画処理
		if(sceneFlag == START) {
			Start();
		}
		else if(sceneFlag == MAINMENU) {
			MainMenu();
		}
		else if(sceneFlag == PLAY) {
			Play();
		}


		//描画処理
		//SceneTrans::TransDraw();
		//if(SceneTrans::ReturnError()) { gameEnd = true; }

		//debug
		DrawFormatString(0, 0, GetColor(255, 255, 255), "sceneFlag : %d", sceneFlag);
		//DrawFormatString(0, 15, GetColor(255, 255, 255), "player.Y : %d",player->RplayerY());

		//---------  ここまでにプログラムを記述  ---------//
		if(gameEnd == true) { break; }
		if(DXlibfina() == -1) { break; }
	}
}

void GamePlay::Load() {
	DrawBox(0, 0, 960, 480, GetColor(0, 0, 0), 1);
	DrawFormatString(0, 0, GetColor(255, 255, 255),
					 "Now Loading...");
}

void GamePlay::Start() {
	static int flame = 255;
	static int add = -7;
	flame += add;
	if(flame <= 0 || flame >= 255) {
		add = -add;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, flame);
	DrawFormatString(480, 280, GetColor(255, 255, 255),
					 "--- PRESS SPACE KEY TO START ---");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GamePlay::MainMenu() {
	const char *stageName = nullptr;
	switch(stageFlag) {
		case 1:
			stageName = { "Resource\\stage.csv" };
	}
	if(stageFlag != 0) {
		if(!LoadPlay(stageName)) {
			Load();
		}
	}
}

bool GamePlay::LoadPlay(const char *mapName) {
	stage = new BackGround(mapName);
	if(stage->LoadFail()) { return false; }

	stage->LoadPlayerIni();
	player = new Player(stage->ReturnXIni(),
						stage->ReturnYIni());

	sceneFlag = PLAY;
	return true;
}

bool GamePlay::Play() {
	if(stageFlag == 1) {
		//debug 背景
		for(int i = 0; i < 480; i++) {
			DrawBox(0, i, 960, i + 1,
					GetColor(105 + 114 * i / 480, 179 + 57 * i / 480, 255), 1);
		}
		if(!player->ReturnClear() && !pauseSwitch && player->ReturnAlive()) {
			player->Update(*stage);
			if(Input::isKeyTrigger(KEY_INPUT_ESCAPE)) {
				pauseSwitch = true;
			}

			//debug
			DrawFormatString(0, 15, GetColor(255, 255, 255),
							 "player.Y : %lf", player->RplayerY());
		}
		else if(player->ReturnClear()) {
			Clear();
		}
		else if(!player->ReturnAlive()) {
			GameOver();
		}
		else if(pauseSwitch) {
			Pause();
		}
		stage->MapChip();
		player->Draw();
		SetDrawBright(255, 255, 255);
	}
	return true;
}

void GamePlay::Clear() {
	if(CheckHitKeyAll()) {
		delete stage;
		delete player;
		stageFlag = MAINMENU;
	}

	//debug
	DrawFormatString(200, 200, GetColor(255, 255, 255),
					 "gameclear");
	DrawFormatString(90, 215, GetColor(255, 255, 255),
					 "いずれかのキーを押してください");
}

void GamePlay::GameOver() {
	DrawFormatString(200, 200,
					 GetColor(255, 255, 255),
					 "GameOver");
	SetDrawBright(200, 200, 200);
}

void GamePlay::Pause() {
	DrawFormatString(200, 200,
					 GetColor(255, 255, 255),
					 "pause");
	SetDrawBright(200, 200, 200);
	if(Input::isKeyTrigger(KEY_INPUT_ESCAPE)) {
		sceneFlag = MAINMENU;
	}
	if(Input::isKeyTrigger(KEY_INPUT_SPACE)) {
		pauseSwitch = false;
	}
}
