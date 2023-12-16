module;
#include <math.h>
#include <iostream>

export module Math;
double epsilon = 1e-15;

export class Complex
{

	double m_mod;
	double m_arg;

public:
	Complex() : m_mod(0), m_arg(0) {}
	Complex(double mod) : m_mod(mod), m_arg(0) {}
	Complex(double re, double im) : m_mod(sqrt(re*re + im*im)), m_arg(atan2(im,re)) {}

	Complex static FromExponentialForm(double mod, double arg) {
		Complex object{ mod * cos(arg), mod * sin(arg) };

		return object;
	}
	Complex static FromAlgebraicForm(double re, double im) {
		Complex object{ re, im };

		return object;
	}

	double Mod() const {

		return m_mod;
	}

	double Arg() const {
		if (abs(m_mod * cos(m_arg)) < 0.000001 && abs(m_mod * sin(m_arg)) < 0.000001) {
			return 0;
		}

		return m_arg;
	}

	double Re() const {

		return m_mod * cos(m_arg);
	}

	double Im() const {

		return m_mod * sin(m_arg);
	}

	explicit operator double() { return Re(); }

	Complex operator-() const {
		
		return Complex(-Re(), -Im());
	}

	Complex& operator++() {
		double m_re = Re() + 1;
		double m_im = Im();
		m_mod = sqrt(m_re*m_re + m_im*m_im);
		m_arg = atan2(m_im,m_re);

		return *this;
	}

	Complex operator++(int) {
		Complex object(*this);
		++(*this);

		return object;
	}

	Complex& operator--() {
		double m_re = Re() - 1;
		double m_im = Im();
		m_mod = sqrt(m_re * m_re + m_im * m_im);
		m_arg = atan2(m_im, m_re);

		return *this;
	}

	Complex operator--(int) {
		Complex object(*this);
		--(*this);

		return object;
	}

	Complex& operator+=(Complex rhs) {
		double m_re = Re();
		double m_im = Im();
		m_re += rhs.m_mod * cos(rhs.m_arg);
		m_im += rhs.m_mod * sin(rhs.m_arg);

		m_mod = sqrt(m_re * m_re + m_im * m_im);
		m_arg = atan2(m_im, m_re);

		return *this;
	}

	Complex& operator-=(Complex rhs) {
		double m_re = Re();
		double m_im = Im();
		m_re -= rhs.m_mod * cos(rhs.m_arg);
		m_im -= rhs.m_mod * sin(rhs.m_arg);

		m_mod = sqrt(m_re * m_re + m_im * m_im);
		m_arg = atan2(m_im, m_re);

		return *this;
	}

	Complex& operator*=(Complex rhs) {
		m_mod *= rhs.m_mod;
		m_arg += rhs.m_arg;

		return *this;
	}

	Complex& operator/=(Complex rhs) {
		m_mod /= rhs.m_mod;
		m_arg -= rhs.m_arg;

		return *this;
	}

	friend Complex operator+(const Complex&, const Complex&);
	friend Complex operator-(const Complex&, const Complex&);
	friend Complex operator*(const Complex&, const Complex&);
	friend Complex operator/(const Complex&, const Complex&);
	friend std::ostream& operator<<(std::ostream&, const Complex&);
	friend Complex operator ""i(long double);
	friend Complex operator ""i(unsigned long long);
};

export Complex operator+(const Complex& lhs, const Complex& rhs) {
	double m_re = lhs.m_mod * cos(lhs.m_arg) + rhs.m_mod * cos(rhs.m_arg);
	double m_im = lhs.m_mod * sin(lhs.m_arg) + rhs.m_mod * sin(rhs.m_arg);

	return Complex(m_re, m_im);
}

export Complex operator-(const Complex& lhs, const Complex& rhs) {
	double m_re = lhs.m_mod * cos(lhs.m_arg) - rhs.m_mod * cos(rhs.m_arg);
	double m_im = lhs.m_mod * sin(lhs.m_arg) - rhs.m_mod * sin(rhs.m_arg);

	return Complex(m_re, m_im);
}

export Complex operator*(const Complex& lhs, const Complex& rhs) {
	double m_reLhs = lhs.m_mod * cos(lhs.m_arg);
	double m_reRhs = rhs.m_mod * cos(rhs.m_arg);
	double m_imLhs = lhs.m_mod * sin(lhs.m_arg);
	double m_imRhs = rhs.m_mod * sin(rhs.m_arg);

	double m_re = m_reLhs * m_reRhs - m_imLhs * m_imRhs;
	double m_im = m_reLhs * m_imRhs + m_imLhs * m_reRhs;

	return Complex(m_re, m_im);
}

export Complex operator/(const Complex& lhs, const Complex& rhs) {
	double m_reLhs = lhs.m_mod * cos(lhs.m_arg);
	double m_reRhs = rhs.m_mod * cos(rhs.m_arg);
	double m_imLhs = lhs.m_mod * sin(lhs.m_arg);
	double m_imRhs = rhs.m_mod * sin(rhs.m_arg);

	double m_re = (m_reLhs * m_reRhs + m_imLhs * m_imRhs) / (m_reRhs * m_reRhs + m_imRhs * m_imRhs);
	double m_im = (m_reRhs * m_imLhs - m_reLhs * m_imRhs) / (m_reRhs * m_reRhs + m_imRhs * m_imRhs);

	return Complex(m_re, m_im);
}

export Complex operator ""i(unsigned long long m_im) {
	
	return Complex(0.0, (double)m_im);
}

export Complex operator ""i(long double m_im) {
	
	return Complex(0.0, (double)m_im);
}

export std::ostream& operator<<(std::ostream& stream, const Complex& inst) {
	double m_re = inst.m_mod * cos(inst.m_arg);
	double m_im = inst.m_mod * sin(inst.m_arg);
	
	stream << std::fixed << m_re << (m_im < 0 ? "" : "+") << m_im << "i";


	return stream;
}

export int FindGreatestCommonDivisor(int a, int b) {
	a = std::abs(a);
	b = std::abs(b);

	while (a != 0 && b != 0) {
		if (a > b) {
			a %= b;
		}
		else {
			b %= a;
		}
	}
	return a + b;
}

export int FindLeastCommonMultiple(int a, int b) {
	return abs(a * b) / FindGreatestCommonDivisor(a, b);
}


export class Rational
{

	int m_nominator;
	int m_denominator;

	void normirovanie() {
		int nod = FindGreatestCommonDivisor(m_nominator, m_denominator);
		m_nominator /= nod;
		m_denominator /= nod;
		if (m_denominator < 0) {
			m_denominator *= -1;
			m_nominator *= -1;
		}
	}

public:
	Rational(): m_nominator(0), m_denominator(1) {}
	Rational(int nominator) : m_nominator(nominator), m_denominator(1) { normirovanie(); }
	Rational(int nominator, int denominator) : m_nominator(nominator), m_denominator(denominator) { normirovanie(); }
	
	int Nominator() const {

		return m_nominator;
	}

	int Denominator() const {

		return m_denominator;
	}

	explicit operator double() const {

		return (double)Nominator() / Denominator();
	}

	Rational operator-() const {

		return Rational(-Nominator(), Denominator());
	}


	Rational& operator++()
	{
		m_nominator += Denominator();
		normirovanie();

		return *this;
	}

	Rational operator++(int)
	{
		Rational object(*this);
		++(*this);
		normirovanie();

		return object;
	}


	Rational& operator--()
	{
		m_nominator -= Denominator();
		normirovanie();

		return *this;
	}

	Rational operator--(int)
	{
		Rational object(*this);
		--(*this);
		normirovanie();

		return object;
	}

	Rational& operator+=(Rational rhs) {
		int nok = FindLeastCommonMultiple(Denominator(), rhs.m_denominator);
		m_nominator = nok / Denominator() * Nominator();
		m_nominator += nok / rhs.m_denominator * rhs.m_nominator;
		m_denominator = nok;
		normirovanie();

		return *this;
	}

	Rational& operator-=(Rational rhs) {
		int nok = FindLeastCommonMultiple(Denominator(), rhs.m_denominator);
		m_nominator = nok / Denominator() * Nominator();
		m_nominator -= nok / rhs.m_denominator * rhs.m_nominator;
		m_denominator = nok;
		normirovanie();

		return *this;
	}

	Rational& operator*=(Rational rhs) {
		m_nominator *= rhs.m_nominator;
		m_denominator *= rhs.m_denominator;
		normirovanie();

		return *this;
	}

	Rational& operator/=(Rational rhs) {
		m_nominator *= rhs.m_denominator;
		m_denominator *= rhs.m_nominator;
		normirovanie();

		return *this;
	}

	friend Rational operator+ (const Rational& lhs, const Rational& rhs);
	friend Rational operator- (const Rational& lhs, const Rational& rhs);
	friend Rational operator* (const Rational& lhs, const Rational& rhs);
	friend Rational operator/(const Rational& lhs, const Rational& rhs);
	friend bool operator==(const Rational& lhs, const Rational& rhs);
	friend bool operator>(const Rational& lhs, const Rational& rhs);
	friend bool operator<(const Rational& lhs, const Rational& rhs);
	friend bool operator>=(const Rational& lhs, const Rational& rhs);
	friend bool operator<=(const Rational& lhs, const Rational& rhs);
	friend std::ostream& operator<<(std::ostream& stream, const Rational& instance);

};

export Rational operator+ (const Rational& lhs, const Rational& rhs) {
	int denominator = FindLeastCommonMultiple(lhs.m_denominator, rhs.m_denominator);
	int nominator = denominator / lhs.m_denominator * lhs.m_nominator;
	nominator += denominator / rhs.m_denominator * rhs.m_nominator;

	return Rational(nominator, denominator);
}

export Rational operator-(const Rational& lhs, const Rational& rhs){
	int denominator = FindLeastCommonMultiple(lhs.m_denominator, rhs.m_denominator);
	int nominator = denominator / lhs.m_denominator * lhs.m_nominator;
	nominator -= denominator / rhs.m_denominator * rhs.m_nominator;

	return Rational{ nominator, denominator };
}

export Rational operator*(const Rational& lhs, const Rational& rhs){

	return Rational(lhs.m_nominator * rhs.m_nominator, rhs.m_denominator * lhs.m_denominator);
}

export Rational operator/(const Rational& lhs, const Rational& rhs){

	return Rational(lhs.m_nominator * rhs.m_denominator, lhs.m_denominator * rhs.m_nominator);
}

export bool operator==(const Rational& lhs, const Rational& rhs){

	return lhs.m_nominator == rhs.m_nominator && lhs.m_denominator == rhs.m_denominator;
}

export bool operator>(const Rational& lhs, const Rational& rhs){
	int nok = FindLeastCommonMultiple(lhs.m_denominator, rhs.m_denominator);

	return nok / lhs.m_denominator * lhs.m_nominator > nok / rhs.m_denominator * rhs.m_nominator;
}

export bool operator<(const Rational& lhs, const Rational& rhs){
	int nok = FindLeastCommonMultiple(lhs.m_denominator, rhs.m_denominator);

	return nok / lhs.m_denominator * lhs.m_nominator < nok / rhs.m_denominator * rhs.m_nominator;
}

export bool operator>=(const Rational& lhs, const Rational& rhs){
	int nok = FindLeastCommonMultiple(lhs.m_denominator, rhs.m_denominator);

	return nok / lhs.m_denominator * lhs.m_nominator >= nok / rhs.m_denominator * rhs.m_nominator;
}

export bool operator<=(const Rational& lhs, const Rational& rhs){
	int nok = FindLeastCommonMultiple(lhs.m_denominator, rhs.m_denominator);

	return nok / lhs.m_denominator * lhs.m_nominator <= nok / rhs.m_denominator * rhs.m_nominator;
}

export std::ostream& operator<<(std::ostream& stream, const Rational& inst) {
	stream << inst.m_nominator << "/" << inst.m_denominator;

	return stream;
}

export Complex f(const Complex& u) {
	Complex a = Complex(0.0, 5);

	return u / 3 - 1 / (a + u);
}

export Rational f(const Rational& r) {
	Rational a(1, 5);

	return r / 3 - 1 / (a + r);
}

export double f(double x) {
	double a = 0.2;

	return x / 3 - 1 / (a + x);
}