#include "GamePlay.h"
#include "DxLib.h"
#include "system/Initialize.h"

void GamePlay::game() {
	while (1)
	{
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//
		//�X�V����
		if(CheckHitKey(KEY_INPUT_A))
		{
			break;
		}
		
		//�`�揈��
		DrawCircle(200,300,16,GetColor(255,255,255));
		DrawFormatString(0,0,GetColor(255,255,255),"����̓e�X�g�ł��B");


		//---------  �����܂łɃv���O�������L�q  ---------//
		if(DXlibfina() == -1) { break; }
	}
	
}
