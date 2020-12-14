#pragma once

class Player {
//private:
public:
	double playerX;
	double playerY;
	double oldPlayerX;
	double oldPlayerY;
	int graph;
	int airRemain;
	int oldAirRemain;
	int speed;
	int radius;
	int width;
	int height;
	bool rightSwich = false;
	bool leftSwich = false;
	bool airSwich = false;
	bool floatSwich = false;
	int flame = 0;
	float maxFlame = 50;
	bool playerAlive = true;
public:
	Player(double playerX, double playerY,double graph,double airRemain = 70, int speed = 4, int radius = 8, int width = 16, int height = 16);

	void Update();
	void Draw();

private:
	void PlayerInput();
	void PlayerRun();
	void StateCheck();
	bool IsPlayerAlive();
};
