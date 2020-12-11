#include "Easing.h"
#include "math.h"

double Easing::EaseIn(double x, int y) {
	return pow(x,y);
}

double Easing::EaseOut(double x,int y) {
	return 1 - pow((1 - x), y);
}
