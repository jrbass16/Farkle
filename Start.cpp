#include "start.h"

//Function: 	startGame
//
//inputs: 		none
//outputs: 		none
//
//Description:	Changes color of terminal, displays menu and waits for input
void startGame() {
	system("color 70");
	std::ifstream inFile;
	std::string newline;
	inFile.open("menuScreen.txt");
	while (getline(inFile, newline)) {
		std::cout << newline << std::endl;
	}
	inFile.close();
	system("pause");
}