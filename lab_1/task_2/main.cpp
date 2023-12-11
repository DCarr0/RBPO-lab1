#include <sstream>
#include "Header.h";

using namespace std;

void main() {
	unsigned short age = 0;
	string name;
	unsigned short weight;
	ReadPersonData(name, age);
	WritePersonData(age, name);


	ReadPersonData(name, age, weight);
	WritePersonData(age, name, to_string(height), to_string(weight));

}