#include "Initialize.h"
#include "DxLib.h"

const char TITLE[] = "BalloonMan(��)";

const int WIN_WIDTH = 600; //�E�B���h�E����
const int WIN_HEIGHT = 400;//�E�B���h�E�c��


int DXlibInit() {
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɐݒ�
	//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// �^�C�g����ύX
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�ɍ��킹��j
	SetWindowSizeExtendRate(1.0);				//��ʃT�C�Y��ݒ�i�𑜓x�Ƃ̔䗦�Őݒ�j
	SetBackgroundColor(0x00, 0x00, 0xFF);		// ��ʂ̔w�i�F��ݒ肷��

	//Dx���C�u�����\���̏�����
	if (DxLib_Init() == -1) { return -1; }

	//�i�_�u���o�b�t�@�j�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);
	return 0;
}

int DXlibfina() {
	ScreenFlip();//�i�_�u���o�b�t�@�j����
	// 20�~���b�ҋ@�i�^��60FPS�j
	WaitTimer(20);
	if (ProcessMessage() == -1)
	{
		return -1;
	}
	return 0;
}
