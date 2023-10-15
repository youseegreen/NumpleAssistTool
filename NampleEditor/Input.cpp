#include "Input.h"

char Input::now[256] = { 0 };
char Input::isDown[256] = { 0 };
char Input::prev[256] = { 0 };

void Input::Update() {
	GetHitKeyStateAll(now);
	for (int i = 0; i < 256; i++) {
		if ((now[i] == 1) && (prev[i]!= 1))isDown[i] = 1;
		else isDown[i] = 0;
	}
	for (int i = 0; i < 256; i++) {
		prev[i] = now[i];
	}
}

bool Input::GetKeyDown(int num) {
	return (isDown[num] == 1) ? true : false;
}
bool Input::GetKey(int num) {
	return (now[num] == 1) ? true : false;
}