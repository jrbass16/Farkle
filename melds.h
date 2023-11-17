#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Dice.h"

#ifndef MELD_H
#define MELD_H
class Meld{
    private:
	std::string displayText;
    std::string shorthand;
	bool presentInRoll;
	int value;
    int diceVals[6];
    int activeDice; //number of dice needed to complete the meld
    public:
    void setVals(int vals [6]){for (int i = 0;i<6;i++){diceVals[i] = vals[i];}}
    std::string getShorthand(){return shorthand;}
    int getActiveDice(){return activeDice;}
    int getValue() {return value;}
    bool isPresent() {return presentInRoll;}
    void setPresent(bool v) {presentInRoll = v;}
    void display() {std::cout <<"(" << shorthand << ")\t\t"<< displayText << " worth " << value << " points" << std::endl;}
    Meld() {}
    Meld(std::string Disp, std::string shorty, int score, int actDice) 
    {displayText = Disp,shorthand = shorty; value = score; presentInRoll = 0; activeDice = actDice;}
    ~Meld() {}
};
#endif