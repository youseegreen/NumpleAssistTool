#pragma once

#include "NumpleDisp.h"

#include <list>
using namespace std;

class NumpleControl {
private:
	list<NumpleDisp *> numList;
	int nowNum;


public:
	NumpleControl(int field[9][9]) {
		numList.push_front(new NumpleDisp(field));
		nowNum = 0;
	}

	void Update() {
		Input::Update();

		auto itr = numList.begin();
		(*itr)->Update();
	}

};