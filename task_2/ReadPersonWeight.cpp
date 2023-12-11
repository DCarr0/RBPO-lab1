#include <iostream>
#include "Header1.h";

using namespace std;

unsigned short ReadPersonWeight(unsigned short& weight) {
	cout << "Input ur weight: ";
	cin >> weight;

	return weight;
}