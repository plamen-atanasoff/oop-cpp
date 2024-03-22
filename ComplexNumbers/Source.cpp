#include <iostream>

#include "ComplexNumber.h"

int main()
{
    ComplexNumber cn;
    ComplexNumber cn2{ 2 };
    ComplexNumber cn3{ 3, 3 };

    ComplexNumber cn4{ cn2 + cn3 };
    std::cout << cn4 + cn3 << std::endl;
    std::cin >> cn;

    std::cout << cn / cn3 << std::endl;
    std::cout << (cn == cn2) << std::endl;
    std::cout << (cn != cn2) << std::endl;
}
