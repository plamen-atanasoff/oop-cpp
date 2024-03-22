#include <cmath>

#include "NVector.h"

int main()
{
	double collection1[] = { 1, 1, 1 };
	double collection2[] = { 3, 3, 3 };
	double collection3[] = { 5, 0, 0 };
	double collection4[] = { 0, 7, 0 };
	NVector a(3);
	NVector b(3, collection1);
	NVector c(3, collection2);
	NVector d(3, collection3);
	NVector e(3, collection4);

	a += b + c;
	std::cout << vectorsAreParallel(b, c);
	std::cout << vectorsArePerpendicular(b, c);

	std::cout << vectorsAreParallel(d, e);
	std::cout << vectorsArePerpendicular(d, e);
}