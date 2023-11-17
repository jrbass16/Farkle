#include "Cup.h"
#include "melds.h"
ostream& operator<<(ostream& os, Cup& cup) {
	os << "|" << cup.dice[cup.i].getSide() << "| ";
	return os;
}

void Cup::printDice(Cup& cup, int i = 0) {
	cout << endl << endl;
	//Print Table
	cout << "  _____________________________________________________";
	cout << endl << endl;
	cup.i = 0;
	for (int a = 0; a < 6; a++) {
		cout << "  |";
		int r = rand() % 24;
		for (int b = 0; b < 24; b++) {
			cout << " ";
			if (b == r) {
				if (cup.dice[cup.i].isKept() == false) {
					cout << cup;
				}
				else {
					cout << "    ";
				}
				cup.i++;

			}
			cout << " ";
		}
		//cout << "                                                ";	
		cout << "|";
		cout << endl;
	}
	cout << "  _____________________________________________________";
	cout << endl;
	//Print ordered
	cout << endl << endl;
	cup.i = 0;
	cout << "Here are the dice in play organized: ";
	while (cup.i < 6) {
		if (cup.dice[cup.i].isKept() == false) {
			cout << cup;
		}
		cup.i++;
	}
	cout << endl << endl;
}

void Cup::resetCup(int diceToReset) {
	for (int i = 0; i < diceToReset; i++) {//for each dice
		dice[i].setKept(false);//set kept to false; they are in play
	}
}

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
		resetCup(6);
	}
}

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
	Meld _5s("5s!","5s", 50, 1);
	Meld _1s("1s!","1s", 100, 1);

	int again = 0;
	int values[] = { 0, 0, 0, 0, 0, 0 };
	string userIn;
	bool bust = true;
	//check combinations from the top down.
	//I think the easiest way is to know how many of each value there is and check from there, then identify which dice are valid
	for (int i = 0; i < 6; i++) { //for each of the 6 dice
		if (dice[i].isKept() == false) { //checks if they were just rolled
			values[dice[i].getSide()-1]++;
		}
	}
	cout << endl;
	//for each case, it looks at the dice that were just rolled and sees if their values match a meld. 
	//It then marks down that meld as valid in the points array and moves on to the next meld to check
	for (int i = 0; i < 6; i++) {
		cout<<values[i];
	}
	cout << endl;
	//Full run
	if (values[0] == 1 && values[1] == 1 && values[2] == 1 && values[3] == 1 && values[4] == 1 && values[5] == 1) {
	run.display();run.setPresent(1);}
	//Three pairs
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
	if (values[0] == 6 || values[1] == 6 || values[2] == 6 || values[3] == 6 || values[4] == 6 || values[5] == 6) {
	_6oK.display();_6oK.setPresent(1);}
	//Five of a kind
	if (values[0] >= 5 || values[1] == 5 || values[2] == 5 || values[3] == 5 || values[4] == 5 || values[5] == 5) {
	_5oK.display();_5oK.setPresent(1);}
	//Four of a kind
	if (values[0] >= 4 || values[1] == 4 || values[2] == 4 || values[3] == 4 || values[4] == 4 || values[5] == 4) {
	_4oK.display();_4oK.setPresent(1);}
	//Triple 6
	if (values[5] >= 3) {_3six.display();_3six.setPresent(1);}
	//Triple 5
	if (values[4] >= 3) {_3five.display();_3five.setPresent(1);}
	//Triple 4
	if (values[3] >= 3) {_3four.display();_3four.setPresent(1);}
	//Triple 3
	if (values[2] >= 3) {
	_3three.display();_3three.setPresent(true);}
	//Triple 2
	if (values[1] >= 3) {
	_3two.display();_3two.setPresent(true);}
	//Triple 1
	if (values[0] >= 3) {
	_3one.display();_3one.setPresent(true);}
	//Fives
	if (values[4] >= 1) {
	_5s.display();_5s.setPresent(true);}
	//Ones
	if (values[0] >= 1) {
	_1s.display();_1s.setPresent(true);}
	cout << endl;
	int foundMeld;
	Meld curMeld("Inactive", "NULL", 0, 0);
	int pointReturn = 0;

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

	do {
		int temp = 1;
		int resetDice = 0;
		again = 0;
		std::cout << "Which meld do you want to keep?" << std::endl;
		cin >> userIn;
		for (auto iter = allMelds.begin(); iter != allMelds.end(); iter++) {
			if ((iter->second.getShorthand() == userIn)&&iter->second.isPresent() == true){
				curMeld = iter->second;
				iter->second.setPresent(false);
				bust = false;
			}
		}
		resetDice = curMeld.getActiveDice();
		if (userIn == "5s") {//5's, ask how many to keep and add p for each
			int j = 0;
			int k = 0;
			cout << "How many 5's would you like to keep?: ";
			cin >> temp;
			while (!cin || temp > values[4] || temp < 0) {//input is not an integer or is out of bounds
				cin.clear();
				cin.ignore(128, '\n');
				cout << "Input ERROR. Please try again:";
				cin >> temp;
			}
			bust = false;
		}
		else if (userIn == "1s"){//1's, ask how many to keep and add 100 for each
			int j = 0;
			int k = 0;
			cout << "How many 1's would you like to keep?: ";
			cin >> temp;
			while (!cin || temp > values[0] || temp < 0) {//input is not an integer or is out of bounds
				cin.clear();
				cin.ignore(128, '\n');
				cout << "Input ERROR. Please try again:";
				cin >> temp;
			}
			bust = false;
			resetCup(temp);
		}
		int anotherMeld = 0;
		for (auto iter = allMelds.begin(); iter != allMelds.end(); ++iter) {
			if (iter->second.isPresent() == 1){
				anotherMeld = 1;
			}
		}
		if (anotherMeld == 1) {//there are still valid melds left
			cout << "Choose another meld? (1. Yes) (0. No)\t";
			cin >> again;
			while (!cin || again < 0 || again > 1) {//input is not an integer or is out of bounds
				cin.clear();
				cin.ignore(128, '\n');
				cout << "Input ERROR. Please try again:";
				cin >> again;
			}
		}
		pointReturn += curMeld.getValue()*temp;
		resetCup(temp);
	} while (again == 1);
	if (bust == true) { pointReturn = -1; }
	return pointReturn;//returns the score for this roll
}


void Cup::rollCup() { //random number now assigned for every dice in the array	
	for (int i = 0; i < 6; i++) {
		if (dice[i].isKept() == false) {//if the dice hasn't been kept
			dice[i].rollDice();//call the rolldice function
		}
	}
}