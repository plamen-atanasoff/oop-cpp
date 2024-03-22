#pragma once

#include <iostream>

class ComplexNumber
{
private:
	double re;
	double im;
public:
	ComplexNumber(double re = 0, double im = 0)
		: re(re), im(im) {}

	ComplexNumber& operator+=(const ComplexNumber& cn);
	ComplexNumber& operator-=(const ComplexNumber& cn);
	ComplexNumber& operator*=(const ComplexNumber& cn);
	ComplexNumber& operator/=(const ComplexNumber& cn);
	ComplexNumber& operator-();

	double getRe() const { return re; }
	double getIm() const { return im; }

	ComplexNumber getConjugate() const;

	friend std::istream& operator>>(std::istream& is, ComplexNumber& cn);
	friend std::ostream& operator<<(std::ostream& os, const ComplexNumber cn);
};

ComplexNumber operator+(const ComplexNumber& cn1, const ComplexNumber& cn2);
ComplexNumber operator-(const ComplexNumber& cn1, const ComplexNumber& cn2);
ComplexNumber operator*(const ComplexNumber& cn1, const ComplexNumber& cn2);
ComplexNumber operator/(const ComplexNumber& cn1, const ComplexNumber& cn2);

bool operator==(const ComplexNumber& cn1, const ComplexNumber& cn2);
bool operator!=(const ComplexNumber& cn1, const ComplexNumber& cn2);

std::istream& operator>>(std::istream& is, ComplexNumber& cn);
std::ostream& operator<<(std::ostream& os, const ComplexNumber cn);