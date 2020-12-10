#include "GamePlay.h"
#include "DxLib.h"
#include "system/Initialize.h"
#include "Input.h"

void GamePlay::game() {
	//�ϐ��̐錾
	int stageFlag = 0;

	
	while(1) {
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//
		//���͏���
		Input::Update();
		if(Input::isKeyTrigger(KEY_INPUT_1)) {
			stageFlag = 1;
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

		if(Input::isKeyTrigger(KEY_INPUT_A)) {
			break;
		}

		//�X�V����
		if(stageFlag == 1) {
		}



		//�`�揈��
		DrawFormatString(0, 0, GetColor(255, 255, 255), "stageFlag : %d",stageFlag);


		//---------  �����܂łɃv���O�������L�q  ---------//
		if(DXlibfina() == -1) { break; }
	}
}
