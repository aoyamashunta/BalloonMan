#include "GamePlay.h"
#include "DxLib.h"
#include "system/Initialize.h"
#include "Input.h"
#include "BackGround.h"

BackGround *stage;
Player *player;

void GamePlay::MainMenu() {
	//�ϐ��̐錾
	int graph = LoadGraph("player.png");


	gameEnd = false;

	while(1) {
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//
		//���͏���
		Input::Update();
		if(Input::isKeyTrigger(KEY_INPUT_1)) {
			stageFlag = 1;
			const char *stageName = { "stage.csv" };
			stage = new BackGround(stageName);
			PlayIni(*stage);
			player = new Player(stage->returnXIni(), stage->returnYIni(), graph);
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

		if(!Play(*stage,*player)) {
			break;
		}



		//�`�揈��
		//debug
		//DrawFormatString(0, 0, GetColor(255, 255, 255), "stageFlag : %d",stageFlag);
		//DrawFormatString(0, 15, GetColor(255, 255, 255), "player.flame : %d",player1->airRemain);

		//---------  �����܂łɃv���O�������L�q  ---------//
		if(gameEnd == true) { break; }
		if(DXlibfina() == -1) { break; }
	}
}

bool GamePlay::PlayIni(BackGround &stage) {
	if(stage.loadFail()) { return false; }
	stage.mapChip();
}

bool GamePlay::Play(BackGround &stage,Player &player) {

	if(stageFlag == 1) {
		stage.mapChip();

		player.Update();
		player.Draw();
	}
	return true;
}
