#include <iostream>;


using namespace std;

extern unsigned short height;

extern double salary;

unsigned short ReadPersonAge();

string ReadPersonName();

unsigned short ReadPersonHeight();

unsigned short ReadPersonWeight(unsigned short& weight);

void ReadPersonSalary(double* salary);

void ReadPersonData(string& name, unsigned short& age);

void ReadPersonData(string& name, unsigned short& age, unsigned short& weight);

void WritePersonData(const unsigned short age, const string& name, const string& height = "", const string& weight = "");
