#pragma once

class BackGround {
private:
	int mapX;
	int mapY;
	int mapXSize;
	int mapYSize;
	int mapChipHandle[3];
public:
	BackGround();
	void mapLoad();
};
