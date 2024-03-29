#include "die.h"
#include <cassert>
using namespace std;

Die::Die() : SIDES(6), last_roll(0) {
	aside = false;
	for (unsigned int i = 0; i < SIDES; i++)
		weight.push_back(1.0/SIDES);
}

Die::Die(vector<double> new_weights, const int new_sides) : SIDES(new_sides), last_roll(0) {
	aside = false;
	assert(new_sides >= 4);
	assert(new_weights.size() == SIDES);
	double sum = 0;
	for (unsigned int i = 0; i < SIDES; i++) {
		assert(new_weights[i] >= 0 && new_weights[i] <= 1);
		sum += new_weights[i];
		weight.push_back(new_weights[i]);
	}
	assert(sum > .99 && sum < 1.01);
}

int Die::get_roll() {
	return last_roll;
}

void Die::roll() {
	double current_roll = (rand() % 99 + 1) / 100.00;
	double low_bound = 0;

	for (unsigned int i(0); i < weight.size(); i++) {
		if (low_bound < current_roll && current_roll <= weight[i] + low_bound) {
			last_roll = i + 1;
			assert(last_roll >= 1 && last_roll <= SIDES);
			break;
		}
		low_bound += weight[i];
	}
}

void Die::set_aside(bool toggle) {
	aside = toggle;
}

bool Die::is_aside() {
	return aside;
}
