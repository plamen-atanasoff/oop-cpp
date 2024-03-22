#include "MyString.h"

#include <iostream>
#include <cstring>
#include <cmath>

void MyString::copyFrom(const MyString& other)
{
	char* tempStr = new char[other.capacity];
	size = other.size;
	capacity = other.capacity;
	strcpy_s(tempStr, capacity, other.str);
	delete[] str;
	str = tempStr;
}

void MyString::free()
{
	delete[] str;
	str = nullptr;
	size = 0;
	capacity = 4;
}

void MyString::resize(unsigned int newCapacity)
{
	char* newStr = new char[newCapacity];
	capacity = newCapacity;
	strcpy_s(newStr, capacity, str);
	delete[] str;
	str = newStr;
}

unsigned int MyString::calculateCapacity(unsigned int size) const
{
	unsigned int maxPowerOf2 = log2(size);
	return pow(2, maxPowerOf2 + 1);
}

MyString::MyString()
{
	size = 1;
	str = new char[capacity];
	strcpy_s(str, capacity, "");
}

MyString::MyString(const char* str)
{
	setStr(str);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
		copyFrom(other);
	return *this;
}

MyString::~MyString()
{
	free();
}

void MyString::setStr(const char* str)
{
	unsigned int newSize = strlen(str) + 1;
	unsigned int newCapacity = calculateCapacity(newSize);
	char* newStr = new char[newCapacity];
	size = newSize;
	capacity = newCapacity;
	strcpy_s(newStr, capacity, str);
	delete[] this->str;
	this->str = newStr;
}

MyString& MyString::operator+=(const MyString& other)
{
	unsigned int newSize = size + other.size - 1;
	unsigned int newCapacity = calculateCapacity(newSize);

	if (newCapacity >= capacity)
		resize(newCapacity);

	char* newStr = new char[newCapacity];
	size = newSize;
	capacity = newCapacity;
	strcpy_s(newStr, capacity, str);
	strcat_s(newStr, capacity, other.str);

	delete[] str;
	str = newStr;

	return *this;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString res(lhs);
	res += rhs;
	return res;
}

std::istream& operator>>(std::istream& is, MyString& rhs)
{
	char buff[1024];
	is.getline(buff, 1024);
	rhs.setStr(buff);
	return is;
}

std::ostream& operator<<(std::ostream& os, const MyString& rhs)
{
	return os << rhs.str;
}
