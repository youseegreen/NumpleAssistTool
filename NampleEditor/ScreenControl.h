#pragma once

struct Point {
	int x; int y;
};

class ScreenControl {
private:
	Point origin;
	Point corner;

public:
	ScreenControl(){}
};