#pragma once

#include <vector>
using namespace std;

class Numple {
protected:
	//ナンプレのフィールド	
	int field[9][9];	//field[行][列]の順番
	bool isDefine[9][9];

	//4隅に書くフィールドとか
	vector<int> FieldRU[9][9];
	vector<int> FieldLU[9][9];
	vector<int> FieldRD[9][9];

	//何列目の何番目の要素的な感じ
	int col[9][9], row[9][9], block[9][9];


public:
	Numple(int input[9][9]) {
		InputData(input);
	}
	
	void InputData(int input[9][9]){
		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				field[x][y] = input[x][y];
				if (input[x][y] != 0)isDefine[x][y] = true;
				else isDefine[x][y] = false;
			}
		}
	}

	virtual void Update(){}

};