#include "cup.h"
#include "melds.h"
#include <algorithm>
#include <iostream>
#include <vector>


//this should really be an overload in the dice to display the dice
std::ostream& operator<<(std::ostream& os, Cup& cup) {
	os << "|" << cup.dice[cup.i].getSide() << "| ";
	return os;
}

//Function: 	printDice
//
//inputs: 		cup, integer for some odd reason
//outputs: 		none
//
//Description:	Displays the dice in the current roll both in a format as though they were scattered
//				across a table and then neatly organized for the player
void Cup::printDice(Cup& cup, int i = 0) {
	std::cout << std::endl << std::endl;
	//Print Table
	std::cout << "  _____________________________________________________";
	std::cout << std::endl << std::endl;
	cup.i = 0;
	//clean this up. Make r a bucket of 6 randoms generated once, then just use each index
	for (int a = 0; a < 6; a++) {
		std::cout << "  |";
		int r = rand() % 24;
		for (int b = 0; b < 24; b++) {
			std::cout << " ";
			if (b == r) {
				if (cup.dice[cup.i].isKept() == false) {
					std::cout << cup;
				}
				else {
					std::cout << "    ";
				}
				cup.i++;

			}
			std::cout << " ";
		}
		//std::cout << "                                                ";	
		std::cout << "|";
		std::cout << std::endl;
	}
	std::cout << "  _____________________________________________________";
	std::cout << std::endl << std::endl << std::endl;;
	//Print ordered
	cup.i = 0;
	std::cout << "Here are the dice in play organized: ";
	while (cup.i < 6) {
		if (cup.dice[cup.i].isKept() == false) {
			std::cout << cup;
		}
		cup.i++;
	}
	std::cout << std::endl << std::endl;
}

//Function: 	resetCup
//
//inputs: 		int diceForNextRoll
//outputs: 		none
//
//Description:	un-keeps the number of dice needed for the next roll
void Cup::setDiceToPlay(int diceForNextRoll) {
	//std::cout << diceForNextRoll <<" dice in play" <<std::endl;//debug statement
	for (int i = 0; i < 6; i++) {//for each dice up to the number being called
	//std::cout<<i;
	//sets the status of each dice according to whether its index is above or below how many dice are needed
	dice[i].setKept(!(i<diceForNextRoll));
	//std::cout << "Dice "<< i<< " is " << (dice[i].isKept()?"Kept":"NotKept") << std::endl;
	}
}

//Function: 	checkCup
//
//inputs: 		none
//outputs: 		none
//
//Description:	Checks whether all 6 dice in the cup are kept. If they are, resets all of them
void Cup::checkCup() {
	int count = 0;
	bool reset = false;
	for (int i = 0; i < 6; i++) {//for each dice
		if (dice[i].isKept() == true) {//if it has been kept
			count += 1;//count it
		}
	}//once all are counted
	if (count == 6) {//if all 6 dice are kept
		//reset them to put them back into play
		setDiceToPlay(6);
	}
}

//Function: 	tallyScore
//
//inputs: 		none
//outputs: 		int pointReturn
//
//Description:	looks through the dice in play (not kept) and checks for any present melds
//				then prompts the user on whether they would like to select one or more of these melds.
//				resets the number of dice kept for all melds, then returns the point total
int Cup::tallyScore() {
	Meld run("Full run!","run", 2500, 6);
	Meld _3pairs("Three pairs!","3pairs", 1500, 6);
	Meld _6oK("Six of a kind!","6ok",3000, 6);
	Meld _5oK("Five of a kind!","5ok", 2000, 5);
	Meld _4oK("Four of a kind!","4ok", 1000, 4);
	Meld _3six("Triple 6!","3six", 600, 3);
	Meld _3five("Triple 5!","3five", 500, 3);
	Meld _3four("Triple 4!","3four", 400, 3);
	Meld _3three("Triple 3!","3three",300, 3);
	Meld _3two("Triple 2!","3two", 200, 3);
	Meld _3one("Triple 1!","3one",1000, 3);
	Meld _5s("5s!","5s", 50, 0);
	Meld _1s("1s!","1s", 100, 0);
	Meld curMeld("Inactive", "NULL", 0, 0);

	std::vector<int> values { 0, 0, 0, 0, 0, 0 };

	std::string userIn;

	bool bust = true;
	int foundMeld;
	int again = 0;
	int pointReturn = 0;
	int numDiceToReset = 0;
	
	//Checking all dice for potential combinations

	//Sets the value vector so that each index reflects the number of dice with that value
	for (int i = 0; i < 6; i++) { 
		if (dice[i].isKept() == false) { 
			values[dice[i].getSide()-1]++;
		}
	}
	std::cout << std::endl;
	std::cout << std::endl;

	//Potentially move the display function in melds into setPresent so if setPresent is called true, it also displays the values

	//Full run
	if (values == (std::vector<int>)(1,1,1,1,1,1)) {run.display();run.setPresent(true);}
	
	//Three pairs requires the most logic
	int pairs = 0;
	for (int i = 0; i < 6; i++) {
		if (values[i] == 2) {
			pairs++;
		}
		else if (values[i] == 4) {
			pairs += 2;
		}
	}

	if (pairs == 3) {
	_3pairs.display();_3pairs.setPresent(1);}
	//Six of a kind
	if (*max_element(values.begin(), values.end()) == 6) {_6oK.display();_6oK.setPresent(true);}
	//Five of a kind
	if (*max_element(values.begin(), values.end()) == 5) {_5oK.display();_5oK.setPresent(true);}
	//Four of a kind
	if (*max_element(values.begin(), values.end()) == 4) {_4oK.display();_4oK.setPresent(true);}
	//Triple 6
	if (values[5] >= 3) {_3six.display();_3six.setPresent(1);}
	//Triple 5
	if (values[4] >= 3) {_3five.display();_3five.setPresent(1);}
	//Triple 4
	if (values[3] >= 3) {_3four.display();_3four.setPresent(1);}
	//Triple 3
	if (values[2] >= 3) {_3three.display();_3three.setPresent(true);}
	//Triple 2
	if (values[1] >= 3) {_3two.display();_3two.setPresent(true);}
	//Triple 1
	if (values[0] >= 3) {_3one.display();_3one.setPresent(true);}
	//Fives
	if (values[4] >= 1) {_5s.display();_5s.setPresent(true);}
	//Ones
	if (values[0] >= 1) {_1s.display();_1s.setPresent(true);}
	std::cout << std::endl;
	
	std::map<std::string, Meld> allMelds = {
    	{"run", run},
    	{"3pairs", _3pairs},
    	{"6ok", _6oK},
    	{"5ok", _5oK},
    	{"4ok", _4oK},
    	{"3six", _3six},
    	{"3five", _3five},
    	{"3four", _3four},
    	{"3three", _3three},
    	{"3two", _3two},
    	{"3one", _3one},
    	{"5s", _5s},
    	{"1s", _1s}
	};
	//maybe move the above checking for melds into a checkForMelds function and return the map or a reference to the map
	do {
		int temp = 1;
		again = 0;
		std::cout << "Which meld do you want to keep?" << std::endl;
		std::cin >> userIn;
		for (auto iter = allMelds.begin(); iter != allMelds.end(); iter++) {
			if ((iter->second.getShorthand() == userIn)&&iter->second.isPresent() == true){
				curMeld = iter->second;
				iter->second.setPresent(false);
				bust = false;
			}
		}
		numDiceToReset += curMeld.getActiveDice();
		if (userIn == _5s.getShorthand() || userIn == _1s.getShorthand()) {//if they selected ones or fives
			int j = 0;
			int k = 0;
			std::cout << "How many " << userIn[0] << "'s would you like to keep?: ";
			std::cin >> temp;
			while (!std::cin || temp > values[(int)(userIn[0]-'1')] || temp < 0) {//input is tring to keep more than exist
				std::cin.clear();
				std::cin.ignore(128, '\n');
				std::cout << "Input ERROR. Please try again:";
				std::cin >> temp;
			}
			bust = false;
			numDiceToReset+=temp;
		}
		int anotherMeld = 0;
		for (auto iter = allMelds.begin(); iter != allMelds.end(); ++iter) {
			if (iter->second.isPresent() == 1){
				anotherMeld = 1;
			}
		}
		if (anotherMeld == 1) {//there are still valid melds left
			std::cout << "Choose another meld? (1. Yes) (0. No)\t";
			std::cin >> again;
			while (!std::cin || again < 0 || again > 1) {//input is not an integer or is out of bounds
				std::cin.clear();
				std::cin.ignore(128, '\n');
				std::cout << "Input ERROR. Please try again:";
				std::cin >> again;
			}
		}
		pointReturn += curMeld.getValue()*temp;
	} while (again == 1);
	//std::cout << "Dice for next roll: " << diceInPlay()-numDiceToReset << std::endl;//debug statement
	setDiceToPlay(diceInPlay()-numDiceToReset);
	if (bust == true) { pointReturn = -1; }
	return pointReturn;//returns the score for this roll
}

//Function: 	rollCup
//
//inputs: 		none
//outputs: 		none
//
//Description:	Rolls every dice that has not been kept 
void Cup::rollCup() { //random number now assigned for every dice in the array	
	for (int i = 0; i < 6; i++) {
		if (dice[i].isKept() == false) {//if the dice hasn't been kept
			dice[i].rollDice();//call the rolldice function
		}
	}
}

//Function: 	diceInPlay
//
//inputs: 		none
//outputs: 		numDice
//
//Description:	Counts how many dice are in play 
int Cup::diceInPlay() { //random number now assigned for every dice in the array
	int numDice	= 0;
	for (int i = 0; i < 6; i++) {
		if (dice[i].isKept() == false) {//if the dice hasn't been kept
			numDice++;//increment the number of dice in play
			}
	}
	return numDice;
}