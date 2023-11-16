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

void Cup::resetCup() {
	for (int i = 0; i < 6; i++) {//for each dice
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
		resetCup();
	}
}

int Cup::tallyScore() {
	int pointReturn = 0;
	bool bust = false;
	int temp;
	int again = 0;
	string userIn;
	int values[] = { 0, 0, 0, 0, 0, 0 };
	bool points[] = {0,0,0,0,0,0,0,0,0,0,0,0,0};//{run,3pairs,6oK,5oK,4oK,3six,3five,3four,3three,3two,3one,5s,1s}
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
	if (values[0] == 5 || values[1] == 5 || values[2] == 5 || values[3] == 5 || values[4] == 5 || values[5] == 5) {
	_5oK.display();_5oK.setPresent(1);}
	//Four of a kind
	if (values[0] == 4 || values[1] == 4 || values[2] == 4 || values[3] == 4 || values[4] == 4 || values[5] == 4) {
	_4oK.display();_4oK.setPresent(1);}
	//Triple 6
	if (values[5] == 3) {_3six.display();_3six.setPresent(1);}
	//Triple 5
	if (values[4] == 3) {_3five.display();_3five.setPresent(1);}
	//Triple 4
	if (values[3] == 3) {_3four.display();_3four.setPresent(1);}
	//Triple 3
	if (values[2] == 3) {
	_3three.display();_3three.setPresent(1);}
	//Triple 2
	if (values[1] == 3) {
	_3two.display();_3two.setPresent(1);}
	//Triple 1
	if (values[0] == 3) {
	_3one.display();_3one.setPresent(1);}
	//Fives
	if (values[4] >= 1) {
	_5s.display();_5s.setPresent(1);}
	//Ones
	if (values[0] >= 1) {
	_1s.display();_1s.setPresent(1);}
	cout << endl;
	bool valid = false;//below is if there are no valid scoring dice combinations
	auto iter = allMelds.begin();
	int foundMeld;
	Meld curMeld;
	while (iter !=allMelds.end() && foundMeld != 1) {
		if (iter->second.isPresent() == 1){
			foundMeld == 1;
		}
		++iter;
	}
	
	do {
		again = 0;
		valid = false;
		if (bust == false && valid == false) {//if there are any combinations, prompt the user
			std::cout << "Which meld do you want to keep?" << std::endl;
			cin >> userIn;
			for (iter = allMelds.begin(); iter !=allMelds.end(); ++iter) {
				if (iter->second.getShorthand() == userIn){
					foundMeld == 1;
					valid = true;
					curMeld = iter->second;
				}
			}
		}
		pointReturn += curMeld.getValue();
		/*
		int j = 0;
		int k = 0;
		switch (userIn) {//this switch case looks at which meld was kept 
			//then keeps the dice needed for that meld and adds to the point return total the correect amount of points
		case 1://full run, keep all 6 and add 2500
			for (int i = 0; i < 6; i++) {
				dice[i].setKept(true);
			}
			pointReturn += curMeld.getValue();
			break;
		case 2://three pairs, keep all 6 and add 1500
			for (int i = 0; i < 6; i++) {
				dice[i].setKept(true);
			}
			pointReturn += 1500;
			break;
		case 3://6 ofKind, keep all 6 and add 3000
			for (int i = 0; i < 6; i++) {
				dice[i].setKept(true);
			}
			pointReturn += 3000;
			break;
		case 4://five of kind, keep all of number and add 2000
			for (int i = 0; i < 6; i++) {
				if (dice[i].isKept() == false) {//look at each dice in play
					if (values[dice[i].getSide() - 1] >= 5) {//looks at whether that dice's value is the one that had 5 of a kind
						dice[i].setKept(true);
					}
				}
			}
			pointReturn += 2000;
			break;
		case 5://four of kind, keep all of number and add 1000
			for (int i = 0; i < 6; i++) {
				if (dice[i].isKept() == false) {//look at each dice in play
					if (values[dice[i].getSide() - 1] >= 4) {//looks at whether that dice's value is the one that had 5 of a kind
						dice[i].setKept(true);
					}
				}
			}
			pointReturn += 1000;
			break;
		case 6://triple 6, keep 3 6's and add 600
			for (int i = 0; i < 6; i++) {
				if (dice[i].isKept() == false) {//look at each dice in play
					if (dice[i].getSide() == 6) {//looks at whether that dice's value is 6
						dice[i].setKept(true);
					}
				}
			}
			pointReturn += 600;
			break;
		case 7://triple 5, keep 3 5's and add 500
			for (int i = 0; i < 6; i++) {
				if (dice[i].isKept() == false) {//look at each dice in play
					if (dice[i].getSide() == 5) {//looks at whether that dice's value is 5
						dice[i].setKept(true);
					}
				}
			}
			values[4] -= 3;//makes sure dice can't be double counted for 5's and triple 5
			pointReturn += 500;
			break;
		case 8://triple 4, keep 3 4's and add 400
			for (int i = 0; i < 6; i++) {
				if (dice[i].isKept() == false) {//look at each dice in play
					if (dice[i].getSide() == 4) {//looks at whether that dice's value is 4
						dice[i].setKept(true);
					}
				}
			}
			pointReturn += 400;
			break;
		case 9://triple 3, keep 3 3's and add 300
			for (int i = 0; i < 6; i++) {
				if (dice[i].isKept() == false) {//look at each dice in play
					if (dice[i].getSide() == 3) {//looks at whether that dice's value is 3
						dice[i].setKept(true);
					}
				}
			}
			pointReturn += 300;
			break;
		case 10://triple 2, keep 3 2's and add 200
			for (int i = 0; i < 6; i++) {
				if (dice[i].isKept() == false) {//look at each dice in play
					if (dice[i].getSide() == 2) {//looks at whether that dice's value is 2
						dice[i].setKept(true);
					}
				}
			}
			pointReturn += 200;
			break;
		case 11://triple 1, keep 3 1's and add 1000
			for (int i = 0; i < 6; i++) {
				if (dice[i].isKept() == false) {//look at each dice in play
					if (dice[i].getSide() == 1) {//looks at whether that dice's value is 1
						dice[i].setKept(true);
					}
				}
			}
			values[0] -= 3; //makes sure that dice can't be double counted for 1's and triple 1
			pointReturn += 1000;
			break;
		case 12://5's, ask how many to keep and add 50  for each
			j = 0;
			k = 0;
			cout << "How many 5's would you like to keep?: ";
			cin >> temp;
			while (!cin || temp > values[4] || temp < 0) {//input is not an integer or is out of bounds
				cin.clear();
				cin.ignore(128, '\n');
				cout << "Input ERROR. Please try again:";
				cin >> temp;
			}
			while (k < temp) {
				if (dice[j].isKept() == false) {//look at each dice in play
					if (dice[j].getSide() == 5) {//looks at whether that dice's value is 1
						dice[j].setKept(true);
						k++; j++;
					}
					else {
						j++;
					}
				}
				else {
					j++;
				}
			}
			pointReturn += (temp * 50);
			break;
		case 13://11's, ask how many to keep and add 100 for each
			j = 0;
			k = 0;
			cout << "How many 1's would you like to keep?: ";
			cin >> temp;
			while (!cin || temp > values[0] || temp < 0) {//input is not an integer or is out of bounds
				cin.clear();
				cin.ignore(128, '\n');
				cout << "Input ERROR. Please try again:";
				cin >> temp;
			}
			while (k < temp) {
				if (dice[j].isKept() == false) {//look at each dice in play
					if (dice[j].getSide() == 1) {//looks at whether that dice's value is 1
						dice[j].setKept(true);
						k++; j++;
					}
					else {
						j++;
					}
				}
				else {
					j++;
				}
			}
			pointReturn += (temp * 100);
			break;
		default:
			break;
		}
		if (!(points[0] == 0 && points[1] == 0 && points[2] == 0 && points[3] == 0 && points[4] == 0 && points[5] == 0
			&& points[6] == 0 && points[7] == 0 && points[8] == 0 && points[9] == 0 && points[10] == 0 && points[11] == 0 && points[12] == 0)) {//there are still valid melds left
			cout << "Choose another meld? (1. Yes) (0. No)\t";
			cin >> again;
			while (!cin || again < 0 || again > 1) {//input is not an integer or is out of bounds
				cin.clear();
				cin.ignore(128, '\n');
				cout << "Input ERROR. Please try again:";
				cin >> again;
			}
		}
	*/
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