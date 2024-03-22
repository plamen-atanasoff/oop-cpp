#include <iostream>
#include <cmath>
using namespace std;

struct Point
{
	double x;
	double y;
};

struct Triangle
{
	Point p1;
	Point p2;
	Point p3;
};

void fillPoint(Point& p)
{
	cin >> p.x;
	cin >> p.y;
}

void fillTriangles(Triangle* triangles, size_t count)
{
	for (int i = 0; i < count; ++i)
	{
		fillPoint(triangles[i].p1);
		fillPoint(triangles[i].p2);
		fillPoint(triangles[i].p3);
	}
}

double getLength(const Point& p1, const Point& p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double getArea(const Triangle& t)
{
	double side_a = getLength(t.p1, t.p2);
	double side_b = getLength(t.p1, t.p3);
	double side_c = getLength(t.p3, t.p2);

	double halfP = (side_a + side_b + side_c) / 2;

	return sqrt(halfP * (halfP - side_a) * (halfP - side_b) * (halfP - side_c));
}

double* getAreas(const Triangle* triangles, size_t count)
{
	double* areas = new double[count];
	for (int i = 0; i < count; ++i)
	{
		areas[i] = getArea(triangles[i]);
	}

	return areas;
}

void printAreas(const double* areas, size_t count)
{
	for (int i = 0; i < count; ++i)
	{
		cout << areas[i] << ", ";
	}
}

int main()
{
	unsigned int n;
	cin >> n;

	Triangle* triangles = new Triangle[n];
	fillTriangles(triangles, n);

	double* areas = getAreas(triangles, n);
	printAreas(areas, n);

	delete[] triangles;
	delete[] areas;
}