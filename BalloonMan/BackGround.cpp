#include "BackGround.h"
#include "stdio.h"
#include <stdlib.h>
#include "DxLib.h"

enum blocknum {
	NONE,
	BLOCK,
	PLAYER,
	GOAL
};

int WIN_WIDTH = 480; //�E�B���h�E����
int WIN_HEIGHT = 480;//�E�B���h�E�c��

BackGround::BackGround(const char *mapName) :
	mapXSize(32),
	mapYSize(32),
	mapChipMax(3),
	map() {
	fname = mapName;
	LoadDivGraph("mapHandle.png", 10, 10, 1, mapXSize, mapYSize, mapChipHandle);
	error = false;
	if(!MapLoad()) {
		//���s���Ȃ�
		error = true;
	}
}

bool BackGround::MapLoad() {
	char buf[1000], *p, *end;
	//[200]��x�̍ő�l [200]��y�̍ő�l�@�ŉ��Œ�
	//unsigned char data[200][200];

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
			for(int j = 0; j < 20; j++) {
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
	//mapReWrite(data);
	return true;
}

void BackGround::MapChip() {
	for(int i = 0; i < 20; i++) {
		for(int j = 0; j < 200; j++) {
			if(map[j][i] == BLOCK) {
				//DrawGraph(i * mapXSize, j * mapYSize, mapChipHandle[0], 1);
				DrawBox(i * mapXSize,
						j * mapYSize,
						(i + 1) * mapXSize,
						(j + 1) * mapYSize,
						GetColor(255,255,255),
						0);
			}
			else if(map[j][i] == GOAL)
			{
				DrawBox(i * mapXSize,
						j * mapYSize,
						(i + 1) * mapXSize,
						(j + 1) * mapYSize,
						GetColor(255,255,255),
						1);
			}
		}
	}
}

void BackGround::LoadPlayerIni() {
	for(int i = 0; i < 20; i++) {
		for(int j = 0; j < 200; j++) {
			if(map[j][i] == PLAYER) {
				playerXIni = i * mapXSize;
				playerYIni = j * mapYSize;
			}
		}
	}
}
