#include "BackGround.h"
#include "stdio.h"
#include <stdlib.h>
#include "DxLib.h"

enum {
	NONE,
	BLOCK,
	PLAYER
};

BackGround::BackGround(const char *mapName) :
	mapXSize(32),
	mapYSize(32),
	mapChipMax(2),
	map()
{
	fname = mapName;
	LoadDivGraph("mapHandle.png", 10, 10, 1, mapXSize, mapYSize, mapChipHandle);
	error = false;
	if(!mapLoad()) {
		//実行しない
		error = true;
	}
}

void BackGround::mapReWrite(const unsigned char data[200][200]) {
	for(int i = 0; i < 200; i++) {
		for(int j = 0; j < 200; j++) {
			if(data[i][j] == 48) {
				map[i][j] = NONE;
			}
			else if(data[i][j] == 49) {
				map[i][j] = BLOCK;
			}
			else if(data[i][j] == 50) {
				map[i][j] = 2;
			}
			else if(data[i][j] == 51) {
				map[i][j] = 3;
			}
			else if(data[i][j] == 52) {
				map[i][j] = 4;
			}
			else if(data[i][j] == 53) {
				map[i][j] = 5;
			}
			else if(data[i][j] == 54) {
				map[i][j] = 6;
			}
			else if(data[i][j] == 55) {
				map[i][j] = 7;
			}
			else if(data[i][j] == 56) {
				map[i][j] = 8;
			}
			else if(data[i][j] == 57) {
				map[i][j] = 9;
			}
		}
	}
}

bool BackGround::mapLoad() {
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

void BackGround::mapChip() {
	for(int i = 0; i < 200; i++) {
		for(int j = 0; j < 200; j++) {
			if(map[i][j] == NONE) {
				DrawGraph(i * mapXSize, j * mapYSize, mapChipHandle[0], 1);
			}
			else if(map[i][j] == BLOCK) {
				DrawGraph(i * mapXSize, j * mapYSize, mapChipHandle[1], 1);
			}
			else if(map[i][j] == PLAYER)
			{
				playerXIni = i * mapXSize;
				playerYIni = j * mapYSize;
			}
		}
	}
}