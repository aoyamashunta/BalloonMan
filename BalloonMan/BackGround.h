#pragma once

class BackGround {
private:
	const char *fname;
	int mapXSize;
	int mapYSize;
	int mapChipMax;
	int mapChipHandle[10];
	int map[200][20];
	bool error;
	int playerXIni;
	int playerYIni;
public:
	BackGround(const char *mapName);
	bool MapLoad();
	void MapChip();
	void LoadPlayerIni();
	bool LoadFail(){
		return error;
	} 
	int ReturnXIni(){
		return playerXIni;
	}
	int ReturnYIni(){
		return playerYIni;
	}
	int ReturnMap(int x, int y) {
		return map[y][x];
	}
	int ReturnXSize(){
		return mapXSize;
	}
	int ReturnYSize(){
		return mapYSize;
	}
};
