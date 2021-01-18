#include "Player.h"
#include "DxLib.h"
#include <algorithm>
#include "Input.h"
#include "Effect.h"
#include "CheckHit.h"

Player::Player(double playerX, double playerY, double graph, double airRemain, float speed, int radius, int width, int height) :
	playerX(playerX),
	playerY(playerY),
	oldPlayerX(playerX),
	oldPlayerY(playerY),
	graph(graph),
	airRemain(airRemain),
	speed(speed),
	radius(radius),
	width(width),
	height(height) {
}

void Player::Update() {
	PlayerInput();
	PlayerRun();
}

void Player::Draw() {
	if(rightSwich) {

	}
	else if(leftSwich) {

	}
	else if(airSwich) {

	}
	else {
		//DrawGraph(playerX, playerY, graph, 1);
	}

	DrawGraph(playerX, playerY, graph, 1);
}

void Player::PlayerInput() {
	if(Input::isKeyTrigger(KEY_INPUT_RIGHT) || Input::isKeyTrigger(KEY_INPUT_D)) {
		if(!leftSwich && !rightSwich && !airSwich) {
			rightSwich = true;
			oldPlayerX = playerX;
		}
	}

	if(Input::isKeyTrigger(KEY_INPUT_LEFT) || Input::isKeyTrigger(KEY_INPUT_A)) {
		if(!leftSwich && !rightSwich && !airSwich) {
			leftSwich = true;
			oldPlayerX = playerX;
		}
	}

	if(Input::isKeyTrigger(KEY_INPUT_SPACE)) {
		if(!leftSwich && !rightSwich && !airSwich) {
			airSwich = true;
			oldAirRemain = airRemain;
		}
	}
}

void Player::PlayerRun() {
	oldPlayerX = playerX;
	oldPlayerY = playerY;

	if(!airSwich)
	{
		if(airRemain >= 80) {
			playerY -= speed + airRemain * 0.1;
		}
		else{
			playerY += speed;
		}
	}


	if(rightSwich) {
		if(flame <= maxFlame) {
			flame++;
			playerX = oldPlayerX + 100 * Effect::EaseOutQuart(flame / maxFlame, 5);
		}
		else {
			flame = 0;
			airRemain -= 5;
			rightSwich = false;
		}
	}

	if(leftSwich) {
		if(flame <= maxFlame) {
			flame++;
			playerX = oldPlayerX - 100 * Effect::EaseOutQuart(flame / maxFlame, 5);
		}
		else {
			flame = 0;
			airRemain -= 5;
			leftSwich = false;
		}
	}

	if(airSwich) {
		if(flame <= maxFlame) {
			flame++;
			airRemain = oldAirRemain + 11 * Effect::EaseOutQuart(flame / maxFlame, 5);
		}
		else {
			flame = 0;
			airSwich = false;
		}
	}
}

void Player::StateCheck() {
}

void Player::PlayerHit(BackGround stage) {
	for(int i = 0; i < 200; i++) {
		for(int j = 0; j < 200; j++) {
			if(stage.returnMap(i, j) == 1) {
				if(CheckHit::checkHit(playerX,
									  playerY,
									  width,
									  height,
									  stage.returnXSize() * i,
									  stage.returnYSize() * j,
									  stage.returnXSize(),
									  stage.returnYSize())) {
					if(playerX != oldPlayerX) {
						playerX = max(playerX, oldPlayerX);
						playerX /= stage.returnXSize();
						playerX *= stage.returnXSize();
					}
					if(playerY != oldPlayerY) {
						playerY = max(playerY, oldPlayerY);
						playerY /= stage.returnYSize();
						playerY *= stage.returnYSize();
					}
				}
			}
		}
	}
}

bool Player::IsPlayerAlive() {
	return playerAlive;
}
