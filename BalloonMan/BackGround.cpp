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

//extern int WIN_WIDTH;	//ウィンドウ横幅
//extern int WIN_HEIGHT;	//ウィンドウ縦幅

BackGround::BackGround(const char *mapName) :
	mapXSize(32),
	mapYSize(32),
	mapChipMax(4),
	map() {
	whiteColor = GetColor(108,103,110);
	fname = mapName;
	error = false;
	if(!MapLoad()) {
		//実行しない
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
	return true;
}

void BackGround::MapChip() {
	//背景
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
	//内側の塗りつぶし
	DrawBox((int)((i + 0.125) * mapXSize),
			(int)((j + 0.25) * mapYSize),
			(int)((i + 0.875) * mapXSize),
			(int)((j + 0.75) * mapYSize),
			GetColor(255,255,255),
			1);
	
	//下段の雲
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

	//中段の雲
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

	//上段の雲
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
	//goal flagの棒の部分
	DrawLine((int)((i + 0.25) * mapXSize),
			 j * mapYSize,
			 (int)((i + 0.25) * mapXSize),
			 (j + 1) * mapYSize,
			 whiteColor);
	
	//goal flagの旗の部分
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
	//中心円
	DrawCircle((int)((i + 0.5) * mapXSize),
			   (int)((j + 0.5) * mapYSize),
			   mapXSize / 2 - 5,
			   GetColor(0, 0, 0));
	
	//上三角
	DrawTriangle((int)((i + 0.5) * mapXSize),
				 j * mapYSize,
				 (int)((i + 0.5) * mapXSize - 2),
				 j * mapYSize + 4,
				 (int)((i + 0.5) * mapXSize + 2),
				 j * mapYSize + 4,
				 whiteColor, 1);
	
	//右上三角
	DrawTriangle((i + 1) * mapXSize,
				 j * mapYSize,
				 (int)((i + 0.5) * mapXSize + 2),
				 j * mapYSize + 4,
				 (i + 1) * mapXSize - 4,
				 (int)((j + 0.5) * mapYSize - 2),
				 whiteColor, 1);

	//右三角
	DrawTriangle((i + 1) * mapXSize,
				 (int)((j + 0.5) * mapYSize),
				 (i + 1) * mapXSize - 4,
				 (int)((j + 0.5) * mapYSize - 2),
				 (i + 1) * mapXSize - 4,
				 (int)((j + 0.5) * mapYSize + 2),
				 whiteColor, 1);

	//右下三角
	DrawTriangle((i + 1) * mapXSize,
				 (j + 1) * mapYSize,
				 (i + 1) * mapXSize - 4,
				 (int)((j + 0.5) * mapYSize + 2),
				 (int)((i + 0.5) * mapXSize + 2),
				 (j + 1) * mapYSize - 4,
				 whiteColor, 1);

	//下三角
	DrawTriangle((int)((i + 0.5) * mapXSize),
				 (j + 1) * mapYSize,
				 (int)((i + 0.5) * mapXSize + 2),
				 (j + 1) * mapYSize - 4,
				 (int)((i + 0.5) * mapXSize - 2),
				 (j + 1) * mapYSize - 4,
				 whiteColor, 1);

	//左下三角
	DrawTriangle(i * mapXSize,
				 (j + 1) * mapYSize,
				 (int)((i + 0.5) * mapXSize - 2),
				 (j + 1) * mapYSize - 4,
				 i * mapXSize + 4,
				 (int)((j + 0.5) * mapYSize + 2),
				 whiteColor, 1);

	//左三角
	DrawTriangle(i * mapXSize,
				 (int)((j + 0.5) * mapYSize),
				 i * mapXSize + 4,
				 (int)((j + 0.5) * mapYSize + 2),
				 i * mapXSize + 4,
				 (int)((j + 0.5) * mapYSize - 2),
				 whiteColor, 1);
	
	//左上三角
	DrawTriangle(i * mapXSize,
				 j * mapYSize,
				 (int)((i + 0.5) * mapXSize - 2),
				 j * mapYSize + 4,
				 i * mapXSize + 4,
				 (int)((j + 0.5) * mapYSize - 2),
				 whiteColor, 1);
}
