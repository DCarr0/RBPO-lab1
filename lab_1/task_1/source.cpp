#include <iostream>
#include <sstream>

using namespace std;

unsigned short height=0;

double salary;

unsigned short ReadPersonAge(){
	unsigned short age;
	cout << "Input ur age: ";
	cin >> age;

	return age;
}


string ReadPersonName() {
	string name;
	cout << "Input ur name: ";
	cin >> name;

	return name;
}


unsigned short ReadPersonHeight() {
	cout << "Input ur height: ";
	cin >> height;

	return height;
}


unsigned short ReadPersonWeight(unsigned short& weight) {
	cout << "Input ur weight: ";
	cin >> weight;

	return weight;
}


void ReadPersonSalary(double* salary) {
	cout << "Input ur salary: ";
	cin >> *salary;

}


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



void WritePersonData(const unsigned short age, const string& name, const string& height = "", const string& weight = "") {
	cout << "Your name : " << name << "\n" << "Your age : " << age << "\n" << "Your height : " << height << "\n" << "Your weight : " << weight << "\n" << "Your salary : " << salary << endl << endl;
}


#ifndef DO_NOT_DEFINE_MAIN
void main() {
	unsigned short age=0;
	string name;
	unsigned short weight;
	ReadPersonData(name,age);
	WritePersonData( age, name);


	ReadPersonData(name, age, weight);
	WritePersonData(age, name, to_string(height),to_string(weight));

}
#endif
