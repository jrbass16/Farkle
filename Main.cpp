#include "dice.h"
#include "cup.h"
#include "player.h"
#include "start.h"
using namespace std;

int main() {
	startGame();
	srand(time(0));
	Player p1("Player 1");
	Player p2("Player 2");
	bool winner = false;
	int turn = 1;
	while (winner == false) {
		if (turn == 1) {//Player 1's turn
			try { p1.playTurn(p2); }
			catch (string pName) {
				cout << pName << " rolled no combinations! Thats a Farkle and 0 points this turn!" << endl;
				system("pause");
			}
			if (p1.giveScore() >= 5000) { //if player 1 has over 5000 points, they win! game over
				winner = true;
				cout << "Player 1 wins!!! Congratulations!!" << endl;
			}
			turn += 1;//to make it player 2s turn
		}
		else {//Player 2's turn
			try { p2.playTurn(p1); }
			catch (string pName) {
				cout << pName << " rolled no combinations! Thats a Farkle and 0 points this turn!" << endl;
				system("pause");
			}
			if (p2.giveScore() >= 5000) { //if player 2 has over 5000 points, they win! game over
				winner = true;
				cout << "Player 2 wins!!! Congratulations!!" << endl;
			}
			turn -= 1;//to make it back into player 1s turn
		}
	}
	return 0;
}