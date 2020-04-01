#include <cassert>
#include <iostream>
#include "player.h"
#include "colors.h"
#include "die.h"

Player::Player(std::string new_name, bool new_humanity) {
	name = new_name;
	score = 0;
	humanity = new_humanity;
	for (int i(0); i < 6; i++) {
		dice.emplace_back();
	}
}

Player::Player(std::string new_name, bool new_humanity, std::vector<double> new_weights, unsigned int new_sides) {
	name = new_name;
	score = 0;
	humanity = new_humanity;
	for (int i(0); i < 6; i++) {
		dice.emplace_back(new_weights, new_sides);
	}
}

bool Player::is_human() {
	return humanity;
}

unsigned int Player::get_score() {
	return score;
}

void Player::set_aside(std::vector<unsigned int> scoring_dice) {
	for (unsigned int i(0); i < scoring_dice.size(); i++) {
		dice.at(scoring_dice.at(i)).set_aside(true);
	}
}

bool Player::roll() {
	bool busted = true;

	for (unsigned int i(0); i < 6; i++) {
		if (dice.at(i).is_aside() == false) dice.at(i).roll();
		if (busted == true) if (dice.at(i).get_roll() == 1 || dice.at(i).get_roll() == 5) busted = false;
	}
	for (unsigned int i(0); i < 6 && busted == true; i++) {
		if (dice.at(i).is_aside() == false) {
			unsigned int count = 0;
			for (unsigned int x(0); x < 6; x++) {
				if (x != i && dice.at(i).get_roll() == dice.at(x).get_roll()) count++;
			}
			if (count >= 3) busted = false;
		}
	}
	return busted;
}

void Player::print_dice() {
	std::cout << name << "\'s dice:\n";
	for (unsigned int i(0); i < 6; i++) {
		if (dice.at(i).is_aside() == true) std::cout << RED;
		std::cout << "Die " << i << ": " << dice.at(i).get_roll() << RESET << std::endl;
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
