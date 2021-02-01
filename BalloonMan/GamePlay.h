#pragma once
#include "Player.h"
#include "BackGround.h"
#include "Sound.h"

class GamePlay {
private:
	bool gameEnd;
	bool gameTrans;
	int stageFlag;
	int sceneFlag;
	bool stageEnd;
	bool pauseSwitch;
	BackGround *stage;
	Player *player;
	Sound *sound;

	bool debugOption = false;
	int titleGraph;
	
	int tutorial_Num;
	
	int fontHandle_CountDown;
	int fontHandle_Loading;

	bool gameStart_Flag;

	int mainMenu_Pointer;
	int mainMenu_SceneNum;

	bool gameClear_Flag[8];
	int gameClear_ColorY;
	int gameClear_ColorN;

public:
	GamePlay();
private:
	void Game();

	//Load‰æ–Ê
	bool Load_Now();
	bool Load_Circle(int maxSec);

	//Start‰æ–Ê
	bool Start_Load();
	void Start_Draw();

	//Tutorial‰æ–Ê
	void Tutorial_Load();
	void Tutorial_Update();
	void Tutorial_Draw();

	//MainMenu‰æ–Ê
	void MainMenu_Update();
	void MainMenu_Draw();

	//Play‰æ–Ê
	bool Play_Load(const char *mapName);
	void Play_Update();
	void GameStart_Update();
	void GameStart_Draw();
	void Clear_Update();
	void Clear_Draw();
	void GameOver_Update();
	void GameOver_Draw();
	void Pause_Update();
	void Pause_Draw();
	void AllDraws();
	void error();
};
