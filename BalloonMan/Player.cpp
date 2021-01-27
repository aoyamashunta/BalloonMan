#include "Player.h"
#include "DxLib.h"
#include "Input.h"
#include "Effect.h"
#include "CheckHit.h"

extern enum blocknum {
	NONE,
	BLOCK,
	PLAYER,
	GOAL
};

Player::Player(double playerX, double playerY, int airRemain, float speed, int radius, int width, int height) :
	playerX(playerX),
	playerY(playerY),
	oldPlayerX(playerX),
	oldPlayerY(playerY),
	oldPlayerXHit(0),
	oldPlayerYHit(0),
	airRemain(airRemain),
	oldAirRemain(0),
	speed(speed),
	radius(radius),
	width(width),
	height(height),
	stageClear(false) {
	graph = LoadGraph("player.png");
}

void Player::Update(BackGround stage) {
	PlayerInput();
	PlayerRun();
	PlayerHit(stage);
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

	DrawGraph((int)playerX, (int)playerY, graph, 1);
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
	oldPlayerXHit = (int)playerX;
	oldPlayerYHit = (int)playerY;
	if(!airSwich) {
		if(airRemain >= 80) {
			speed = (float)0.5 + (float)(airRemain - 80) * 0.1;
			playerY -= speed;
		}
		else {
			speed = 0.5;
			playerY += speed;
		}
	}


	if(rightSwich) {
		if(flame <= maxFlame) {
			flame++;
			playerX = oldPlayerX + 100 *
				Effect::EaseOutQuart(flame / maxFlame, 5);
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
			playerX = oldPlayerX - 100 *
				Effect::EaseOutQuart(flame / maxFlame, 5);
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

bool Player::CheckFlyStates() {
	return flyStates;
}

void Player::PlayerHit(BackGround stage) {
	for(int i = 0; i < 20; i++) {
		for(int j = 0; j < 200; j++) {
			if(stage.ReturnMap(i, j) == BLOCK) {
				PlayerHitSub(stage, i, j);
			}
			else if(stage.ReturnMap(i, j) == GOAL) {
				if(CheckHit::checkHit((int)playerX,
									  (int)playerY,
									  width,
									  height,
									  stage.ReturnXSize() * i,
									  stage.ReturnYSize() * j,
									  stage.ReturnXSize(),
									  stage.ReturnYSize())) {
					stageClear = true;
				}
			}
		}
	}
}

void Player::PlayerHitSub(BackGround stage, int i, int j) {
	//¶ã‚Ì“–‚½‚è”»’è
	if((int)playerX / stage.ReturnXSize() == i &&
	   (int)playerY / stage.ReturnYSize() == j ) {
		if((int)playerX / stage.ReturnXSize() == i &&
		   (int)oldPlayerYHit / stage.ReturnYSize() == j )
		{
			playerX = oldPlayerXHit;
		}
		else if((int)oldPlayerXHit / stage.ReturnXSize() == i &&
				(int)playerY / stage.ReturnYSize() == j )
		{
			playerY = oldPlayerYHit;
		}
		else
		{
			playerX = oldPlayerXHit;
			playerY = oldPlayerYHit;
		}
	}

	//‰Eã‚Ì“–‚½‚è”»’è
	if(((int)playerX + width) / stage.ReturnXSize() == i &&
	   (int)playerY / stage.ReturnYSize() == j ) {
		if(((int)playerX + width) / stage.ReturnXSize() == i &&
		   (int)oldPlayerYHit / stage.ReturnYSize() == j )
		{
			playerX = oldPlayerXHit;
		}
		else if(((int)oldPlayerXHit + width) / stage.ReturnXSize() == i &&
				(int)playerY / stage.ReturnYSize() == j )
		{
			playerY = oldPlayerYHit;
		}
		else
		{
			playerX = oldPlayerXHit;
			playerY = oldPlayerYHit;
		}
	}

	//¶‰º‚Ì“–‚½‚è”»’è
	if((int)playerX / stage.ReturnXSize() == i &&
	   ((int)playerY + height) / stage.ReturnYSize() == j ) {
		if((int)playerX / stage.ReturnXSize() == i &&
		   ((int)oldPlayerYHit + height) / stage.ReturnYSize() == j )
		{
			playerX = oldPlayerXHit;
		}
		else if((int)oldPlayerXHit / stage.ReturnXSize() == i &&
				((int)playerY + height) / stage.ReturnYSize() == j )
		{
			playerY = oldPlayerYHit;
		}
		else
		{
			playerX = oldPlayerXHit;
			playerY = oldPlayerYHit;
		}
	}

	//‰E‰º‚Ì“–‚½‚è”»’è
	if(((int)playerX + width) / stage.ReturnXSize() == i &&
	   ((int)playerY + height) / stage.ReturnYSize() == j ) {
		if(((int)playerX + width) / stage.ReturnXSize() == i &&
		   ((int)oldPlayerYHit + height) / stage.ReturnYSize() == j )
		{
			playerX = oldPlayerXHit;
		}
		else if(((int)oldPlayerXHit + width) / stage.ReturnXSize() == i &&
				((int)playerY + height) / stage.ReturnYSize() == j )
		{
			playerY = oldPlayerYHit;
		}
		else
		{
			playerX = oldPlayerXHit;
			playerY = oldPlayerYHit;
		}
	}
}

bool Player::IsPlayerAlive() {
	return playerAlive;
}
