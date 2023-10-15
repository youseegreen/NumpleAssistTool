#pragma once

#include<DxLib.h>

namespace My {
	int extern biasX;
	int extern biasY;

	void SetOrigin(int x, int y);
	void DrawBox(int x1, int y1, int x2, int y2, int col, bool frag);
	void DrawLine(int x1, int y1, int x2, int y2, int col,int thick);
	void DrawStringToHandle(int x, int y, const char *str, int col, int font);
}