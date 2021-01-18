#pragma once
#include "BackGround.h"

class Player {
public:
	double playerX;
	double playerY;
	double oldPlayerX;
	double oldPlayerY;
	int graph;
	int airRemain;
	int oldAirRemain;
	float speed;
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
	
	Player(double playerX, double playerY,double graph,double airRemain = 70, float speed = 0.5, int radius = 8, int width = 16, int height = 16);

	void Update();
	void Draw();

private:
	void PlayerInput();
	void PlayerRun();
	void StateCheck();
	void PlayerHit(BackGround stage);
	bool IsPlayerAlive();
};
