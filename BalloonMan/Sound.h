#pragma once

class Sound {
private:
	int soundBGM[3];
	int soundSE;
public:
	Sound();
	void LoadSound();
	void TitleBGM();
	void MainMenuBGM();
	void GameBGM();
	void StopTitle();
	void StopMainMenu();
	void StopGame();
};
