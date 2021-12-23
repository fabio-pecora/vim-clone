#include <iostream>
#include "Editor.h"
#include <Windows.h>
using namespace std;



int main(int argc, char * argv[]) {

	Editor editor(argv[1],"Keywords.txt"); //create an instance of editor
	
	editor.run();

	return 0;
}
