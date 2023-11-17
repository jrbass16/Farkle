
#include "player.h"
#include <iostream>

//Function: 	addScore
//
//inputs: 		score
//outputs: 		none
//
//Description:	Updates the players score
void Player::addScore(int score = 0) {
	this->score = this->score + score;
}

//Function: 	playTurn
//
//inputs: 		opponent
//outputs: 		none
//display
//Description:	Walks through a full turn. Rolls a ful cup, 
//				then allows for the player to either roll until they chose to bank or until they get a bust
void Player::playTurn(Player& opponent) {
	int rollScore = 0;
	int turnScore = 0;
	int again;
	myCup.setDiceToPlay(6);//reset it. this is called in case this isn't the first turn
	do {
		again = 0;//set to not repeat
		system("cls");
		std::cout << name << "'s turn. Your current score is " << score << std::endl;
		std::cout << opponent.giveName() << " has " << opponent.giveScore() << " points" << std::endl;
		myCup.rollCup();//roll all the dice in play
		myCup.printDice(myCup, 0);//display
		rollScore = myCup.tallyScore();//returns how many points were earned in that roll
		if (rollScore > 0) {//if it isn't a bust
			std::cout << "You gained " << rollScore << " points!" << std::endl << std::endl;//display points earned
		}
		turnScore += rollScore;//add roll to the total score for this hand
		if (rollScore > 0) {//if the player did not bust
			std::cout << "You can currently bank " << turnScore << " points" << std::endl;
			std::cout << "Would you like to roll again or bank score? (1. Roll again) (0. Bank) ";//prompot to roll again or bank
			std::cin >> again;//set choice to again
			std::cout << std::endl;
			while (!std::cin || again < 0 || again > 1) {//input is not an integer or is out of bounds
				std::cin.clear();
				std::cin.ignore(128, '\n');
				std::cout << "Input ERROR. Please try again:";
				std::cin >> again;
				std::cout << std::endl;
			}
			myCup.checkCup();//resets the dice if all 6 have been kept
		}
	} while (again != 0);//if player decides to roll again: option not given for bust
	if (rollScore == -1) {
		turnScore = 0;
		throw(name);
	}//if a roll was a bust, then no points are gained for this. throw an error
	addScore(turnScore);
}