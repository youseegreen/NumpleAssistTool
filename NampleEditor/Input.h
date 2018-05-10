#pragma once

#include <DxLib.h>


class Input {
private:
	static char now[256];
	static char prev[256];
	static char isDown[256];

public:
	static void Update();
	static bool GetKeyDown(int num);
	static bool GetKey(int num);
};