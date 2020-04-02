#include "table.h"
#include <vector>
#include <cassert>
#include <unistd.h>
#include "player.h"
#include "colors.h"

//const int BOT_TIMEOUT_1 = 2000000;
//const int BOT_TIMEOUT_2 = 500000;
const int BOT_TIMEOUT_1 = 0;
const int BOT_TIMEOUT_2 = 0;

FTable::FTable() {
	target_score = 2000;
	size = 0;
}

void FTable::add_player(std::string new_name) {
	Player temp(new_name, true);
	players.push_back(temp);
	size++;
}

void FTable::add_player(std::string new_name, std::vector<double> new_weights) {
	Player temp(new_name, true, new_weights, 6);
	players.push_back(temp);
	size++;
}

void FTable::add_bot(std::string new_name, std::vector<double> new_weights) {
	Player temp(new_name, false, new_weights, 6);
	players.push_back(temp);
	size++;
}

void FTable::set_target(unsigned int new_target_score) {
	target_score = new_target_score;
}

unsigned int FTable::get_target() {
	return target_score;
}

unsigned int FTable::get_size() {
	return size;
}

Player* FTable::get_player(unsigned int i) {
	return &players.at(i);
}

std::string FTable::start_round(unsigned int wager) {
	pot = 0;

	for (int i(0); i < size; i++) {
		if (players.at(i).check_seat() == false) continue;
		unsigned int pot_adjust = players.at(i).adjust_wallet(wager, false);
		pot += pot_adjust;

		std::cout << players.at(i).get_name() << " added " << GREEN << "$" << pot_adjust << RESET << " to the pot.\n";
		if (players.at(i).get_wallet() == 0) std::cout << RED << players.at(i).get_name() << " is broke!\n" << RESET;
	}
	for (int player_loop(0); players.at(player_loop).get_score() < target_score; player_loop++) {
		bool player_busted = false;
		if (players.at(player_loop).check_seat() == false) continue;

		unsigned int win_condition = target_score - players.at(player_loop).get_score();
		std::cout << "\n==============================================\n"
				  << players.at(player_loop).get_name() << "\'s turn:\n"
				  << "Score: " << players.at(player_loop).get_score() << endl
				  << YELLOW << win_condition << " more points to win!\n" << RESET
				  << "==============================================\n\n";
	
		bool fresh_roll = true;
		players.at(player_loop).roll();
		players.at(player_loop).print_dice();
		if (players.at(player_loop).round_score() < 50) {
			player_busted == true;
			std::cout << RED << players.at(player_loop).get_name() << " farkled!\n" << RESET;
			players.at(player_loop).end_turn(true);
			if (player_loop >= size - 1) player_loop = -1;
			continue;
		} 
		bool continue_turn = true;
		bool bot_phase = 0;
		bool selected = false;
		while (continue_turn == true) { // player turn
			unsigned int input;
			std::cout << "Points: " << players.at(player_loop).round_score() << "\n\n"
					  << "What would you like to do?\n"
					  << "0. Set dice aside.\n"
					  << "1. Roll active dice.\n";
			if (players.at(player_loop).round_score() >= win_condition && selected == true) std::cout << YELLOW;
			else if (selected == false) std::cout << RED;
			std::cout << "2. Score in.\n"
					  << CYAN
					  << "input> ";
			if (players.at(player_loop).is_human() == true) std::cin >> input;
			
			// AI FOR MAIN MENU
			else {
				if (players.at(player_loop).round_score() < players.at(player_loop).get_risk() && players.at(player_loop).round_score() < target_score && players.at(player_loop).aside_count() < 4) {
					if (fresh_roll == true) {
						input = 0;
						fresh_roll = false;
					} 
					else {
						input = 1;
						fresh_roll = true;
					}
				} else {
					input = 0;
					if (selected == true) input = 2;
				}
				//usleep(BOT_TIMEOUT_1);
				std::cout << input << endl;
				//usleep(BOT_TIMEOUT_2);
			}
			while (input == 2 && selected == false) {
				std::cout << RED << "You must select at least one die before scoring in!\n" << CYAN << "input> " << RESET;
				std::cin >> input;
			}
			for (int i(0); input < 0 || input > 2; i++) {
				if (i > 20) {
					input = 0;
					break;
				}
				std::cout << RED << "Invalid input. Try again.\n" << CYAN << "input> ";
				std::cin >> input;
			}

			std::cout << RESET;

			cout << endl;
			if (input == 0) {
				int grab_all = 0;
				do {
					players.at(player_loop).print_dice();
					std::cout << "Which die number would you like to set aside?\n"
							  << "Input 0 to return to the previous menu.\n"
							  << CYAN << "input> ";
					if (players.at(player_loop).is_human() == true) std::cin >> input;
					
					// AI FOR CHOOSING DICE
					else {
						input = 0;
						bool found_selection = false;
						for (int i(0); i < 6; i++) {
							if (players.at(player_loop).aside_count() >= 3 && selected == true && grab_all == 0) break;
							if (grab_all == players.at(player_loop).get_die(i) && players.at(player_loop).is_aside(i) == false) {
								input = i + 1;
								found_selection = true;
							}
							else if (players.at(player_loop).get_die(i) == 1 && players.at(player_loop).is_aside(i) == false) {
								input = i + 1;
								found_selection = true;
							}
							else if (found_selection == false && selected == false) {
								if (players.at(player_loop).get_die(i) == 5 && players.at(player_loop).is_aside(i) == false) {
									input = i + 1;
									found_selection = true;
								}
								else if (found_selection == false && selected == false) { 
									if (players.at(player_loop).is_aside(i) == false && players.at(player_loop).scoring(players.at(player_loop).get_die(i)) == true) {
										std::cout << "Grabbing all " << players.at(player_loop).get_die(i) << "\'s!\n";
										grab_all = players.at(player_loop).get_die(i);
										input = i + 1;
										found_selection = true;
									}
								}
							}
						}
						//usleep(BOT_TIMEOUT_1);
						std::cout << input << endl;
						//usleep(BOT_TIMEOUT_2);
					}

					std::cout << std::endl;
					while (input > 6) {
						std::cout << RED << "Invalid input. Try again.\n" << CYAN << "input> ";
						std::cin >> input;
					}
					std::cout << RESET;
					if (input > 0) {
						players.at(player_loop).set_aside(input);
						selected = true;
					}
				} while (input != 0);
			}

			else if (input == 1) {
				if (players.at(player_loop).roll() == true) {
					player_busted = true;
					players.at(player_loop).print_dice();
					std::cout << RED << players.at(player_loop).get_name() << " farkled!\n" << RESET;
					players.at(player_loop).end_turn(true);
					continue_turn = false;
					break;
				} 
				else {
					players.at(player_loop).print_dice();
					selected = false;
				}
			} 
			
			else if (input == 2) {
				players.at(player_loop).adjust_score(players.at(player_loop).round_score());
				players.at(player_loop).end_turn(true);
				continue_turn = false;
			}
		}
		if (continue_turn == false) std::cout << std::endl << players.at(player_loop).get_name() << " earned: ";
		if (player_busted == false) std::cout << players.at(player_loop).round_score();
		else std::cout << 0;
		std::cout << " points.\n" << players.at(player_loop).get_name() << "\'s score: " << players.at(player_loop).get_score() << " points.\n";
		if (players.at(player_loop).get_score() >= target_score) {
			players.at(player_loop).adjust_wallet(pot, true);
			return players.at(player_loop).get_name();
		}
		if (player_loop >= size - 1) player_loop = -1;
	}
	return "Nobody";
}

void FTable::reset() {
	for (int i(0); i < size; i++) {
		players.at(i).reset_score();
	}
}

void FTable::print_wallets() {
	for (unsigned int i(0); i < size; i++) {
		std::cout << players.at(i).get_name() << "\'s stack: ";
		if (players.at(i).get_wallet() < 1) std::cout << RED;
		else std::cout << GREEN;
		std::cout << "$" << players.at(i).get_wallet() << std::endl << RESET;
	}
}

unsigned int FTable::max_wager() {
	unsigned int largest = 0;
	for (unsigned int i(0); i < size; i++) {
		if (players.at(i).get_wallet() > largest) largest = players.at(i).get_wallet();
	}
	return largest;
}

unsigned int FTable::remaining_players() {
	unsigned int remaining = 0;
	for (unsigned int i(0); i < size; i++) {
		if (players.at(i).check_seat() == true) remaining++;
	}
	return remaining;
}

unsigned int FTable::check_pot() {
	return pot;
}

void FTable::check_seats() {
	for (unsigned int i(0); i < size; i++) {
		players.at(i).check_funds();
	}
}
