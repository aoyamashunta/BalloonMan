#include "BackGround.h"
#include "stdio.h"
#include <stdlib.h>
#include "DxLib.h"

extern enum blocknum{
	NONE,
	BLOCK,
	PLAYER,
	GOAL,
	SPINE
};

//extern int WIN_WIDTH;	//�E�B���h�E����
//extern int WIN_HEIGHT;	//�E�B���h�E�c��

BackGround::BackGround(const char *mapName) :
	mapXSize(32),
	mapYSize(32),
	mapChipMax(4),
	map() {
	whiteColor = GetColor(108,103,110);
	fname = mapName;
	error = false;
	if(!MapLoad()) {
		//���s���Ȃ�
		error = true;
	}
}

bool BackGround::MapLoad() {
	char buf[1000], *p, *end;

	FILE *fp;
	errno_t error;
	error = fopen_s(&fp, fname, "r");

	if(error != 0) {
		return false;
	}
	else {
		for(int i = 0; i < 200; i++) {
			if(fgets(buf, sizeof(buf), fp) == NULL) {
				break;
			}
			p = buf;
			for(int j = 0; j < 30; j++) {
				long num = strtol(p, &end, 10);		// 10�i����ǂݎ��
				if(p == end) break;						// �ǂݎ��I��
				if(num < 0 || num > mapChipMax) {
					fclose(fp);
					return false;	// �ُ�I��
				}
				map[i][j] = num;
				p = end + 1;	// ',' ���X�L�b�v����
			}
		}
		fclose(fp);
	}
	return true;
}

void BackGround::MapChip() {
	//�w�i
	for(int i = 0; i < 480; i++) {
			DrawBox(0, i, 960, i + 1,
					GetColor(105 + 114 * i / 480, 179 + 57 * i / 480, 255), 1);
	}

	//map chip
	for(int i = 0; i < 30; i++) {
		for(int j = 0; j < 200; j++) {
			if(map[j][i] == BLOCK) {
				DrawBlock(i,j);
			}
			else if(map[j][i] == GOAL) {
				DrawGoal(i,j);
			}
			else if(map[j][i] == SPINE) {
				DrawSpine(i,j);
			}
		}
	}
}

void BackGround::LoadPlayerIni() {
	for(int i = 0; i < 30; i++) {
		for(int j = 0; j < 200; j++) {
			if(map[j][i] == PLAYER) {
				playerXIni = i * mapXSize;
				playerYIni = j * mapYSize;
			}
		}
	}
}

void BackGround::DrawBlock(int i,int j) {
	//�����̓h��Ԃ�
	DrawBox((int)((i + 0.125) * mapXSize),
			(int)((j + 0.25) * mapYSize),
			(int)((i + 0.875) * mapXSize),
			(int)((j + 0.75) * mapYSize),
			GetColor(255,255,255),
			1);
	
	//���i�̉_
	DrawOval((int)((i + 0.25) * mapXSize),
			 (int)((j + 0.8125) * mapYSize),
			 10,5,
			 GetColor(255,255,255),1);
	DrawOval((int)((i + 0.5) * mapXSize),
			 (int)((j + 0.8125) * mapYSize),
			 10,4,
			 GetColor(255,255,255),1);
	DrawOval((int)((i + 0.75) * mapXSize),
			 (int)((j + 0.8125) * mapYSize),
			 10,5,
			 GetColor(255,255,255),1);

	//���i�̉_
	DrawOval((int)((i + 0.25) * mapXSize),
			 (int)((j + 0.5) * mapYSize),
			 8,5,
			 GetColor(255,255,255),1);
	DrawOval((int)((i + 0.375) * mapXSize),
			 (int)((j + 0.5) * mapYSize),
			 10,4,
			 GetColor(255,255,255),1);
	DrawOval((int)((i + 0.625) * mapXSize),
			 (int)((j + 0.5) * mapYSize),
			 10,4,
			 GetColor(255,255,255),1);
	DrawOval((int)((i + 0.75) * mapXSize),
			 (int)((j + 0.5) * mapYSize),
			 8,5,
			 GetColor(255,255,255),1);

	//��i�̉_
	DrawOval((int)((i + 0.75) * mapXSize),
			   (int)((j + 0.25) * mapYSize),
			   10,8,
			   GetColor(255,255,255),1);
	DrawCircle((int)((i + 0.375) * mapXSize),
			   (int)((j + 0.1875) * mapYSize),
			   6,
			   GetColor(255,255,255));
}

void BackGround::DrawGoal(int i, int j) {
	//goal flag�̖_�̕���
	DrawLine((int)((i + 0.25) * mapXSize),
			 j * mapYSize,
			 (int)((i + 0.25) * mapXSize),
			 (j + 1) * mapYSize,
			 whiteColor);
	
	//goal flag�̊��̕���
	DrawTriangle((int)((i + 0.25) * mapXSize),
				 j * mapYSize,
				 (int)((i + 0.25) * mapXSize),
				 (int)((j + 0.5) * mapYSize),
				 (i + 1) * mapXSize,
				 (int)((j + 0.25) * mapYSize),
				 GetColor(255, 0, 0),
				 1);
}

void BackGround::DrawSpine(int i, int j) {
	//���S�~
	DrawCircle((int)((i + 0.5) * mapXSize),
			   (int)((j + 0.5) * mapYSize),
			   mapXSize / 2 - 5,
			   GetColor(0, 0, 0));
	
	//��O�p
	DrawTriangle((int)((i + 0.5) * mapXSize),
				 j * mapYSize,
				 (int)((i + 0.5) * mapXSize - 2),
				 j * mapYSize + 4,
				 (int)((i + 0.5) * mapXSize + 2),
				 j * mapYSize + 4,
				 whiteColor, 1);
	
	//�E��O�p
	DrawTriangle((i + 1) * mapXSize,
				 j * mapYSize,
				 (int)((i + 0.5) * mapXSize + 2),
				 j * mapYSize + 4,
				 (i + 1) * mapXSize - 4,
				 (int)((j + 0.5) * mapYSize - 2),
				 whiteColor, 1);

	//�E�O�p
	DrawTriangle((i + 1) * mapXSize,
				 (int)((j + 0.5) * mapYSize),
				 (i + 1) * mapXSize - 4,
				 (int)((j + 0.5) * mapYSize - 2),
				 (i + 1) * mapXSize - 4,
				 (int)((j + 0.5) * mapYSize + 2),
				 whiteColor, 1);

	//�E���O�p
	DrawTriangle((i + 1) * mapXSize,
				 (j + 1) * mapYSize,
				 (i + 1) * mapXSize - 4,
				 (int)((j + 0.5) * mapYSize + 2),
				 (int)((i + 0.5) * mapXSize + 2),
				 (j + 1) * mapYSize - 4,
				 whiteColor, 1);

	//���O�p
	DrawTriangle((int)((i + 0.5) * mapXSize),
				 (j + 1) * mapYSize,
				 (int)((i + 0.5) * mapXSize + 2),
				 (j + 1) * mapYSize - 4,
				 (int)((i + 0.5) * mapXSize - 2),
				 (j + 1) * mapYSize - 4,
				 whiteColor, 1);

	//�����O�p
	DrawTriangle(i * mapXSize,
				 (j + 1) * mapYSize,
				 (int)((i + 0.5) * mapXSize - 2),
				 (j + 1) * mapYSize - 4,
				 i * mapXSize + 4,
				 (int)((j + 0.5) * mapYSize + 2),
				 whiteColor, 1);

	//���O�p
	DrawTriangle(i * mapXSize,
				 (int)((j + 0.5) * mapYSize),
				 i * mapXSize + 4,
				 (int)((j + 0.5) * mapYSize + 2),
				 i * mapXSize + 4,
				 (int)((j + 0.5) * mapYSize - 2),
				 whiteColor, 1);
	
	//����O�p
	DrawTriangle(i * mapXSize,
				 j * mapYSize,
				 (int)((i + 0.5) * mapXSize - 2),
				 j * mapYSize + 4,
				 i * mapXSize + 4,
				 (int)((j + 0.5) * mapYSize - 2),
				 whiteColor, 1);
}
