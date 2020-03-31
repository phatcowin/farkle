// cowin && davison
#include <iostream>
#include "die.h"
using namespace std;
/*
int main() {
	srand(time(0));
	cout << "Hello World!\n";
	Die d({.5,.1,.1,.1,.1,.1},6);
	Die d2;
	d.roll();
	d2.roll();
	cout << d.get_roll() << endl;
	cout << d2.get_roll() << endl;
}
*/
/*
	Farkle Steps:
	1:	Set up game.
		1.1: 	Enable/disable special dice.
		1.2:	Set number of players.
	2:	Player turn loop.
		2.1:	Player throws 6 dice.
		2.2:	If no scoring dice are thrown the player earns a zero for the round, regardless of dice set aside.
		2.3:	If scoring dice are thrown, the player may set aside scoring dice.
		2.4:	Player may choose to roll the remaining dice, or end their turn.
			2.4.1:	 	If the player chooses to roll, they repeat steps 2.2 thru 2.4.
		2.5:	Score the dice.
			2.5.1:		A single 1 == 100pts.
			2.5.2:		A single 5 == 50pst.
			2.5.3:		3 of a kind (excluding 1s) == 100(n) where n == number on the dice.
			2.5.4:		3 ones == 1000pts.
			2.5.5:		4+ of a kind == multiply by 2 for every extra identical (x4 4s == 800, x5 4s == 1600).
		2.6: 	Increase the player's score by the round's points.
			2.6.1: 		If the player has achieved the win condition, break the loop.
			2.6.2:		If the player has not won yet, switch players.
	4:	Output the winner and their score, exit.
*/

int main() {
	Table table();
	size_t players;
	srand(time(0));

	cout << "                  Cowin & Davison's\n"
		 << " _____ _    ____  _  ___     _____\n"
		 << "|  ___/ \\  |  _ \\| |/ / |   | ____|\n"
		 << "| |_ / _ \\ | |_) | ' /| |   |  _|\n"
		 << "|  _/ ___ \\|  _ <| . \\| |___| |___\n"
		 << "|_|/_/   \\_\\_| \\_\\_|\\_\\_____|_____|\n\n";

	// Step 1: Set up game.
	// Step 1.1: Set number of players.
	cout << "Please enter a number of human players: ";
	cin >> players;
	table.set_players(players);
	
	// Step 1.2: Set number of bots. (optional)
	cout << "Please enter a number of computer players: ";
	cin >> players;
	table.set_bots(players);

	// Step 2: Player turn loop.
	

	return 0;
}
