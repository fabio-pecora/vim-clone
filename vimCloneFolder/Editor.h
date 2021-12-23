
#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include <string>
#include <Windows.h>
#include "Position.h"
#include "Update.h"
#include "LinkedStack.h"
#include "BinarySearchTree.h"
using namespace std;

class Editor {
private:
	LinkedStack <Update> updateLines;
	LinkedList <string> lines; // created an instance of LinkedList 
	Position point;
	string filename;
	void moveDown();
	void moveUp();
	void moveLeft();
	void moveRight();
	bool change; // depends on the user change
	//string keyWordsArray[120];
	BinarySearchTree <string> keyWordTree;
	int numKeyWords;
public:
	Editor(string filename, string key);
	void run();
	void displayLines();

};