#include <iostream>
#include <string>
#include <map>
#include <vector>

class Meld{
    private:
	string displayText;
    string shorthand;
	bool presentInRoll;
	int value;
    int diceVals[6];
    public:
    string getShorthand(){return shorthand;}
    int getValue() {return value;}
    bool isPresent() {return presentInRoll;}
    void setPresent(bool v) {presentInRoll = v;}
    void display() {std::cout <<"(" << shorthand << ")\t\t"<< displayText << " worth " << value << " points" << std::endl;}
    Meld() {}
    Meld(string Disp, string shorty, int score) {displayText = Disp,shorthand = shorty; value = score; presentInRoll = 0;}
    ~Meld() {}
};
//potential melds: {run,3pairs,6oK,5oK,4oK,3six,3five,3four,3three,3two,3one,5s,1s}
Meld run("Full run!","run", 2500);
Meld _3pairs("Three pairs!","3pairs", 1500);
Meld _6oK("Six of a kind!","6ok",3000);
Meld _5oK("Five of a kind!","5ok", 2000);
Meld _4oK("Four of a kind!","4ok", 1000);
Meld _3six("Triple 6!","3six", 600);
Meld _3five("Triple 5!","3five", 500);
Meld _3four("Triple 4!","3four", 400);
Meld _3three("Triple 3!","3three",300);
Meld _3two("Triple 2!","3two", 200);
Meld _3one("Triple 1!","3one",1000);
Meld _5s("5s!","5s", 50);
Meld _1s("1s!","1s", 100);

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