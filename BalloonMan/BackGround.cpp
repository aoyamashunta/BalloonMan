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

int WIN_WIDTH = 480; //ウィンドウ横幅
int WIN_HEIGHT = 480;//ウィンドウ縦幅

BackGround::BackGround(const char *mapName) :
	mapXSize(32),
	mapYSize(32),
	mapChipMax(3),
	map() {
	fname = mapName;
	LoadDivGraph("mapHandle.png", 10, 10, 1, mapXSize, mapYSize, mapChipHandle);
	error = false;
	if(!MapLoad()) {
		//実行しない
		error = true;
	}
}

bool BackGround::MapLoad() {
	char buf[1000], *p, *end;
	//[200]がxの最大値 [200]がyの最大値　で仮固定
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
				long num = strtol(p, &end, 10);		// 10進数を読み取る
				if(p == end) break;						// 読み取り終了
				if(num < 0 || num > mapChipMax) {
					fclose(fp);
					return false;	// 異常終了
				}
				map[i][j] = num;
				p = end + 1;	// ',' をスキップする
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
