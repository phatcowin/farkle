#pragma once
#include <vector>
#include <cassert>
#include <cstdlib>
using std::vector;
using std::cout;
using std::endl;

class Die {
	private:
		const unsigned int SIDES;
		vector<double> weight;
		unsigned int last_roll;
		bool aside(false);
	public:
		Die(); //Create a fair die
		Die(vector<double> new_weights, int new_sides); //Create a cheater die
		int get_roll(); //Return the last value rolled
		void roll(); //Set the die to a random value
		void set_aside(bool toggle);
		bool is_aside();
};
