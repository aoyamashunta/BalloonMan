#pragma once
#include "Player.h"
#include "BackGround.h"

class GamePlay {
public:
	bool gameEnd;
	int stageFlag;
	bool stageEnd;
	
	GamePlay() {
		MainMenu();
	}
	void MainMenu();
	bool PlayIni(BackGround &stage);
	bool Play(BackGround &stage,Player &player);
};
