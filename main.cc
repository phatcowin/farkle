// cowin && davison
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "table.h"
using namespace std;
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
	cout << "                  Cowin & Davison's\n"
		 << " _____ _    ____  _  ___     _____\n"
		 << "|  ___/ \\  |  _ \\| |/ / |   | ____|\n"
		 << "| |_ / _ \\ | |_) | ' /| |   |  _|\n"
		 << "|  _/ ___ \\|  _ <| . \\| |___| |___\n"
		 << "|_|/_/   \\_\\_| \\_\\_|\\_\\_____|_____|\n\n";

	// Step 1: Set up game.
	srand(time(0));
	FTable table();

	bool is_fair;
	cout << "Would you like to play with weighted dice?\n"
		 << "0. Yes.\n"
		 << "1. No.\n";
	cin >> is_fair;

	unsigned int player_count;
	cout << "Please enter a number of human players: ";
	cin >> player_count;
	while (player_count < 1) {
		cout << "There must be at least one player!\n"
			 << "Please enter a number of human players: ";
		cin >> player_count;
	}

	string name;
	for (unsigned int i(0); i < player_count; i++) {
		cout << "Player " << i << "\'s name: ";
		cin >> name;
		while (!cin) {
			cout << "Bad input, try again: ";
			cin >> name;
		}
		if (is_fair == true) table.add_player(name);
		else {
			vector<double> weights;
			cout << "Load your dice! Enter 6 decimals with a sum of 1.\n";
			for (unsigned int x(0); x < 6; x++) {
				cout << "Weight for side " << x + 1 << ": ";
				cin >> weights.at(x);
				while (!cin) {
					cout << "Bad input, try again: ";
					cin >> weights.at(x);
				}
			}
			while (weights.at(0) + weights.at(1) + weights.at(2) + weights.at(3) + weights.at(4) + weights.at(5) != 1) {
				cout << "The sum of the inputs was not 1, try again.\n";
				for (unsigned int x(0); x < 6; x++) {
					cout << "Weight for side " << x + 1 << ": ";
					cin >> weights.at(x);
					while (!cin) {
						cout << "Bad input, try again: ";
						cin >> weights.at(x);
					}
				}
			}
			table.add_player(name, weights);
		}
	}
	
	// Step 1.2: Set number of bots. (optional)
	//cout << "Please enter a number of computer players: ";
	//cin >> player_count;
	//table.add_bots(player_count);

	// Step 2: Player turn loop.
	

	return 0;
}
