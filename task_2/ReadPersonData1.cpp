#include "Header.h";

using namespace std;


void ReadPersonData(string& name, unsigned short& age) {

	name = ReadPersonName();
	age = ReadPersonAge();
	ReadPersonSalary(&salary);
}