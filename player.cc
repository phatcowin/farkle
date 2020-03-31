#include <cassert>
#include <iostream>
#include "player.h"
#include "colors.h" 

Player::Player(std::string new_name) {
	name = new_name;
	score = 0;
	for (int i(0); i < 6; i++) {
		dice.emplace_back();
	}
}

Player::Player(std::string new_name, std::vector<double> new_weights, unsigned int new_sides) {
	name = new_name;
	score = 0;
	for (int i(0); i < 6; i++) {
		dice.emplace_back(new_weights, new_sides);
	}
}

void Player::set_aside(std::vector<unsigned int> scoring_dice) {
	for (int i(0); i < scoring_dice.size(); i++) {
		pile.push_back(scoring_dice.at(i));
	}
	assert(pile.size() <= 6);
}

void Player::roll() {
	for (int i(0); i < 6; i++) {
		if (dice.at(i).is_aside() == false) dice.at(i).roll();
	}
}

void Player::print_dice() {
	std::cout << name << "'s dice:\n";
	for (unsigned int i(0); i < 6; i++) {
		if (dice.at(i).is_aside() == true) std::cout << RED;
		std::cout << "Die " << i << ": " << dice.at(i).get_roll() << RESET << std::endl;
	}
}
