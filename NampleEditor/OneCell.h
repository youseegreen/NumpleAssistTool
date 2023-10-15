#pragma once

#include "Input.h"
#include "DxLibFunc.h"
#include <list>
#include <string>
using namespace std;

struct Point { float x; float y; };


class OneCell {
private:
	static int fontB;	//ビッグサイズ
	static int fontD;	//ビッグサイズの太文字
	static int fontS;	//スモールサイズ
	static int cellSize;
	int backColor;
	int fontColor;

	void ClearRU() {
	//	for (int i = 0; i < 9; i++)dataRU[i] = false;
	}

public:
	int data;
	bool isDefine;
	bool dataRU[9];
	bool dataRD[9];
	bool dataLU[9];
	bool dataLD[9];	//隠しコマンド

public:
	OneCell() {
		isDefine = false;
		data = 0;
		for (int i = 0; i < 9; i++) {
			dataRD[i] = false;
			dataLU[i] = false;
			dataRU[i] = false;
			dataLD[i] = false;
		}
		backColor = GetColor(255, 255, 255);
		fontColor = GetColor(0, 0, 0);
	}

	static void SetSize(int i) { 
		cellSize = i; 
		DeleteFontToHandle(fontB);
		DeleteFontToHandle(fontD);
		DeleteFontToHandle(fontS);
		fontB = CreateFontToHandle(NULL, cellSize / 2, 1);
		fontD = CreateFontToHandle(NULL, cellSize / 2, 5);
		fontS = CreateFontToHandle(NULL, cellSize / 5, 1);
	}

	//dataに変化あればtrue
	bool Update() {
		if (Input::GetKey(KEY_INPUT_Q)) {
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD1))dataLU[0] = !dataLU[0];
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD2))dataLU[1] = !dataLU[1];
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD3))dataLU[2] = !dataLU[2];
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD4))dataLU[3] = !dataLU[3];
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD5))dataLU[4] = !dataLU[4];
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD6))dataLU[5] = !dataLU[5];
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD7))dataLU[6] = !dataLU[6];
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD8))dataLU[7] = !dataLU[7];
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD9))dataLU[8] = !dataLU[8];
		}
		else if (Input::GetKey(KEY_INPUT_W)) {
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD1)) { dataRU[0] = !dataRU[0]; return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD2)) { dataRU[1] = !dataRU[1]; return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD3)) { dataRU[2] = !dataRU[2]; return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD4)) { dataRU[3] = !dataRU[3]; return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD5)) { dataRU[4] = !dataRU[4]; return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD6)) { dataRU[5] = !dataRU[5]; return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD7)) { dataRU[6] = !dataRU[6]; return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD8)) { dataRU[7] = !dataRU[7]; return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD9)) { dataRU[8] = !dataRU[8]; return true; }
		}
		else if (Input::GetKey(KEY_INPUT_S)) {
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD1))dataRD[0] = !dataRD[0];
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD2))dataRD[1] = !dataRD[1];
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD3))dataRD[2] = !dataRD[2];
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD4))dataRD[3] = !dataRD[3];
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD5))dataRD[4] = !dataRD[4];
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD6))dataRD[5] = !dataRD[5];
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD7))dataRD[6] = !dataRD[6];
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD8))dataRD[7] = !dataRD[7];
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD9))dataRD[8] = !dataRD[8];
		}
		else {
			if (isDefine)return false;
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD0)) { data = 0; ClearRU(); return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD1)) { data = 1; ClearRU(); return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD2)) { data = 2; ClearRU(); return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD3)) { data = 3; ClearRU(); return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD4)) { data = 4; ClearRU(); return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD5)) { data = 5; ClearRU(); return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD6)) { data = 6; ClearRU(); return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD7)) { data = 7; ClearRU(); return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD8)) { data = 8; ClearRU(); return true; }
			if (Input::GetKeyDown(KEY_INPUT_NUMPAD9)) { data = 9; ClearRU(); return true; }
		}
		return false;
	}

	void SetFontColor(int num) {
		if (num == 0)fontColor = GetColor(100, 100, 100);
		else if (num == 1)fontColor = GetColor(250, 100, 100);
		else if (num == 2)fontColor = GetColor(100, 250, 100);
		else fontColor = GetColor(100, 100, 250);
	}

	void SetBackColor(int col) {
		backColor = col;
	}

	void DrawScreen(int x,int y, bool disp = false) {
		//呼ぶ側(FieldManager)が原点指定してるからそれ使う
		string str;

		My::DrawBox(x, y, x + cellSize, y + cellSize, backColor, TRUE);

		if (data != 0) {	
			string str = to_string(data);
			if(isDefine)My::DrawStringToHandle(x + cellSize * 3 / 8, y + cellSize / 4, str.c_str(), GetColor(0, 0, 0), fontD);
			else My::DrawStringToHandle(x + cellSize * 3 / 8, y + cellSize / 4, str.c_str(), fontColor, fontB);
		}
		else {
			string strRU;
			string strRD;
			string strLU;
			string strLD;
			for (int i = 0; i < 9; i++) {
				if (dataRD[i])strRD += to_string(i+1);
				if (strRD.size() == 5)strRD += '\n';
				if (dataRU[i])strRU += to_string(i+1);
				if (strRU.size() == 5)strRU += '\n';
				if (dataLU[i])strLU += to_string(i+1);
				if (strLU.size() == 4)strLU += '\n';
				if (dataLD[i])strLD += to_string(i + 1);
				if (strLD.size() == 4)strLD += '\n';
			}
			My::DrawStringToHandle(x + cellSize / 2, y + cellSize/50, strRU.c_str(), GetColor(100, 100, 100), fontS);
			if (strRD.size() > 6)My::DrawStringToHandle(x + cellSize / 2, y + cellSize * 3 / 5, strRD.c_str(), GetColor(100, 100, 100), fontS);
			else My::DrawStringToHandle(x + cellSize / 2, y + cellSize * 4/ 5, strRD.c_str(), GetColor(100, 100, 100), fontS);
			My::DrawStringToHandle(x + cellSize / 50, y + cellSize / 50, strLU.c_str(), GetColor(100, 100, 100), fontS);

			if (disp) {
				if (strLD.size() > 6)My::DrawStringToHandle(x + cellSize / 50, y + cellSize * 3 / 5, strLD.c_str(), GetColor(100, 100, 100), fontS);
				else My::DrawStringToHandle(x + cellSize / 50, y + cellSize * 4 / 5, strLD.c_str(), GetColor(100, 100, 100), fontS);
			}
		}
	}
};