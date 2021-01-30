#pragma once

class BackGround {
private:
	const char *fname;
	int mapXSize;
	int mapYSize;
	int mapChipMax;
	int map[200][30];
	bool error;
	int playerXIni;
	int playerYIni;
	int whiteColor;
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
private:
	//map_chip Block 
	void DrawBlock(int i, int j);
	//map_chip Goal
	void DrawGoal(int i, int j);
	//map_chip Spine
	void DrawSpine(int i, int j);
};
