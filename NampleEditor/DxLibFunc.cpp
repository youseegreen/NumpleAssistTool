#include "DxLibFunc.h"

int My::biasX = 0;
int My::biasY = 0;

void My::SetOrigin(int x, int y) { biasX = x; biasY = y; }
void My::DrawBox(int x1, int y1, int x2, int y2, int col, bool frag) {
	DxLib::DrawBox(x1 + biasX, y1 + biasY, x2 + biasX, y2 + biasY, col, frag);
}

void My::DrawLine(int x1, int y1, int x2, int y2, int col, int thick) {
	DxLib::DrawLine(x1 + biasX, y1 + biasY, x2 + biasX, y2 + biasY, col, thick);
}
void My::DrawStringToHandle(int x, int y, const char *str, int col, int font) {
	DxLib::DrawStringToHandle(x + biasX, y + biasY, str, col, font);
}