#include "FieldManager.h"

int main() {

	SetGraphMode(1000, 1000, 16);
	if (DxLib_Init() == -1)	return -1;// ＤＸライブラリ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);


	int data[9][9] = {
	{ 0,3,0,8,7,0,0,0,5 },
	{ 8,0,0,2,0,5,9,0,0 },
	{ 0,9,0,0,0,0,0,0,8 },
	{ 2,0,0,5,0,4,7,0,6 },
	{ 0,0,9,6,0,0,0,0,0 },
	{ 0,0,1,7,0,0,0,5,2 },
	{ 0,0,0,0,2,0,0,0,1 },
	{ 0,1,6,0,5,0,0,8,0 },
	{ 0,0,0,1,0,0,0,3,0 },
	};

	FieldManager numple(100);
	numple.LoadMap("tmp.csv");
//	numple.SetData(data);



	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面を初期化
		ClearDrawScreen();

		numple.Update();

		// 裏画面の内容を表画面に映す
		ScreenFlip();
	}
	DxLib_End();				// ＤＸライブラリ使用の終了処理


	return 1;
}