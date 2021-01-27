#include "SceneTrans.h"
#include "DxLib.h"
#include <math.h>

extern int WIN_WIDTH;
extern int WIN_HEIGHT;

int SceneTrans::flame = 0;
float SceneTrans::maxflame = 60;

bool SceneTrans::openFlag = false;
bool SceneTrans::closeFlag = false;

bool SceneTrans::errorTrans = false;

double SceneTrans::CircleR = 0;
int SceneTrans::ScreenHandle = MakeScreen(WIN_WIDTH,WIN_HEIGHT,true);

bool SceneTrans::TransO() {
	flame++;
	if(flame <= maxflame) {
		CircleR = sqrt(pow(WIN_WIDTH,2) + pow(WIN_HEIGHT,2))
				  * (flame / maxflame);
		openFlag = true;
		return false;
	}
	else {
		CircleR = 0;
		flame = 0;
		openFlag = false;
		return true;
	}
}

bool SceneTrans::TransC() {
	flame++;
	if(flame <= maxflame) {
		CircleR = sqrt(pow(WIN_WIDTH,2) / 2 + pow(WIN_HEIGHT,2) / 2)
				  * (1.0 - flame / maxflame);
		closeFlag = true;
		return false;
	}
	else {
		flame = 0;
		closeFlag = false;
		return true;
	}
}

void SceneTrans::TransDraw() {
	if(openFlag && closeFlag) {
		errorTrans = true;
	}
	else if(openFlag) {
		SetDrawScreen(ScreenHandle);
		
		DrawBox(0, 0,
				WIN_WIDTH, WIN_HEIGHT,
				GetColor(0, 0, 0), true);

		//blend mode変更(add)
		SetDrawBlendMode(DX_BLENDMODE_SRCCOLOR,0);
		DrawCircle(WIN_WIDTH / 2,WIN_HEIGHT / 2,
				   (int)CircleR,
				   GetColor(0,0,0));

		//blend mode変更(no blend)
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);
		SetDrawScreen(DX_SCREEN_BACK);
	}
	else if(closeFlag) {
		SetDrawScreen(ScreenHandle);
		
		DrawBox(0, 0,
				WIN_WIDTH, WIN_HEIGHT,
				GetColor(0, 0, 0), true);

		//blend mode変更()
		SetDrawBlendMode(DX_BLENDMODE_SRCCOLOR,0);
		DrawCircle(WIN_WIDTH / 2,WIN_HEIGHT / 2,
				   (int)CircleR,
				   GetColor(0,0,0));

		//blend mode変更(no blend)
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);
		SetDrawScreen(DX_SCREEN_BACK);
	}
}

bool SceneTrans::ReturnError() {
	return errorTrans;
}

