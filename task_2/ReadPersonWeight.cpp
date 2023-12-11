#include <iostream>
#include "Header.h";

using namespace std;

unsigned short ReadPersonWeight(unsigned short& weight) {
	cout << "Input ur weight: ";
	cin >> weight;

	return weight;
}