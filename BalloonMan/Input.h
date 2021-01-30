#pragma once

class Input
{
private:
	static char keys[256];
	static char oldkeys[256];

public:
	static void Update();

	static bool isKey(int key);

	static bool isKeyTrigger(int key);
};