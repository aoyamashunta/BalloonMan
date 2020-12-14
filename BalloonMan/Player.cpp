#include "Player.h"
#include "DxLib.h"
#include "Input.h"
#include "Effect.h"

Player::Player(double playerX, double playerY, double graph, double airRemain, int speed, int radius, int width, int height) :
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
	if(!airSwich && airRemain >= 80) {
		playerY -= 0.5;
	}
	else if(!airSwich) {
		playerY += 0.5;
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
	if()
}

bool Player::IsPlayerAlive() {
	return playerAlive;
}
