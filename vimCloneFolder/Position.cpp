#include <iostream>
#include "Position.h"

using namespace std;

Position::Position() {
	x = 0;
	y = 0;
}
Position::Position(int x, int y) {
	this->x = x;
	this->y = y;
}

int Position::getX() {
	return x;
}

int Position::getY() {
	return y;
}

void Position::setX(int xPos) {
	x = xPos;
}

void Position::setY(int yPos) {
	y = yPos;
}