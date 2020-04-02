// cowin && davison
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "table.h"
#include "colors.h"
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
	cout << MAGENTA << endl
		 << "      _____ _    ____  _  ___     _____\n"
		 << "     |  ___/ \\  |  _ \\| |/ / |   | ____|\n"
		 << "     | |_ / _ \\ | |_) | ' /| |   |  _|\n"
		 << "     |  _/ ___ \\|  _ <| . \\| |___| |___\n"
		 << "     |_|/_/   \\_\\_| \\_\\_|\\_\\_____|_____|\n"
		 << CYAN
		 << "              by Cowin, Davison & Kerney\n\n"
		 << RESET;

	// Step 1: Set up game.
	srand(time(0));
	FTable table;
	const unsigned int UNIQUE_DICE = 5;
	vector<vector<double>> kcd_dice;
		vector<double> fair_die = {1/6.0,1/6.0,1/6.0,1/6.0,1/6.0,1/6.0}; kcd_dice.push_back(fair_die);
		vector<double> alfonse = {0.468927,0.0451977,0.0508475,0.0677966,0.101695,0.265537}; kcd_dice.push_back(alfonse);
		vector<double> alfonse_devil = {0.243902,0.109756,0.146341,0.121591,0.182927,0.195122}; kcd_dice.push_back(alfonse_devil);
		vector<double> biased_die = {0.444444,0.111111,0.111111,0.111111,0.111111,0.111111}; kcd_dice.push_back(biased_die);
		vector<double> ci_die = {0.184783,0.0978261,0.125,0.13587,0.11413,0.342391}; kcd_dice.push_back(ci_die);
		vector<double> devils_head = {0.188406,0.101449,0.173913,0.246377,0.130435,0.15942}; kcd_dice.push_back(devils_head);
		vector<double> even_number = {0.0967742,0.193548,0.0322581,0.129032,0.225806,0.322581}; kcd_dice.push_back(even_number);
		vector<double> fer_die = {0.140541,0.113514,0.124324,0.135135,0.135135,0.351351}; kcd_dice.push_back(fer_die);
		vector<double> heavenly_k = {0.333333,0.0952381,0.166667,0.0952381,0.119048,0.190476}; kcd_dice.push_back(heavenly_k);
		vector<double> holy_trinity = {0.235294,0.191176,0.426471,0.0588235,0.0294118,0.0588235}; kcd_dice.push_back(holy_trinity);
		vector<double> lu_die = {0.172414,0.16092,0.155172,0.149425,0.103448,0.258621}; kcd_dice.push_back(lu_die);
		vector<double> lucky_die = {0.342105,0.0263158,0.0614035,0.131579,0.184211,0.254386}; kcd_dice.push_back(lucky_die);
		vector<double> lucky_playing = {0.333333,0,0.0190476,0.0476619,0.361905,0.238095}; kcd_dice.push_back(lucky_playing);
		vector<double> odd_die = {0.293333,0.08,0.213333,0.0666667,0.293333,0.0533333}; kcd_dice.push_back(odd_die);
		vector<double> shrinking = {0.265625,0.0625,0.09375,0.15625,0.125,0.296875}; kcd_dice.push_back(shrinking);
		vector<double> unpopular = {0.2,0.1,0.1,0.3,0.2,0.1}; kcd_dice.push_back(unpopular);
		vector<double> misfortune = {0.1,0.12,0.26,0.12,0.32,0.08}; kcd_dice.push_back(misfortune);
		vector<double> strip_die = {0.22,0.12,0.1,0.14,0.28,0.14}; kcd_dice.push_back(strip_die);
		vector<double> commonest = {0.36,0.16,0.14,0.08,0.1,0.16}; kcd_dice.push_back(commonest);

	bool is_fair;
	string input_string;
	cout << "Do all players agree to play on equal footing?\n"
		 << "0. No.\n"
		 << "1. Yes.\n"
		 << CYAN
		 << "input> ";
	cin >> input_string;
	cout << RESET;
	while (input_string != "0" && input_string != "1") {
		cout << RED << "Bad input, try again.\n" << CYAN << "input> ";
		cin >> input_string;
		cout << RESET;
	}
	is_fair = stoi(input_string);
	cout << endl;

	unsigned int player_count;
	cout << "Please enter a number of human players.\n" << CYAN <<"input> ";
	cin >> player_count;
	cout << RESET;
	while (player_count < 0 || player_count > 10) {
		cout << RED << "Arbitrary 10 player limit. Try again.\n" << CYAN << "input> ";
		cin >> player_count;
		cout << RESET;
	}
	cout << endl;

	string name;
	for (unsigned int i(0); i < player_count; i++) {
		cout << "Enter a name for Player " << i + 1 << "\n" << CYAN << "inputv" << endl;
		name = "";
		while (name == "") getline(cin, name);
		while (table.name_available(name) == false) {
			cout << RED << name << " is taken. Try again.\n" << CYAN << "inputv" << endl;
			name = "";
			while (name == "") getline(cin, name);
		}
		cout << RESET;
		if (is_fair == true) table.add_player(name);
		else {
			cout << "Which set of dice would you like to use?\n"
				 << "0. Balanced dice.\n"
				 << "1. Kingdom Come Deliverance dice.\n"
				 << "2. Custom dice.\n"
				 << CYAN
				 << "input> ";
			cin >> input_string;
			cout << RESET;
			while (input_string < "0" || input_string > "2") {
				cout << RED << "Bad input! Try again.\n" << CYAN << "input> ";
				cin >> input_string;
				cout << RESET;
			}

			if (input_string == "0") table.add_player(name);

			else if (input_string == "1") {
				cout << "Select your set of dice:\n"
					 << "0. Fair dice.\n"
					 << "1. Alfonse\'s dice.\n"
					 << "2. Alfonse\'s Devil dice.\n"
					 << "3. Biased dice.\n"
					 << "4. Ci dice.\n"
					 << "5. Devil's Head die\n"
					 << "6. Even number die.\n"
					 << "7. Fer die.\n"
					 << "8. Heavenly Kingdom die.\n"
					 << "9. Holy Trinity die.\n"
					 << "10. Lu die.\n"
					 << "11. Lucky die.\n"
					 << "12. Lucky playing die.\n"
					 << "13. Odd die.\n"
					 << "14. Shrinking playing die.\n"
					 << "15. Unpopular die.\n"
					 << "16. Die of misfortune.\n"
					 << "17. Strip die.\n"
					 << "18. The commonest die.\n"
					 << CYAN
					 << "input> ";
				cin >> input_string;
				cout << RESET;
				while (input_string < "0" || stoi(input_string) > kcd_dice.size()) {
					cout << RED << "Bad input, try again.\n" << CYAN << "input> ";
					cin >> input_string;
					cout << RESET;
				}
				table.add_player(name, kcd_dice.at(stoi(input_string)));
			}

			else if (input_string == "2") {
				vector<double> weights;
				double weight_input;
				cout << "Load your dice! Enter 6 decimals with a sum of 1.\n";
				for (unsigned int x(0); x < 6; x++) {
					cout << "Select a weight for side " << x + 1 << ".\n" << CYAN << "input> ";
					cin >> weight_input;
					cout << RESET;
					while (weight_input < 0 || weight_input > 1) {
						cout << RED << "Bad input, try again.\n" << CYAN << "input> ";
						cin >> weight_input;
						cout << RESET;
					}
					weights.push_back(weight_input);
				}

				while (weights.at(0) + weights.at(1) + weights.at(2) + weights.at(3) + weights.at(4) + weights.at(5) != 1) {
					cout << RED << "The sum of the inputs was not 1, try again.\n" << RESET;
					for (unsigned int x(0); x < 6; x++) {
						cout << "Select a weight for side " << x + 1 << ".\n" << CYAN << "input> ";
						cin >> weight_input;
						cout << RESET;
						while (weight_input < 0 || weight_input > 1) {
							cout << RED << "Bad input, try again.\n" << CYAN << "input> ";
							cin >> weight_input;
							cout << RESET;
						}
						weights.push_back(weight_input);
					}
				}

				table.add_player(name, weights);
			}
		}
		if (is_fair == false) cout << endl;
	}
	if (is_fair == true) cout << endl;

	cout << "Please enter a number of computer players.\n" << CYAN << "input> ";
	cin >> player_count;
	cout << RESET;
	if (table.get_size() == 0 && player_count == 0) {
		cout << RED << "There are no players. Exiting game...\n" << RESET;
		return 1;
	}
	while (player_count >= 10) {
		cout << RED << "Arbitrary 9 bot limit! Try again.\n" << CYAN << "input> ";
		cin >> player_count;
		cout << RESET;
	}
	if (player_count > 1) name = "Bot 1";
	else name = "Bot";
	for (int i(0); i < player_count; i++) {
		vector<double> bot_weights;
		if (is_fair == true) bot_weights = kcd_dice.at(0);
		else bot_weights = kcd_dice.at(rand() % UNIQUE_DICE);
		table.add_bot(name, bot_weights);
		if (player_count > 1) name[4]++;
	}

	bool continue_game = true;
	for (int round_number(1); continue_game; round_number++) {
		cout << endl << "Please select a target score for this round.\n" << CYAN << "input> ";
		cin >> player_count;
		while (player_count < 1000) {
			cout << RED << "Arbitrary 1000 point minimum. Try again.\n" << CYAN << "input> ";
			cin >> player_count;
		}
		cout << RESET << endl;
		table.set_target(player_count);

		if (round_number == 1) {
			cout << "==============================================\n";
			table.print_wallets();
			cout << "==============================================\n";
		}
		unsigned int wager;
		cout << "Set the wager.\n" << CYAN << "input> ";
		cin >> name;
		cout << RESET;
		if (stoi(name) > 0) wager = stoi(name);
		else wager = stoi(name) * -1;
		if (wager >= table.max_wager()) {
			cout << YELLOW << "Going all in!\n" << RESET;
			wager = table.max_wager();
		}
		cout << endl;

		name = table.start_round(wager);
		table.reset();
		cout << "\n==============================================\n"
			 << name << " won round " << round_number << "!\n"
			 << name << " earned " << GREEN << "$" << table.check_pot() << RESET << "!\n\n";
		table.print_wallets();
		cout << endl;

		table.check_seats();
		if (table.remaining_players() < 2) {
			cout << YELLOW << name << " cleaned house!\n" << RESET
				 << "==============================================\n";
			break;
		}
		cout << "==============================================\n"
			 << "Would you like to play another round?\n"
			 << "0. End game.\n"
			 << "1. Continue.\n"
			 << CYAN
			 << "input> ";
		cin >> input_string;
		while (input_string != "1" && input_string != "0") {
			cout << RED << "Bad input, try again.\n" << CYAN << "input> ";
			cin >> input_string;
		}
		cout << RESET;
		continue_game = stoi(input_string);
	}

	cout << endl;
	return 0;
}
