#pragma once
#include <iostream>
#include <Windows.h>

class Position {
private:
	int x;
	int y;



public:
	Position();
	Position(int, int);
	int getX();
	int getY();
	void setX(int);
	void setY(int);
};


#pragma once

