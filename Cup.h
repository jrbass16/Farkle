#pragma once
#include "dice.h"
#include <iostream>

class Cup {
private:
	int rollScore;
public:
	int i;//moving the << overload to dice would also get rid of this awkward public int
	Dice dice[6];//farkle has 6 dice	
	int diceInPlay();
	void setScore(int n) { rollScore = n; }
	int tallyScore(); //Checks for melds, prompts user which to keep and returns the score of what they kept
	void checkCup(); //Checks if all dice have been kept and if they have, resets them
	void setDiceToPlay(int); //Used to set how many dice should be in play (notKept)
	friend std::ostream& operator<<(std::ostream&, Cup&);
	void printDice(Cup&, int);
	void rollCup();
};
