#include "Player.h"
#include "DxLib.h"
#include "Input.h"
#include "Easing.h"

Player::Player(int playerX, int playerY, int graph, int airRemain, int speed, int radius, int width, int height) :
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
	Move();
}

void Player::Draw() {
	if(rightSwich) {

	}
	else if(leftSwich) {

	}
	else if(airSwich) {

	}
	else {
		DrawGraph(playerX, playerY, graph, 1);
	}
}

void Player::Move() {
	PlayerInput();
	PlayerRun();
}

void Player::PlayerInput() {
	if(Input::isKeyTrigger(KEY_INPUT_RIGHT) || Input::isKeyTrigger(KEY_INPUT_D)) {
		if(!leftSwich && !rightSwich) {
			rightSwich = true;
			oldPlayerX = playerX;
		}
	}

	if(Input::isKeyTrigger(KEY_INPUT_LEFT) || Input::isKeyTrigger(KEY_INPUT_A)) {
		if(!leftSwich && !rightSwich) {
			leftSwich = true;
			oldPlayerX = playerX;
		}
	}

	if(Input::isKeyTrigger(KEY_INPUT_SPACE)) {
		if(!airSwich) {
			airSwich = true;
		}
	}
}

void Player::PlayerRun() {
	if(rightSwich) {
		if(flame <= maxFlame) {
			flame++;
			playerX = oldPlayerX + 10 * Easing::EaseIn(flame / maxFlame, 5);
		}
		else {
			flame = 0;
			rightSwich = false;
		}
	}

	if(leftSwich) {
		if(flame <= maxFlame) {
			flame++;
			playerX = oldPlayerX - 10 * Easing::EaseIn(flame / maxFlame, 5);
		}
		else {
			flame = 0;
			leftSwich = false;
		}
	}

	if(airSwich) {

	}
}
