#pragma once
#include <vector>
#include "player.h"

class FTable {
	private:
		vector<Player> players;
		unsigned int target_score;
		unsigned int size;
	public:
		FTable();
		void add_player(std::string new_name);
		void add_player(std::string new_name, std::vector<double> new_weights);
		//bool add_bots(unsigned int bot_count);
		void set_target(unsigned int new_target_score);
		unsigned int get_target();
		unsigned int get_size();
		Player *get_player(unsigned int i);
};
