#include "table.h"
#include <vector>
#include "player.h"

FTable::FTable() {
	target_score = 2000;
	size = 0;
}

void FTable::add_player(std::string new_name) {
	Player temp(new_name, true);
	players.push_back(temp);
}

void FTable::add_player(std::string new_name, std::vector<double> new_weights) {
	Player temp(new_name, true, new_weights, 6);
	players.push_back(temp);
}

//bool Table::add_bots(unsigned int bot_count) {
//	std::string bot_name = "Bot 1";
//	for (unsigned int i(0); i < bot_count; i++) {
//		players.emplace_back({bot_name, false});
//		bot_name[4]++;
//	}
//}

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
