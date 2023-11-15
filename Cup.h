#pragma once
#include "Dice.h"//needs dice for composition
#include <iostream>
#include <string>

using namespace std;

class Cup {
private:
	int rollScore;
public:
	int i;
	Dice dice[6];//farkle has 6 dice	
	void setScore(int n) { rollScore = n; }
	int tallyScore(); // Finds and returns the score of the hand
	void checkCup();//just checks if all dice have been used and if they have, resets them
	void resetCup();//called between turns to set it back to essentially a starting state of no kept dice 
	friend ostream& operator<<(ostream&, Cup&);
	void printDice(Cup&, int); // Could also have a 'table' where the die are scattered before they are ordered below
	void rollCup();
};

/*
int Cup::tallyScore();
void Cup::checkCup();
void Cup::resetCup();
ostream& operator<<(ostream& os, Cup& cup);
void Cup::printDice(Cup& cup, int i = 0);
void Cup::rollCup();*/
