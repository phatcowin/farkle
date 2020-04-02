#pragma once
#include <vector>
#include "player.h"

class FTable {
	private:
		vector<Player> players;
		unsigned int target_score;
		unsigned int size;
		unsigned int pot;
	public:
		FTable();
		void add_player(std::string new_name);
		void add_player(std::string new_name, std::vector<double> new_weights);
		void  add_bot(std::string new_name, std::vector<double> new_weights);
		void set_target(unsigned int new_target_score);
		unsigned int get_target();
		unsigned int get_size();
		Player *get_player(unsigned int i);
		std::string start_round(unsigned int wager);
		void reset();
		void print_wallets();
		unsigned int max_wager();
		unsigned int remaining_players();
		unsigned int check_pot();
		void check_seats();
};
