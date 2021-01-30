#pragma once
#include "Player.h"
#include "BackGround.h"

class GamePlay {
private:
	bool gameEnd;
	int stageFlag;
	int sceneFlag = 1;
	bool stageEnd;
	bool pauseSwitch;
	BackGround *stage;
	Player *player;

public:
	GamePlay();
	void Game();
private:
	void Load();
	bool LoadStart();
	void Start();
	bool LoadMainMenu();
	void MainMenu();
	bool LoadPlay(const char *mapName);
	bool Play();
	void Clear();
	void GameOver();
	void Pause();
};
