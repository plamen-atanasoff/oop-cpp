#include "NVector.h"

#include <iostream>

void NVector::copyCollection(const double* collection)
{
	for (int i = 0; i < dimension; ++i)
	{
		vectorCollection[i] = collection[i];
	}
}

void NVector::copyFrom(const NVector& other)
{
	dimension = other.dimension;
	copyCollection(other.vectorCollection);
}

void NVector::create(unsigned int dim)
{
	vectorCollection = new double[dim];
	dimension = dim;
}

NVector::NVector(unsigned int dim)
{
	create(dim);
}

NVector::NVector(unsigned int dim, const double* collection)
{
	double a = sizeof(*collection) * (double)dim;
	double b = sizeof(double);
	if (fabs(a / b - dim) >= 0.1)
		return; //exception
	create(dim);
	copyCollection(collection);
}

NVector::NVector(const NVector& other)
{
	create(other.dimension);
	copyFrom(other);
}

NVector& NVector::operator=(const NVector& other)
{
	if (dimension != other.dimension)
		return *this; //exception
	copyFrom(other);
	return *this;
}

NVector::~NVector()
{
	delete[] vectorCollection;
	vectorCollection = nullptr;
	dimension = 0;
}

NVector& NVector::operator+=(const NVector& other)
{
	if (dimension != other.dimension)
		return *this; //exception
	for (int i = 0; i < dimension; ++i)
	{
		vectorCollection[i] += other.vectorCollection[i];
	}

	return *this;
}

NVector& NVector::operator-=(const NVector& other)
{
	if (dimension != other.dimension)
		return *this; //exception
	for (int i = 0; i < dimension; ++i)
	{
		vectorCollection[i] -= other.vectorCollection[i];
	}

	return *this;
}

NVector& NVector::operator*=(double scalar)
{
	for (int i = 0; i < dimension; ++i)
	{
		vectorCollection[i] *= scalar;
	}

	return *this;
}

double& NVector::operator[](unsigned int index)
{
	if (index >= dimension)
		return vectorCollection[0]; //exception
	return vectorCollection[index];
}

double NVector::operator[](unsigned int index) const
{
	if (index >= dimension)
		return vectorCollection[0]; //exception
	return vectorCollection[index];
}

NVector operator+(const NVector& lhs, const NVector& rhs)
{
	NVector temp(lhs.dimension); //move this down
	if (lhs.dimension != rhs.dimension)
		return temp; //exception
	temp += rhs;

	return temp;
}

NVector operator-(const NVector& lhs, const NVector& rhs)
{
	NVector temp(lhs.dimension); //move this down
	if (lhs.dimension != rhs.dimension)
		return temp; //exception
	temp -= rhs;

	return temp;
}

bool vectorsAreParallel(const NVector& lhs, const NVector& rhs)
{
	if (lhs.dimension != rhs.dimension)
		return false; //exception
	double ratio = lhs.vectorCollection[0] / rhs.vectorCollection[0];
	for (int i = 1; i < lhs.dimension; ++i)
	{
		double currentRatio = lhs.vectorCollection[i] / rhs.vectorCollection[i];
		if (fabs(currentRatio - ratio) >= 0.1)
			return false;
	}
	return true;
}

bool vectorsArePerpendicular(const NVector& lhs, const NVector& rhs)
{
	if (lhs.dimension != rhs.dimension)
		return false; //exception
	double sum = 0.0;
	for (int i = 0; i < lhs.dimension; ++i)
	{
		sum += lhs.vectorCollection[i] * rhs.vectorCollection[i];
	}
	if (fabs(sum) < 0.1)
		return true;
	else
		return false;
}

std::istream& operator>>(std::istream& is, NVector& vector)
{
	for (int i = 0; i < vector.dimension; ++i)
	{
		is >> vector[i];
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, const NVector& vector)
{
	for (int i = 0; i < vector.dimension; ++i)
	{
		os << vector[i];
	}

	return os;
}
