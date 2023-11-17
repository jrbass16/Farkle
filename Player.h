#pragma once
#include "cup.h"
#include <string>

class Player {
private:
	int score;//keeps track of the score
	std::string name;
public:
	Cup myCup;//the player's cup of dice
	void playTurn(Player& opponent); //plays a turn, input purely for display purposes
	void addScore(int);
	int giveScore() { return score; }
	std::string giveName() { return name; }
	Player(std::string n) { score = 0; name = n; }//when a new player is created, set the score to 0
};