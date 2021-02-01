#include "GamePlay.h"
#include "DxLib.h"
#include "Initialize.h"
#include "Input.h"
#include "BackGround.h"
//#include "SceneTrans.h"

/// <summary>
/// sceneFlag用
/// </summary>
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
	pauseSwitch(false),
	mainMenu_Pointer(1),
	mainMenu_SceneNum(0),
	tutorial_Num(0),
	gameClear_Flag{} {
	sound = new Sound();
	
	titleGraph = LoadGraph("Resource\\graph\\BallonManTitle.png");

	fontHandle_CountDown = CreateFontToHandle(NULL, 100, -1);
	fontHandle_Loading = CreateFontToHandle(NULL, 20, -1);

	gameClear_ColorY = GetColor(255, 200, 0);
	gameClear_ColorN = GetColor(204, 204, 204);
	Game();
}

void GamePlay::Game() {

	while(1) {
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//
		//入力処理
		Input::Update();
		if(sceneFlag == START) {
			sound->TitleBGM();
			if(Input::isKeyTrigger(KEY_INPUT_SPACE)) {
				gameTrans = true;
			}
			if(Input::isKeyTrigger(KEY_INPUT_Q)) {
				gameTrans = true;
				debugOption = true;
			}
		}
		else if(sceneFlag == TUTORIAL) {
			Tutorial_Update();
		}
		else if(sceneFlag == MAINMENU) {
			MainMenu_Update();
		}
		else if(sceneFlag == PLAY) {

		}

		//更新・描画処理
		if(sceneFlag == START) {
			Start_Draw();
		}
		else if(sceneFlag == TUTORIAL) {
			Tutorial_Draw();
		}
		else if(sceneFlag == MAINMENU) {
			MainMenu_Draw();
		}
		else if(sceneFlag == PLAY) {
			Play_Update();
		}


		//描画処理
		//SceneTrans::TransDraw();
		//if(SceneTrans::ReturnError()) { gameEnd = true; }

		//debug
		//DrawFormatString(0, 0, GetColor(255, 255, 255), "sceneFlag : %d", sceneFlag);
		//DrawFormatString(0, 15, GetColor(255, 255, 255), "player.Y : %d",player->RplayerY());

		//---------  ここまでにプログラムを記述  ---------//
		if(gameEnd == true) { break; }
		if(DXlibfina() == -1) { break; }
	}
}

bool GamePlay::Load_Now() {
	static int flame = 0;
	flame++;
	if(flame <= 2 * 60) {
		DrawBox(0, 0, 960, 480, GetColor(0, 0, 0), 1);
		DrawFormatStringToHandle(960 - 160, 0, GetColor(255, 255, 255),
								 fontHandle_Loading, "Now Loading...");
		return false;
	}
	flame = 0;
	return true;
}

bool GamePlay::Load_Circle(int maxSec) {
	static int flame = 0;
	if(flame <= maxSec * 60) {
		flame++;
		DrawCircle(480, 240, (int)(536 * (flame / (double)(maxSec * 60))), 0);
		return false;
	}

	if(!Load_Now()) {
		return false;
	}

	flame = 0;
	return true;

}

void GamePlay::Start_Draw() {
	static int flame = 255;
	static int add = -7;
	flame += add;
	if(flame <= 0 || flame >= 255) {
		add = -add;
	}
	for(int i = 0; i < 480; i++) {
		DrawBox(0, i, 960, i + 1,
				GetColor(105 + 114 * i / 480, 179 + 57 * i / 480, 255), 1);
	}

	DrawGraph(230, 100, titleGraph, 1);

	DrawBox(0, 0, 960, 100, 0, 1);
	DrawBox(0, 380, 960, 480, 0, 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, flame);
	DrawFormatString(345, 320, GetColor(255, 255, 255),
					 "--- PRESS SPACE KEY TO START ---");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if(gameTrans) {
		if(Load_Circle(2)) {
			gameTrans = false;
			sound->StopTitle();
			sound->MainMenuBGM();
			if(!debugOption) {
				Tutorial_Load();
				sceneFlag = TUTORIAL;
			}
			else if(debugOption) {
				sceneFlag = MAINMENU;
			}
		}
	}
}

void GamePlay::Tutorial_Load() {
	const char *tutorialStage = { "Resource\\Stage\\Tutorial.csv" };
	stage = new BackGround(tutorialStage);

	if(stage->LoadFail()) { error(); }
}

void GamePlay::Tutorial_Update() {
	if(Input::isKeyTrigger(KEY_INPUT_SPACE) && !gameTrans) {
		tutorial_Num++;
	}
	if(tutorial_Num == 7) {
		gameTrans = true;
	}
}

void GamePlay::Tutorial_Draw() {
	stage->MapChip();
	if(tutorial_Num != 6 && tutorial_Num != 7) {
		DrawFormatString(250, 20, GetColor(255, 255, 255), "space keyを押すと次のチュートリアルに進みます");
	}

	if(tutorial_Num == 0) {
		DrawOval((int)(96 + 16 / 2), (int)(416 + (22 - 4) / 2),
				 16 / 2, (22 - 4) / 2,
				 GetColor(255, 200, 0), 1);
		DrawTriangle((int)(96 + 16 / 2), (int)(416 + 22 - 4),
					 (int)(96 + 16 / 2 - 5), (int)(416 + 22),
					 (int)(96 + 16 / 2 + 5), (int)(416 + 22),
					 GetColor(255, 200, 0), 1);

		DrawFormatString(32, 352, 0, "space key を押すと　空気がたまって浮きます");
	}
	else if(tutorial_Num == 1 || tutorial_Num == 2) {
		DrawOval((int)(448 + 16 / 2), (int)(128 + (22 - 4) / 2),
				 16 / 2, (22 - 4) / 2,
				 GetColor(255, 200, 0), 1);
		DrawTriangle((int)(448 + 16 / 2), (int)(128 + 22 - 4),
					 (int)(448 + 16 / 2 - 5), (int)(128 + 22),
					 (int)(448 + 16 / 2 + 5), (int)(128 + 22),
					 GetColor(255, 200, 0), 1);

		if(tutorial_Num == 1) {
			DrawFormatString(96, 64, 0, "左矢印keyで左に");
			DrawFormatString(640, 64, 0, "右矢印keyで右に");
		}
		else if(tutorial_Num == 2) {
			DrawFormatString(512, 96, 0, "ただし、移動すると空気が減るので注意！");
		}
	}
	else if(tutorial_Num == 3) {
		DrawOval((int)(416 + 16 / 2), (int)(192 + (22 - 4) / 2),
				 16 / 2, (22 - 4) / 2,
				 GetColor(255, 200, 0), 1);
		DrawTriangle((int)(416 + 16 / 2), (int)(192 + 22 - 4),
					 (int)(416 + 16 / 2 - 5), (int)(192 + 22),
					 (int)(416 + 16 / 2 + 5), (int)(192 + 22),
					 GetColor(255, 200, 0), 1);

		DrawFormatString(0, 224, 0, "空気が少ないと落ちていき");
		DrawFormatString(0, 224 + 15, 0, "空気が多いと浮かんでいくよ");
	}
	else if(tutorial_Num == 4) {
		DrawOval((int)(426 + 16 / 2), (int)(256 + (22 - 4) / 2),
				 16 / 2, (22 - 4) / 2,
				 GetColor(255, 200, 0), 1);
		DrawTriangle((int)(426 + 16 / 2), (int)(256 + 22 - 4),
					 (int)(426 + 16 / 2 - 5), (int)(256 + 22),
					 (int)(426 + 16 / 2 + 5), (int)(256 + 22),
					 GetColor(255, 200, 0), 1);

		DrawFormatString(0, 224, 0, "とげに当たると風船が割れてゲームオーバー");
		DrawFormatString(0, 224 + 15, 0, "画面買いに出てもゲームオーバーだよ");
	}
	else if(tutorial_Num == 5) {
		DrawOval((int)(128 + 16 / 2), (int)(96 + (22 - 4) / 2),
				 16 / 2, (22 - 4) / 2,
				 GetColor(255, 200, 0), 1);
		DrawTriangle((int)(128 + 16 / 2), (int)(96 + 22 - 4),
					 (int)(128 + 16 / 2 - 5), (int)(96 + 22),
					 (int)(128 + 16 / 2 + 5), (int)(96 + 22),
					 GetColor(255, 200, 0), 1);

		DrawFormatString(192, 96, 0, "旗に触れるとゴールだよ");
	}
	else if(tutorial_Num >= 6) {
		DrawOval((int)(448 + 16 / 2), (int)(128 + (22 - 4) / 2),
				 16 / 2, (22 - 4) / 2,
				 GetColor(255, 200, 0), 1);
		DrawTriangle((int)(448 + 16 / 2), (int)(128 + 22 - 4),
					 (int)(448 + 16 / 2 - 5), (int)(128 + 22),
					 (int)(448 + 16 / 2 + 5), (int)(128 + 22),
					 GetColor(255, 200, 0), 1);

		DrawFormatString(250, 50, 0, "TUTORIAL　終わり");
		DrawFormatString(250, 50 + 15, 0, "space keyを押すと　ゲームスタート!!!");
	}

	if(gameTrans) {
		if(Load_Circle(2)) {
			delete stage;
			gameTrans = false;
			sceneFlag = MAINMENU;
		}
	}
}

void GamePlay::MainMenu_Update() {
	if(Input::isKeyTrigger(KEY_INPUT_RIGHT)) {
		if(mainMenu_Pointer < 8) {
			mainMenu_Pointer++;
		}
		else if(mainMenu_Pointer == 8) {
			mainMenu_Pointer = 1;
		}
	}
	if(Input::isKeyTrigger(KEY_INPUT_LEFT)) {
		if(mainMenu_Pointer > 1) {
			mainMenu_Pointer--;
		}
		else if(mainMenu_Pointer == 1) {
			mainMenu_Pointer = 8;
		}
	}

	if(Input::isKeyTrigger(KEY_INPUT_SPACE)) {
		stageFlag = mainMenu_Pointer;
	}

	const char *stageName = nullptr;
	switch(stageFlag) {
		case 1:
			stageName = { "Resource\\Stage\\stage1.csv" };
			break;
		case 2:
			stageName = { "Resource\\Stage\\stage2.csv" };
			break;
		case 3:
			stageName = { "Resource\\Stage\\stage3.csv" };
			break;
		case 4:
			stageName = { "Resource\\Stage\\stage4.csv" };
			break;
		case 5:
			stageName = { "Resource\\Stage\\stage5.csv" };
			break;
		case 6:
			stageName = { "Resource\\Stage\\stage6.csv" };
			break;
		case 7:
			stageName = { "Resource\\Stage\\stage7.csv" };
			break;
		case 8:
			stageName = { "Resource\\Stage\\stage8.csv" };
			break;
	}
	if(stageFlag != 0) {
		if(!Play_Load(stageName)) {
			error();
		}
	}
}

void GamePlay::MainMenu_Draw() {
	for(int i = 0; i < 480; i++) {
		DrawBox(0, i, 960, i + 1,
				GetColor(5 + 178 * i / 480, 29 + 226 * i / 480, 191 + 60 * i / 480), 1);
	}

	static int flame = 255;
	static int add = -31;

	flame += add;

	if(flame <= 0 || flame >= 255) {
		add = -add;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, flame);
	if(mainMenu_Pointer % 2 == 1) {
		DrawFormatString(mainMenu_Pointer * 120 - 8, 180, GetColor(255, 255, 255),
						 "<   >");
	}
	else if(mainMenu_Pointer % 2 == 0) {
		DrawFormatString((mainMenu_Pointer - 1) * 120 - 8, 420, GetColor(255, 255, 255),
						 "<   >");
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for(int i = 0; i < 8; i++) {
		//上段のステージ
		if(i % 2 == 0) {
			//ステージ番号
			DrawFormatString((i + 1) * 120, 180, GetColor(255, 255, 255), " %d", i + 1);

			if(gameClear_Flag[i]) {
				DrawOval((int)(((i + 1) * 120 - 4) + 32 / 2), (int)(120 + (44 - 4) / 2),
						 32 / 2, (44 - 4) / 2,
						 gameClear_ColorY, 1);
				DrawTriangle((int)(((i + 1) * 120 - 4) + 32 / 2), (int)(120 + 44 - 4),
							 (int)(((i + 1) * 120 - 4) + 32 / 2 - 5), (int)(120 + 44),
							 (int)(((i + 1) * 120 - 4) + 32 / 2 + 5), (int)(120 + 44),
							 gameClear_ColorY, 1);
			}
			else if(!gameClear_Flag[i]) {
				DrawOval((int)(((i + 1) * 120 - 4) + 32 / 2), (int)(120 + (44 - 4) / 2),
						 32 / 2, (44 - 4) / 2,
						 gameClear_ColorN, 1);
				DrawTriangle((int)(((i + 1) * 120 - 4) + 32 / 2), (int)(120 + 44 - 4),
							 (int)(((i + 1) * 120 - 4) + 32 / 2 - 5), (int)(120 + 44),
							 (int)(((i + 1) * 120 - 4) + 32 / 2 + 5), (int)(120 + 44),
							 gameClear_ColorN, 1);
			}
		}
		//下段のステージ
		else if(i % 2 == 1) {
			//ステージ番号
			DrawFormatString(i * 120, 420, GetColor(255, 255, 255), " %d", i + 1);

			//クリアしたかどうか
			if(gameClear_Flag[i]) {
				DrawOval((int)((i * 120 - 4) + 32 / 2), (int)(360 + (44 - 4) / 2),
						 32 / 2, (44 - 4) / 2,
						 gameClear_ColorY, 1);
				DrawTriangle((int)((i * 120 - 4) + 32 / 2), (int)(360 + 44 - 4),
							 (int)((i * 120 - 4) + 32 / 2 - 5), (int)(360 + 44),
							 (int)((i * 120 - 4) + 32 / 2 + 5), (int)(360 + 44),
							 gameClear_ColorY, 1);
			}
			else if(!gameClear_Flag[i]) {
				DrawOval((int)((i * 120 - 4) + 32 / 2), (int)(360 + (44 - 4) / 2),
						 32 / 2, (44 - 4) / 2,
						 gameClear_ColorN, 1);
				DrawTriangle((int)((i * 120 - 4) + 32 / 2), (int)(360 + 44 - 4),
							 (int)((i * 120 - 4) + 32 / 2 - 5), (int)(360 + 44),
							 (int)((i * 120 - 4) + 32 / 2 + 5), (int)(360 + 44),
							 gameClear_ColorN, 1);
			}
		}
	}
}

bool GamePlay::Play_Load(const char *mapName) {
	stage = new BackGround(mapName);
	if(stage->LoadFail()) { error(); }

	stage->LoadPlayerIni();
	player = new Player(stage->ReturnXIni(),
						stage->ReturnYIni());

	gameStart_Flag = false;
	sound->StopMainMenu();
	sound->GameBGM();
	sceneFlag = PLAY;
	return true;
}

void GamePlay::Play_Update() {
	if(!gameStart_Flag) {
		GameStart_Update();
	}
		
	if(!player->ReturnClear() && !pauseSwitch && player->ReturnAlive() && gameStart_Flag) {
		player->Update(*stage);
		if(Input::isKeyTrigger(KEY_INPUT_ESCAPE)) {
			pauseSwitch = true;
		}
	}
	else if(player->ReturnClear()) {
		Clear_Update();
	}
	else if(!player->ReturnAlive()) {
		GameOver_Update();
	}
	else if(pauseSwitch) {
		Pause_Update();
	}
	stage->MapChip();
	player->Draw();
	AllDraws();
}

void GamePlay::GameStart_Update() {
	static int flame = 0;
	const int maxSec = 2 * 60;

	flame++;

	if(flame <= maxSec) {
		SetDrawBright(200, 200, 200);
		gameStart_Flag = false;
		return;
	}
	flame = 0;
	gameStart_Flag = true;
}

void GamePlay::GameStart_Draw() {
	if(!gameStart_Flag) {
		DrawStringToHandle(440, 233, "GameStart", GetColor(255, 255, 255), fontHandle_CountDown);
	}
}

void GamePlay::Clear_Update() {
	if(Input::isKeyTrigger(KEY_INPUT_SPACE)) {
		delete stage;
		delete player;
		gameClear_Flag[stageFlag] = true;
		sound->StopGame();
		sound->MainMenuBGM();
		stageFlag = 0;
		sceneFlag = MAINMENU;
	}
	SetDrawBright(200, 200, 200);
}

void GamePlay::Clear_Draw() {
	if(player->ReturnClear()) {
		DrawFormatString(200, 200, GetColor(255, 255, 255),
						 "gameclear");
		DrawFormatString(90, 215, GetColor(255, 255, 255),
						 "いずれかのキーを押してください");
	}
}

void GamePlay::GameOver_Update() {
	if(Input::isKeyTrigger(KEY_INPUT_SPACE)) {
		delete stage;
		delete player;
		sound->StopGame();
		sound->MainMenuBGM();
		stageFlag = 0;
		sceneFlag = MAINMENU;
	}
	SetDrawBright(200, 200, 200);
}

void GamePlay::GameOver_Draw() {
	if(!player->ReturnAlive()) {
		DrawFormatString(200, 200,
						 GetColor(255, 255, 255),
						 "GameOver");
	}
}

void GamePlay::Pause_Update() {
	if(Input::isKeyTrigger(KEY_INPUT_ESCAPE)) {
		sound->StopGame();
		sound->MainMenuBGM();
		sceneFlag = MAINMENU;
	}
	if(Input::isKeyTrigger(KEY_INPUT_SPACE)) {
		pauseSwitch = false;
	}
	SetDrawBright(200, 200, 200);
}

void GamePlay::Pause_Draw() {
	if(pauseSwitch) {
		DrawFormatString(200, 200,
						 GetColor(255, 255, 255),
						 "pause");
	}
}

void GamePlay::AllDraws() {
	SetDrawBright(255, 255, 255);
	Clear_Draw();
	GameOver_Draw();
	Pause_Draw();
	GameStart_Draw();
}

void GamePlay::error() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "errorが発生しました");
	if(CheckHitKeyAll()) {
		gameEnd = true;
	}
}
