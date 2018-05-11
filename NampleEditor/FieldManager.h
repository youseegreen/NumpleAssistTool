#pragma once

#include "OneCell.h"
#include <queue>
#include<stdio.h>

class FieldManager {
private:
	int cellSize;
	int blackFont;
	Point nowPos;
	OneCell cell[9][9];
	int activeNum;
	bool dispFrag;
	int fontColor;

public:
	FieldManager(int size = 100) {
		cellSize = size;
		blackFont = CreateFontToHandle(NULL, cellSize / 2, 5);
		fontColor = 0;
		activeNum = 0;
		dispFrag = false;
		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				cell[x][y].SetSize(size);
			}
		}
	}

	void SetData(int input[9][9]) {
		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				cell[x][y].data = input[x][y];
				if (input[x][y] != 0)cell[x][y].isDefine = true;
			}
		}
		FindAvailableNum();
	}

	void Update() {
		Input::Update();
		if (Input::GetKeyDown(KEY_INPUT_LEFT) && (nowPos.x != 0))nowPos.x -= 1;
		if (Input::GetKeyDown(KEY_INPUT_RIGHT) && (nowPos.x != 8))nowPos.x += 1;
		if (Input::GetKeyDown(KEY_INPUT_UP) && (nowPos.y != 0))nowPos.y -= 1;
		if (Input::GetKeyDown(KEY_INPUT_DOWN) && (nowPos.y != 8))nowPos.y += 1;
		if (Input::GetKeyDown(KEY_INPUT_SPACE))dispFrag = !dispFrag;
		if (Input::GetKeyDown(KEY_INPUT_C)) { fontColor = (fontColor + 1) % 4; }	//この辺
		if (cell[(int)nowPos.x][(int)nowPos.y].Update()) {
			FindAvailableNum();	//dataLDに行ける数をセット
			cell[(int)nowPos.x][(int)nowPos.y].SetFontColor(fontColor);
		}

		if (Input::GetKeyDown(KEY_INPUT_0))activeNum = 0;
		if (Input::GetKeyDown(KEY_INPUT_1))activeNum = (activeNum == 1) ? 0 : 1;
		if (Input::GetKeyDown(KEY_INPUT_2))activeNum = (activeNum == 2) ? 0 : 2;
		if (Input::GetKeyDown(KEY_INPUT_3))activeNum = (activeNum == 3) ? 0 : 3;
		if (Input::GetKeyDown(KEY_INPUT_4))activeNum = (activeNum == 4) ? 0 : 4;
		if (Input::GetKeyDown(KEY_INPUT_5))activeNum = (activeNum == 5) ? 0 : 5;
		if (Input::GetKeyDown(KEY_INPUT_6))activeNum = (activeNum == 6) ? 0 : 6;
		if (Input::GetKeyDown(KEY_INPUT_7))activeNum = (activeNum == 7) ? 0 : 7;
		if (Input::GetKeyDown(KEY_INPUT_8))activeNum = (activeNum == 8) ? 0 : 8;
		if (Input::GetKeyDown(KEY_INPUT_9))activeNum = (activeNum == 9) ? 0 : 9;
		FindActiveCell(activeNum);
		if (Input::GetKey(KEY_INPUT_P)) CheckField();

		DrawScreen();
	}

    void LoadMap_RowWithComma(const char *fName) {
		FILE *fp;
	//	fp = fopen(fName, "r");
		if (fp == NULL)return;
		int data[9][9] = { 0 };
		int x = 0, y = 0;
		for (int i = 0; i < 81; i++) {
			fscanf_s(fp, "%d,",&(data[x][y]));
			x++;
			if (x == 9) {
				x = 0;
				y++;
			}
		}
		SetData(data);
	}

	void LoadMap_RowWithOutComma(const char *fName) {
		FILE *fp;
		fopen_s(&fp,fName, "r");
		if (fp == NULL)return;
		char tmp[9][9] = { 0 };
		int data[9][9] = { 0 };
		int x = 0, y = 0;
		for (int i = 0; i < 81; i++) {
			fread(&(tmp[x][y]), 1, 1, fp);
			tmp[x][y] -= '0';
			x++;
			if (x == 9) {
				x = 0;
				y++;
			}
		}
		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				data[x][y] = (int)tmp[x][y];
			}
		}
		SetData(data);
	}

private:
	void DrawScreen() {
		//左側に適当にボタンはやす
		My::SetOrigin(0, 50);

		//ボタン表示
		for (int y = 0; y < 9; y++) {
			int col = (activeNum == (y + 1)) ? GetColor(255, 128, 128) : GetColor(255, 255, 255);
			My::DrawBox(0, y * 100 + 12, 75, y * 100 + 87, col, true);
			My::DrawStringToHandle(cellSize * 2 / 8, y*100 + cellSize / 4, std::to_string(y+1).c_str(), GetColor(0, 0, 0), blackFont);
		}



		My::SetOrigin(100, 50);

		//注目セル表示
		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				cell[x][y].DrawScreen(x* cellSize, y* cellSize, dispFrag);
			}
		}

		//枠線
		for (int y = 0; y <= 9 * cellSize; y += cellSize) {
			if ((y % 3) == 0)My::DrawLine(0, y, 9 * cellSize, y, GetColor(0, 0, 0), 2);
			else My::DrawLine(0, y, 9 * cellSize, y, GetColor(0, 0, 0), 1);
		}
		for (int x = 0; x <= 9 * cellSize; x += cellSize) {
			if ((x % 3) == 0)My::DrawLine(x, 0, x, 9 * cellSize, GetColor(0, 0, 0), 2);
			else My::DrawLine(x, 0, x, 9 * cellSize, GetColor(0, 0, 0), 1);
		}


		My::DrawBox(nowPos.x * cellSize, nowPos.y*cellSize, (nowPos.x + 1)*cellSize,
			(nowPos.y + 1)*cellSize, GetColor(255, 0, 0), FALSE);
	}

	void CheckField() {
		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				cell[x][y].SetBackColor(GetColor(255, 255, 255));
			}
		}

		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				int num = cell[x][y].data;
				for (int i = 0; i < 9; i++) {
					if (i == y)continue;
					if (cell[x][i].data == num)cell[x][y].SetBackColor(GetColor(255, 255, 128));
				}
				for (int i = 0; i < 9; i++) {
					if (i == x)continue;
					if (cell[i][y].data == num)cell[x][y].SetBackColor(GetColor(255, 255, 128));
				}
				//ブロック方向探索
				int u = x / 3;
				int v = y / 3;
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						if (((u * 3 + i) == x) && ((v * 3 + j)==y))continue;
						if (cell[u * 3 + i][v * 3 + j].data == num)cell[x][y].SetBackColor(GetColor(255, 255, 128));//ブロック内の同じ数を記録	
					}
				}
			}
		}
	}

	void FindActiveCell(int num) {
		//背景初期化
		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				cell[x][y].SetBackColor(GetColor(255,255,255));
			}
		}
		if (num == 0)return;

		//activeのとこだけ色変える
		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				if(cell[x][y].dataLD[num - 1])cell[x][y].SetBackColor(GetColor(128, 128, 255));
			}
		}
	}


	void FindAvailableNum() {

		for (int num = 1; num <= 9; num++) {
			bool active[9][9] = { false };
			for (int y = 0; y < 9; y++) {
				for (int x = 0; x < 9; x++) {
					if (cell[x][y].data != 0)active[x][y] = true;

					if (cell[x][y].data == num) {
						for (int i = 0; i < 9; i++) {
							active[x][i] = true;
							active[i][y] = true;
						}
						int u = x / 3;
						int v = y / 3;
						for (int i = 0; i < 3; i++) {
							for (int j = 0; j < 3; j++) {
								active[u * 3 + i][v * 3 + j] = true;
							}
						}
					}
				}
			}

			//右上も有効にする
			for (int y = 0; y < 9; y++) {
				for (int x = 0; x < 9; x++) {
					if (cell[x][y].dataRU[num-1]) {	//num-1がx,yに入る可能性がある
						//相方のnum-1を探す
						//縦方向探索		
						int frag = 0;
						for (int i = 0; i < 9; i++) {
							if (cell[x][i].dataRU[num - 1]&&(cell[x][i].data==0))frag++;	//縦方向の同じ数を記録							
						}
						if (frag == 2) {	//縦方向に2個の場合だけ
							for (int i = 0; i < 9; i++) {
								if (!cell[x][i].dataRU[num-1])active[x][i] = true; //それ以外の縦方向を削除							
							}
						}
						//横方向探索
						frag = 0;
						for (int i = 0; i < 9; i++) {
							if (cell[i][y].dataRU[num-1] && (cell[i][y].data == 0))frag++;	//横方向の同じ数を記録							
						}
						if (frag == 2) {	//横方向に2個の場合だけ
							for (int i = 0; i < 9; i++) {
								if (!cell[i][y].dataRU[num-1])active[i][y] = true; //それ以外の横方向を削除							
							}
						}
						//ブロック方向探索
						frag = 0;
						int u = x / 3;
						int v = y / 3;
						for (int i = 0; i < 3; i++) {
							for (int j = 0; j < 3; j++) {
								if (cell[u * 3 + i][v * 3 + j].dataRU[num-1] && (cell[u * 3 + i][v * 3 + j].data == 0))frag++;	//ブロック内の同じ数を記録	
							}
						}
						if (frag == 2) {	//ブロック内に2個の時だけ
							for (int i = 0; i < 3; i++) {
								for (int j = 0; j < 3; j++) {
									if (!cell[u * 3 + i][v * 3 + j].dataRU[num-1])active[u * 3 + i][v * 3 + j] = true;	
								}
							}
						}
					}
				}
			}




			for (int y = 0; y < 9; y++) {
				for (int x = 0; x < 9; x++) {
					if (!active[x][y])cell[x][y].dataLD[num - 1] = true;
					else cell[x][y].dataLD[num - 1] = false;
				}
			}
		}
	}
};