#include <iostream>
#include <string>
#include "LinkedStack.h"
#include "Position.h"

using namespace std;

class Update {
private:
	Position pos;
	string command;
	string line;
	int lineIndex;
public:
	Update();
	void setIndex(int);
	int getIndex();
	void setLine(string);
	string getLine();
	void setCommand(string);
	string getCommand();
	void setPosition(Position);
	Position getPosition();


};




#pragma once
