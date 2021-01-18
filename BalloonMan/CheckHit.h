#pragma once

class CheckHit {
private:
	CheckHit();
public:
	static bool checkHit(int x1, int y1, int h1, int w1, int x2, int y2, int h2, int w2);
};
