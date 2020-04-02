#include "table.h"
#include <vector>
#include <cassert>
#include <unistd.h>
#include "player.h"
#include "colors.h"

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
			std::cout << RED << players.at(player_loop).get_name() << " farkled!\n" << RESET;
			players.at(player_loop).end_turn(true);
			if (player_loop >= size - 1) player_loop = -1;
			continue;
		} 
		bool continue_turn = true;
		bool bot_phase = 0;
		while (continue_turn == true) { // player turn
			unsigned int input;
			std::cout << "Points: " << players.at(player_loop).round_score() << "\n\n"
					  << "What would you like to do?\n"
					  << "0. Set dice aside.\n"
					  << "1. Roll active dice.\n";
			if (players.at(player_loop).round_score() >= win_condition) std::cout << YELLOW;
			std::cout << "2. Score in.\n"
					  << CYAN
					  << "input> ";
			if (players.at(player_loop).is_human() == true) std::cin >> input;
			
			// AI FOR MAIN MENU
			else {
				if (players.at(player_loop).round_score() < 700 && players.at(player_loop).round_score() < target_score) {
					if (fresh_roll == true) {
						input = 0;
						fresh_roll = false;
					} 
					else {
						input = 1;
						fresh_roll = true;
					}
				} else input = 2;
				usleep(2000000);
				std::cout << input << endl;
				usleep(500000);
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
				do {
					players.at(player_loop).print_dice();
					std::cout << "Which die number would you like to set aside?\n"
							  << "Input 0 to return to the previous menu.\n"
							  << CYAN << "input> ";
					if (players.at(player_loop).is_human() == true) std::cin >> input;
					
					// AI FOR CHOOSING DICE
					else {
						input = 0;
						for (int i(0); i < 6; i++) if (players.at(player_loop).get_die(i) == 1 && players.at(player_loop).is_aside(i) == false) input = i +1;
						usleep(2000000);
						std::cout << input << endl;
						usleep(500000);
					}

					std::cout << std::endl;
					while (input > 6) {
						std::cout << RED << "Invalid input. Try again.\n" << CYAN << "input> ";
						std::cin >> input;
					}
					std::cout << RESET;
					if (input > 0) players.at(player_loop).set_aside(input);
				} while (input != 0);
			}

			else if (input == 1) {
				if (players.at(player_loop).roll() == true) {
					players.at(player_loop).print_dice();
					std::cout << RED << players.at(player_loop).get_name() << " farkled!\n" << RESET;
					players.at(player_loop).end_turn(true);
					continue_turn = false;
				} else {
					players.at(player_loop).print_dice();
				}
			} 
			
			else if (input == 2) {
				players.at(player_loop).adjust_score(players.at(player_loop).round_score());
				players.at(player_loop).end_turn(true);
				continue_turn = false;
			}
		}
		if (continue_turn == false) std::cout << std::endl << players.at(player_loop).get_name() << " earned: " << players.at(player_loop).round_score() << " points.\n" << players.at(player_loop).get_name() << "\'s score: " << players.at(player_loop).get_score() << " points.\n";
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
