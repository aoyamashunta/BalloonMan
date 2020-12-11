#include "Effect.h"
#include "math.h"

double Effect::EaseIn(double x, int y) {
	return pow(x,y);
}

double Effect::EaseOut(double x,int y) {
	return 1 - pow((1 - x), y);
}
