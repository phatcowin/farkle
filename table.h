#pragma once
#include <vector>
#include "player.h"

class Table {
	private:
		vector<Player> players;
	public:
		Table();
		bool add_players(unsigned int players);
		bool add_bots(unsigned int bots);
		Player *get_player(unsigned int i);
};
