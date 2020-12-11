#pragma once

class Easing {
private:
	Easing();
public:
	static double EaseIn(double x, int y);
	static double EaseOut(double x, int y);
};
