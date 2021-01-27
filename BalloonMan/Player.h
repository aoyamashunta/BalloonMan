#pragma once
#include "BackGround.h"

class Player {
private:
	double playerX;
	double playerY;
	double oldPlayerX;
	double oldPlayerY;
	int oldPlayerXHit;
	int oldPlayerYHit;
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
	bool flyStates = false;
	bool stageClear;
public:
	Player(double playerX, double playerY,int airRemain = 70, float speed = 0.5, int radius = 8, int width = 16, int height = 16);

	void Update(BackGround stage);
	void Draw();

	void PlayerHit(BackGround stage);
	void PlayerHitSub(BackGround stage,int i ,int j);
	
	double RplayerY() {
		return playerY;
	}
	bool ReturnClear() {
		return stageClear;
	}
	void TurnClear() {
		stageClear != stageClear;
	}
private:
	void PlayerInput();
	void PlayerRun();
	bool CheckFlyStates();
	bool IsPlayerAlive();
};
