#include "Sound.h"
#include "DxLib.h"

Sound::Sound() {
	LoadSound();
}

void Sound::LoadSound() {
	soundBGM[0] = LoadSoundMem("Resource\\Sound\\StartBGM.mp3");
	soundBGM[1] = LoadSoundMem("Resource\\Sound\\MainMenuBGM.mp3");
	soundBGM[2] = LoadSoundMem("Resource\\Sound\\GameBGM.mp3");

	ChangeVolumeSoundMem(255 * 30 / 100,soundBGM[0]);
	ChangeVolumeSoundMem(255 * 30 / 100,soundBGM[1]);
	ChangeVolumeSoundMem(255 * 30 / 100,soundBGM[2]);
}

void Sound::TitleBGM() {
	if(CheckSoundMem(soundBGM[0]) == 0)
	{
		PlaySoundMem(soundBGM[0],DX_PLAYTYPE_LOOP);
	}
}

void Sound::MainMenuBGM() {
	if(CheckSoundMem(soundBGM[1]) == 0)
	{
		PlaySoundMem(soundBGM[1],DX_PLAYTYPE_LOOP);
	}
}

void Sound::GameBGM() {
	if(CheckSoundMem(soundBGM[2]) == 0)
	{
		PlaySoundMem(soundBGM[2],DX_PLAYTYPE_LOOP);
	}
}

void Sound::StopTitle() {
	StopSoundMem(soundBGM[0]);
}

void Sound::StopMainMenu() {
	StopSoundMem(soundBGM[1]);
}

void Sound::StopGame() {
	StopSoundMem(soundBGM[2]);
}
