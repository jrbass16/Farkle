#include "Player.h"

void Player::addScore(int score = 0) {
	this->score = this->score + score;
}

void Player::playTurn(Player& opponent) {
	int rollScore = 0;
	int turnScore = 0;
	int again;
	myCup.resetCup(6);//reset it. this is called in case this isn't the first turn
	do {
		again = 0;//set to not repeat
		system("cls");
		cout << name << "'s turn. Your current score is " << score << endl;
		cout << opponent.giveName() << " has " << opponent.giveScore() << " points" << endl;
		myCup.rollCup();//roll all the dice in play
		myCup.printDice(myCup, 0);//display
		rollScore = myCup.tallyScore();//returns how many points were earned in that roll
		if (rollScore > 0) {//if it isn't a bust
			cout << "You gained " << rollScore << " points!" << endl << endl;//display points earned
		}
		turnScore += rollScore;//add roll to the total score for this hand
		if (rollScore > 0) {//if the player did not bust
			cout << "You can currently bank " << turnScore << " points" << endl;
			cout << "Would you like to roll again or bank score? (1. Roll again) (0. Bank) ";//prompot to roll again or bank
			cin >> again;//set choice to again
			cout << endl;
			while (!cin || again < 0 || again > 1) {//input is not an integer or is out of bounds
				cin.clear();
				cin.ignore(128, '\n');
				cout << "Input ERROR. Please try again:";
				cin >> again;
				cout << endl;
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