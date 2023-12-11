#include <iostream>
#include "Header1.h";

using namespace std;

double salary;

void ReadPersonSalary(double* salary) {
	cout << "Input ur salary: ";
	cin >> *salary;

}