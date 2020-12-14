#pragma once

class Effect {
private:
	Effect();
public:
	static double EaseIn(double x, int y);
	static double EaseOut(double x, int y);
	static double EaseOutQuart(double x, int y);
};
