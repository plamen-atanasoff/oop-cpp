#pragma once
#include <iostream>

class NVector
{
private:
	double* vectorCollection;
	unsigned int dimension;
private:
	void copyCollection(const double* collection);

	void create(unsigned int dim);
	void copyFrom(const NVector& other);
public:
	NVector() = delete;
	NVector(unsigned int dim);
	NVector(unsigned int dim, const double* collection);
	NVector(const NVector& other);

	NVector& operator=(const NVector& other);

	~NVector();

	NVector& operator+=(const NVector& other);
	NVector& operator-=(const NVector& other);
	NVector& operator*=(double scalar);

	double& operator[](unsigned int index);
	double operator[](unsigned int index) const;

	friend std::istream& operator>>(std::istream& is, NVector& vector);
	friend std::ostream& operator<<(std::ostream& os, const NVector& vector);
	friend NVector operator+(const NVector& lhs, const NVector& rhs);
	friend NVector operator-(const NVector& lhs, const NVector& rhs);
	friend bool vectorsAreParallel(const NVector& lhs, const NVector& rhs);
	friend bool vectorsArePerpendicular(const NVector& lhs, const NVector& rhs);
};

NVector operator+(const NVector& lhs, const NVector& rhs);
NVector operator-(const NVector& lhs, const NVector& rhs);

bool vectorsAreParallel(const NVector& lhs, const NVector& rhs);
bool vectorsArePerpendicular(const NVector& lhs, const NVector& rhs);

std::istream& operator>>(std::istream& is, NVector& vector);
std::ostream& operator<<(std::ostream& os, const NVector& vector);