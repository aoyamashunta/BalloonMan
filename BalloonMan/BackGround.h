#pragma once
#include "Player.h"

class BackGround {
private:
	const char *fname;
	int mapXSize;
	int mapYSize;
	int mapChipMax;
	int mapChipHandle[10];
	int map[200][200];
	bool error;
	int playerXIni;
	int playerYIni;
public:
	BackGround(const char *mapName);
	void mapReWrite(const unsigned char data[200][200]);
	bool mapLoad();
	void mapChip();
	bool loadFail(){
		return error;
	} 
	int returnXIni(){
		return playerXIni;
	}
	int returnYIni(){
		return playerYIni;
	}
	int returnMap(int i, int j) {
		return map[i][j];
	}
	int returnXSize(){
		return mapXSize;
	}
	int returnYSize(){
		return mapYSize;
	}
};
