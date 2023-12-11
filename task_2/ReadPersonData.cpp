#include "Header1.h";

using namespace std;


void ReadPersonData(string& name, unsigned short& age) {

	name = ReadPersonName();
	age = ReadPersonAge();
	ReadPersonSalary(&salary);
}

void ReadPersonData(string& name, unsigned short& age, unsigned short& weight) {
	name = ReadPersonName();
	age = ReadPersonAge();
	ReadPersonHeight();
	ReadPersonWeight(weight);
}