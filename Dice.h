#pragma once
#include <iostream>
#include <string>

//All inline functions so dice does not come with a cpp file
class Dice {
private:
	int side;
	bool kept;
public:
	bool isKept() { return kept; } //returns whether the dice is currently kept or  not
	void setKept(bool set) { kept = set; } //sets whether the dice has been kept or not
	void rollDice() { side = rand() % 6 + 1; } //sets the side to a random values between 1 and 6
	int getSide() { return side; }
	Dice() { rollDice(); setKept(true); }
	~Dice() {}
};//all Dice functions are inline functions so no source file is needed for the dice class
