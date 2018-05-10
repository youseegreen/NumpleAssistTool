#pragma once

#include "Numple.h"
#include "ScreenControl.h"
#include "Input.h"
#include <DxLib.h>

class NumpleDisp :public Numple{
private:
	ScreenControl screen;
	Point nowPos;
	int fontBig[2];
	int fontSmall;


public:
	NumpleDisp(int field[9][9]) :Numple(field) {
		nowPos.x = 0;
		nowPos.y = 0;
		fontBig[0] = CreateFontToHandle(NULL,8);
	}

	void Update() {
		//GetInput();Å®
		//Numple::Update(inputor);
		DrawScreen();
	}

private:
	void DrawScreen() {

		DrawBox(0, 0, 90, 90, GetColor(255, 255, 255), TRUE);
		for (int y = 0; y <= 9; y++) {
			if ((y % 3) == 0)DrawLine(0, y * 10, 90, y * 10, GetColor(0, 0, 0),2);
			else DrawLine(0, y * 10, 90, y * 10, GetColor(0, 0, 0));
		}
		for (int x = 0; x <= 9; x++) {
			if ((x % 3) == 0)DrawLine(x * 10, 0, x * 10, 90, GetColor(0, 0, 0),2);
			else DrawLine(x * 10, 0, x * 10, 90, GetColor(0, 0, 0));
		}

		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				if (field[x][y] != 0) {
					char tmp = (char)field[x][y];
					DrawFormatString(y*10,x*10,GetColor(0,0,0),);
				}
			}
		}
	}

};