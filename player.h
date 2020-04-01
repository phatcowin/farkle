#pragma once
#include <vector>
#include "die.h"

class Player {
	private:
		std::string name;
		unsigned int score;
		std::vector<Die> dice;
		bool humanity;
	public:
		Player(std::string new_name, bool new_humanity);
		Player(std::string new_name, bool new_humanity, std::vector<double> new_weights, unsigned int sides);
		bool is_human();
		unsigned int get_score();
		void set_aside(std::vector<unsigned int> scoring_dice);
		bool roll(); // Rolls all dice not set aside. Returns true if the player busted. Hint: if (player.roll() == true) player.end_turn(true);
		void print_dice();
		void end_turn(bool busted); // Increments score and resets all aside values to false.
};
