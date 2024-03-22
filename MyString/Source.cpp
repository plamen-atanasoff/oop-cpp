#include <iostream>

#include "MyString.h"

int main()
{
	MyString str1;
	MyString str2("Hello");
	MyString str3(str1);
	MyString str4(str2);

	str1 = str2;
	str1 += str2;
	str1 += str1;

	MyString str5;
	std::cin >> str5;
	std::cout << str5;
}