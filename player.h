#pragma once
#include <vector>

class Player {
	private:
		std::string name;
		unsigned int score;
		std::vector<Die> dice;
		std::vector<unsigned int> pile; // Stores dice that are set aside
	public:
		Player(std::string new_name);
		Player(std::string new_name, std::vector<double> new_weights, unsigned int sides);
		void set_aside(std::vector<unsigned int> scoring_dice);
		void roll(); // Rolls all dice not set aside.
		void print_dice();
};
