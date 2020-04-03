#include <cassert>
#include <iostream>
#include "player.h"
#include "colors.h"
#include "die.h"

Player::Player(std::string new_name, bool new_humanity) {
	name = new_name;
	score = 0;
	humanity = new_humanity;
	wallet = 1000;
	at_table = true;
	risk_index = (rand() % 10 + 4) * 50;
	if (humanity == false) std::cout << name << " created!\n";
	for (int i(0); i < 6; i++) {
		dice.emplace_back();
	}
}

Player::Player(std::string new_name, bool new_humanity, std::vector<double> new_weights, unsigned int new_sides) {
	name = new_name;
	score = 0;
	humanity = new_humanity;
	wallet = 1000;
	at_table = true;
	risk_index = (rand() % 5 + 4) * 100;
	for (int i(0); i < 6; i++) {
		dice.emplace_back(new_weights, new_sides);
	}
	if (new_weights.at(0) == 1) std::cout << YELLOW << "God mode enabled.\n" << RESET;
}

bool Player::is_human() {
	return humanity;
}

unsigned int Player::get_score() {
	return score;
}

void Player::reset_score() {
	score = 0;
}

std::string Player::get_name() {
	return name;
}

void Player::set_aside(unsigned int die) {
	if (dice.at(die - 1).is_aside() == true) std::cout << RED << "This die is already set aside.\n" << RESET;
	else {
		dice.at(die - 1).set_aside(true);
		std::cout << "Die " << die << " set aside.\n";
	}
}

void Player::set_aside(std::vector<unsigned int> scoring_dice) {
	for (unsigned int i(0); i < scoring_dice.size(); i++) {
		dice.at(scoring_dice.at(i)).set_aside(true);
	}
}

bool Player::roll() {
	bool busted = true;

	for (unsigned int i(0); i < 6; i++) {
		if (dice.at(i).is_aside() == false) {
			dice.at(i).roll();
			if (dice.at(i).get_roll() == 1 || dice.at(i).get_roll() == 5) busted = false;
		}
	}
	if (busted == true) {
		std::vector<unsigned int> count = {0,0,0,0,0,0};
		for (unsigned int i(0); i < 6; i++) count.at(dice.at(i).get_roll() - 1)++;
		for (unsigned int i(0); i < 6; i++) if (dice.at(i).is_aside() == false && count.at(dice.at(i).get_roll() - 1) >= 3) busted = false;
	}

	return busted;
}

void Player::print_dice() {
	std::cout << name << "\'s dice:\n";
	for (unsigned int i(0); i < 6; i++) {
		if (dice.at(i).is_aside() == true) std::cout << RED;
		std::cout << "Die " << i + 1 << ": " << dice.at(i).get_roll() << RESET << std::endl;
	}
}

void Player::end_turn(bool busted) {
	unsigned int points = 0;
	if (busted == false) {
		std::vector<unsigned int> count;
		for (int i(0); i < 6; i++) count.push_back(0);
		
		for (unsigned int i(0); i < 6; i++) {
			count.at(dice.at(i).get_roll() - 1)++;
		}
		
		for (unsigned int i(0); i < 6; i++) {
			if (i == 0) {
				if (count.at(i) < 3) points += count.at(i) * 100;
				else {
					unsigned int y = 1000;
					for (int x(count.at(i)); x > 3; x--) y *= 2;
					points += y;
				}
			}

			else if (i == 4 && count.at(i) < 3) points += count.at(i) * 50;

			else {
				if (count.at(i) >= 3) {
					unsigned int y = (i + 1) * 100;
					for (int x(count.at(i)); x > 3; x++) y *= 2;
					points += y;
				}
			}
		}
	}
	score += points;
	for (unsigned int i(0); i < 6; i++) dice.at(i).set_aside(false);
}

unsigned int Player::round_score() {
	unsigned int points = 0;
	std::vector<unsigned int> count = {0,0,0,0,0,0};
	for (unsigned int i(0); i < 6; i++) count.at(dice.at(i).get_roll() - 1)++;

	for (unsigned int i(0); i < 6; i++) {
		if (i == 0) {
			if (count.at(i) < 3) points += count.at(i) * 100;
			else {
				unsigned int y = 1000;
				for (int x(count.at(i)); x > 3; x--) y *= 2;
				points += y;
			}
		}

		else if (i == 4 && count.at(i) < 3) points += count.at(i) * 50;

		else {
			if (count.at(i) >= 3) {
				unsigned int y = (i + 1) * 100;
				for (int x(count.at(i)); x > 3; x--) y *= 2;
				points += y;
			}
		}
	}
	return points;
}

void Player::adjust_score(unsigned int adjustment) {
	score += adjustment;
}

unsigned int Player::aside_count() {
	unsigned int count = 0;
	for (int i(0); i < 6; i++) if (dice.at(i).is_aside() == true) count++;
	return count;
}

int Player::get_die(int i) {
	return dice.at(i).get_roll();
}

bool Player::is_aside(int i) {
	return dice.at(i).is_aside();
}

unsigned int Player::get_wallet() {
	return wallet;
}

unsigned int Player::adjust_wallet(unsigned int i, bool increase) {
	if (wallet == 0) return 0;
	if (increase == true) {
		wallet += i;
		return i;
	}
	else {
		if (wallet > i) {
			wallet -= i;
			return i;
		}
		else {
			unsigned int retval = i - wallet;
			wallet = 0;
			return i - retval;
		}
	}
}

void Player::check_funds() {
	if (wallet < 1) at_table = false;
}

bool Player::check_seat() {
	return at_table;
}

bool Player::scoring(unsigned int roll) {
	if (roll == 5 || roll == 1) return true;

	int count = 0;
	for (unsigned int i(0); i < 6; i++) {
		if (dice.at(i).get_roll() == roll) count++;
	}
	if (count >= 3) return true;
	else return false;
}

unsigned int Player::get_risk() {
	return risk_index;
}
