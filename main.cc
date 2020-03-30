// cowin && davison
#include <iostream>
#include "die.h"
using namespace std;

int main() {
	srand(time(0));
	cout << "Hello World!\n";
	Die d({.5,.1,.1,.1,.1,.1},6);
	Die d2;
	d.roll();
	d2.roll();
	cout << d.get_roll() << endl;
	cout << d2.get_roll() << endl;
}
