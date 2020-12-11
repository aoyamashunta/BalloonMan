#pragma once

class Player {
private:
	int playerX;
	int playerY;
	int oldPlayerX;
	int oldPlayerY;
	int graph;
	int airRemain;
	int speed;
	int radius;
	int width;
	int height;
	bool rightSwich = false;
	bool leftSwich = false;
	bool airSwich = false;
	bool floatSwich = false;
	int flame = 0;
	int maxFlame = 300;
public:
	Player(int playerX, int playerY,int graph,int airRemain = 70, int speed = 4, int radius = 8, int width = 16, int height = 16);

	void Update();
	void Draw();

private:
	void Move();
	void PlayerInput();
	void PlayerRun();
};
