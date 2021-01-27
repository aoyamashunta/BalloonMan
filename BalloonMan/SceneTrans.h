#pragma once

class SceneTrans {
private:
	SceneTrans();
	static int flame;
	static float maxflame;

	static bool openFlag;
	static bool closeFlag;

	static bool errorTrans;

	static double CircleR;
	static int ScreenHandle;

public:
	static bool TransO();
	static bool TransC();

	static void TransDraw();
	static bool ReturnError();
};
