#include <iostream>

#include "Header.h";

using namespace std;

unsigned short height;

unsigned short ReadPersonHeight() {
	cout << "Input ur height: ";
	cin >> height;

	return height;
}