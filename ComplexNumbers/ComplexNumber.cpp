#include "ComplexNumber.h"

#include <iostream>

ComplexNumber& ComplexNumber::operator+=(const ComplexNumber& cn)
{
	re += cn.re;
	im += cn.im;

	return *this;
}

ComplexNumber& ComplexNumber::operator-=(const ComplexNumber& cn)
{
	re -= cn.re;
	im -= cn.im;

	return *this;
}

ComplexNumber& ComplexNumber::operator*=(const ComplexNumber& cn)
{
	double oldRe = re;
	re = re * cn.re - im * cn.im;
	im = oldRe * cn.im + im * cn.re;

	return *this;
}

ComplexNumber& ComplexNumber::operator/=(const ComplexNumber& cn)
{
	if (cn.re == 0 && cn.im == 0)
		return *this; // exception

	ComplexNumber cnCopy(*this);
	cnCopy *= cn.getConjugate();
	double denom = cn.re * cn.re + cn.im * cn.im;
	re = cnCopy.re / denom;
	im = cnCopy.im / denom;

	return *this;
}

ComplexNumber& ComplexNumber::operator-()
{
	re = -re;
	im = -im;

	return *this;
}

ComplexNumber ComplexNumber::getConjugate() const
{
	return ComplexNumber(re, -im);
}

std::istream& operator>>(std::istream& is, ComplexNumber& cn)
{
	return is >> cn.re >> cn.im;
}

std::ostream& operator<<(std::ostream& os, const ComplexNumber cn)
{
	return os << cn.re << " + " << cn.im << "i";
}

ComplexNumber operator+(const ComplexNumber& cn1, const ComplexNumber& cn2)
{
	ComplexNumber temp(cn1);
	temp += cn2;

	return temp;
}

ComplexNumber operator-(const ComplexNumber& cn1, const ComplexNumber& cn2)
{
	ComplexNumber temp(cn1);
	temp -= cn2;

	return temp;
}

ComplexNumber operator*(const ComplexNumber& cn1, const ComplexNumber& cn2)
{
	ComplexNumber temp(cn1);
	temp *= cn2;

	return temp;
}

ComplexNumber operator/(const ComplexNumber& cn1, const ComplexNumber& cn2)
{
	ComplexNumber temp(cn1);
	temp /= cn2;

	return temp;
}

bool operator==(const ComplexNumber& cn1, const ComplexNumber& cn2)
{
	return cn1.getRe() == cn2.getRe() && cn1.getIm() == cn2.getIm();
}

bool operator!=(const ComplexNumber& cn1, const ComplexNumber& cn2)
{
	return !(cn1 == cn2);
}
