#pragma once
#include "Player.h"
#include "BackGround.h"

class GamePlay {
private:
	bool gameEnd;
	int stageFlag;
	int sceneFlag = 2;
	bool stageEnd;
	BackGround *stage;
	Player *player;

public:
	GamePlay() {
		Game();
	}
	void Game();
private:
	void Start();
	void MainMenu();
	bool PlayIni(const char *mapName);
	bool Play();
};
