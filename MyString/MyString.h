#pragma once

#include <iostream>

class MyString
{
private:
	char* str = nullptr;
	unsigned int size = 0;
	unsigned int capacity = 4;

	void copyFrom(const MyString& other);
	void free();

	void resize(unsigned int newCapacity);
	unsigned int calculateCapacity(unsigned int size) const;
public:
	MyString();
	MyString(const char* str);

	MyString(const MyString& other);
	MyString& operator=(const MyString& other);

	~MyString();

	void setStr(const char* str);

	MyString& operator+=(const MyString& other);
	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend std::istream& operator>>(std::istream& is, MyString& rhs);
	friend std::ostream& operator<<(std::ostream& os, const MyString& rhs);
};

MyString operator+(const MyString& lhs, const MyString& rhs);
std::istream& operator>>(std::istream& is, MyString& rhs);
std::ostream& operator<<(std::ostream& os, const MyString& rhs);