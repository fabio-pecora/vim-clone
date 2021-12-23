#include <iostream>
#include "Update.h"
#include <string>

using namespace std;

Update::Update() {

}
void Update::setIndex(int index) {
	lineIndex = index;
}
int Update::getIndex() {
	return lineIndex;
}
void Update::setCommand(string command) {
	this->command = command;
}
string Update::getCommand() {
	return this->command;
}

void Update::setLine(string line) {
	this->line = line;
}
string Update::getLine() {
	return this->line;
}
void Update::setPosition(Position pos) {
	this->pos = pos;
}

Position Update::getPosition() {
	return this->pos;
}