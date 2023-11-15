#include "Start.h"

void startGame() {
	system("color 70");//changes the color. The system command is the new thing in C that we haven't done in class
	//it puts into the system command line whatever the string inputted to it is
	ifstream inFile;
	string newline;
	inFile.open("menuScreen.txt"); //open file with the screen in it
	while (getline(inFile, newline)) {
		cout << newline << endl;
	}
	inFile.close();
	system("pause");
}