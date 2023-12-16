#include <iostream>
#include <complex>
#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
import Math;
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    int choice;

    cout << "Введите 1, чтобы ввести модуль и аргумент комплексного числа\n        2 - ввести действительную и мнимую части: \n";
    cin >> choice;

    Complex userComplex;

    if (choice == 1) {
        double mod, arg;

        cout << "Введите модуль числа: ";
        cin >> mod;

        cout << "Введите аргумент числа: ";
        cin >> arg;

        userComplex = Complex::FromExponentialForm(mod, arg);
    }
    else if (choice == 2) {
        double re, im;

        cout << "Введите действительную часть числа: ";
        cin >> re;

        cout << "Введите мнимую часть числа: ";
        cin >> im;

        userComplex = Complex::FromAlgebraicForm(re, im);
    }
    else {
        cout << "Выбран неверный пункт!\nПожалуйста, выберите внимательно ещё раз." << endl;

        return 1;
    }

    int nominator, denominator;
    cout << "Введите рациональное число в форме числитель/знаменатель: ";
    
    char separator;
    cin >> nominator >> separator >> denominator;

    Rational userRational(nominator, denominator);

    double userDouble;

    cout << "Введите число c плавающей точкой : ";
    cin >> userDouble;

    cout << "\nf(" << userComplex << ") = " << f(userComplex) << endl;
    cout << "f(" << userRational << ") = " << f(userRational) << endl;
    cout << "f(" << userDouble << ") = " << f(userDouble) << endl;

    return 0;
}