#include <iostream>
#include <fstream>
#include <conio.h>
#include "Editor.h"
#include "Position.h"
#include "Node.h"

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80

void colorText(int value) {

    COORD coord;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    FlushConsoleInputBuffer(hConsole);

    SetConsoleTextAttribute(hConsole, value + 240);

}

void placeCursorAt(Position coordinate) {                     
    COORD coord;

    coord.X = coordinate.getX();
    coord.Y = coordinate.getY();

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord);
}

Editor::Editor(string fileName, string key) {

    ifstream inFile;
    ifstream keyFile;
    inFile.open(fileName);
    keyFile.open(key);

    string newLine;

    int startingPosition = 0;
    this->numKeyWords = 0;
    while (!inFile.eof()) {
        startingPosition++;
        getline(inFile, newLine);
        lines.insert(startingPosition, newLine);
    }
    while (!keyFile.eof()) {
        getline(keyFile, newLine);        
        keyWordTree.add(newLine);
    }
    change = false;
}

void Editor::moveDown() {
    int end = lines.getLength() - 1;
    if (point.getY() == end) return;
    string nextLine = lines.getEntry(this->point.getY() + 2);           // get the string of the next node
    int lengthOfNextLine = nextLine.length();                           // get the number of character in the string of our next node
    if (point.getX() <= lengthOfNextLine) {
        this->point.setY(this->point.getY() + 1);
        placeCursorAt(this->point);
    }
    else {
        this->point.setY(this->point.getY() + 1);                   // the cursor go in the next line
        this->point.setX(lengthOfNextLine);                         // the x will be moved at the end of the string
        placeCursorAt(this->point);                                 // place the cursor in that position
    }
}

void Editor::moveUp() {
    if (this->point.getY() == 0) return;
    string previousLine = lines.getEntry(this->point.getY());
    int lengthOfPreviousLine = previousLine.length();
    if (this->point.getY() != 0) {
        if (point.getX() <= lengthOfPreviousLine) {
            this->point.setY(this->point.getY() - 1);
            placeCursorAt(this->point);
        }
        else {
            this->point.setY(this->point.getY() - 1);
            this->point.setX(lengthOfPreviousLine);
            placeCursorAt(this->point);
        }
    }
}

void Editor::moveLeft() {
    if (this->point.getX() != 0) {
        this->point.setX(this->point.getX() - 1);
        placeCursorAt(this->point);
    }
}

void Editor::moveRight() {
    Node <string> node = lines.getEntry(this->point.getY() + 1);
    string currentLine = node.getItem();
    int max = currentLine.length();

    if (this->point.getX() < max) {
        this->point.setX(this->point.getX() + 1);
        placeCursorAt(this->point);
    }

}
void Editor::run() {
    char c;
    string currentLine;
    int endOfScreen = lines.getLength() + 1;
    Position bottom(0, endOfScreen);
    char command;
    Update update; 
    Update prevUpdate;
    Position prevPos;
    string prevLine;
    string prevCommand;
    //Node <string>* choseNode = lines;
    displayLines();

    // placeCursorAt(point);
    while (c = _getwch()) {
        switch (c) {
        case 'j': case KEY_DOWN:
            moveDown();
            break;
        case 'k':case KEY_UP:
            moveUp();
            break;
        case 'd':
            command = _getwch();
            if (command == 'd') {
                change = true;
                /*
                * create update object and push to stack
                * update.setCommand(command)
                */
                currentLine = lines.getEntry(point.getY() + 1);
                update.setCommand("d");
                update.setLine(currentLine);
                update.setPosition(point);
                updateLines.push(update);
                lines.remove(point.getY() + 1);
                displayLines();
            }
            break;
        case 'h':  case KEY_LEFT:
            moveLeft();
            break;
        case 'l': case KEY_RIGHT:
            moveRight();
            break;
        case 'x':
            currentLine = lines.getEntry(point.getY() + 1);			//Stores copy of string using getEntry to get the line in the file
            update.setLine(currentLine);
            update.setPosition(point);
            update.setCommand("x");
            this->updateLines.push(update);
            currentLine.erase(point.getX(), 1);						//Deletes the character at cursor position (x)

            lines.replace(point.getY() + 1, currentLine);			//replace function to replace the line
            change = true;
            displayLines();

            break;
        case 'u':
            if (updateLines.isEmpty()) break;
            else {
                prevUpdate = this->updateLines.peek();
                prevPos = prevUpdate.getPosition();
                placeCursorAt(prevPos);
                prevLine = prevUpdate.getLine();

                prevCommand = prevUpdate.getCommand();
                if (prevCommand == "d") {
                    this->lines.insert(prevPos.getY() + 1, prevLine);
                }
                else {
                    lines.replace(prevPos.getY() + 1, prevLine);
                }
                displayLines();
                this->updateLines.pop();
                break;
            }
        case ':':
            placeCursorAt(Position(bottom));
            cout << ':';
            command = _getwche();
            if (command == 'q') {
                if (!change) {
                    exit(1);
                }
                else {
                    cout << "Were there any changes made? If you really want to quit enter '!'" << endl;
                    command = _getwche();
                    if (command == '!') {                       // command to quit the vi
                        exit(1);
                    }
                    else {
                        placeCursorAt(point);
                    }
                }
            }
            else if (command == 'w') {                         // command to write the new file
                ofstream oFile;
                oFile.open("myInput.txt", ofstream::out);
                for (int i = 1; i <= lines.getLength(); i++)
                    oFile << lines.getEntry(i) << endl;
                oFile.close();
            }
            break;
        }
    }
}

void Editor::displayLines() {
    int position;
    string nextLine;
    system("CLS");
    for (position = 1; position <= lines.getLength(); position++){
        nextLine = lines.getEntry(position);
        int i = 0;
        while (i < nextLine.length()) {
            string word;
           
            // isolate a word at a time (can contain underscores)
            if (isalpha(nextLine[i])) {
                while (isalpha(nextLine[i]) || nextLine[i] == '_') {
                    word += nextLine[i];
                    i++;
                }
                if (keyWordTree.contains(word))  //found
                    colorText(1);
                else
                    colorText(0);
                cout << word;
            }
            else {
                colorText(0);
                cout << nextLine[i];
                i++;
            }

        }
        cout << endl;
    }
    placeCursorAt(point);
}