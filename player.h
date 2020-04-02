#pragma once
#include <vector>
#include "die.h"

class Player {
	private:
		std::string name;
		unsigned int score, wallet;
		std::vector<Die> dice;
		bool humanity;
		bool at_table;
		unsigned int risk_index;
	public:
		Player(std::string new_name, bool new_humanity);
		Player(std::string new_name, bool new_humanity, std::vector<double> new_weights, unsigned int sides);
		bool is_human();
		unsigned int get_score();
		void reset_score();
		std::string get_name();
		void set_aside(unsigned int die);
		void set_aside(std::vector<unsigned int> scoring_dice);
		bool roll(); // Rolls all dice not set aside. Returns true if the player busted. Hint: if (player.roll() == true) player.end_turn(true);
		void print_dice();
		void end_turn(bool busted); // Increments score and resets all aside values to false.
		unsigned int round_score();
		void adjust_score(unsigned int adjustment);
		unsigned int aside_count();
		int get_die(int i);
		bool is_aside(int i);
		unsigned int get_wallet();
		unsigned int adjust_wallet(unsigned int i, bool increase);
		bool check_seat();
		void check_funds();
		bool scoring(unsigned int roll);
		unsigned int get_risk();
};
