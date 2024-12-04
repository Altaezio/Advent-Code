#include <iostream>
#include <source_location>
#include "Solution/J1.h"
#include "Solution/J2.h"
#include "Solution/J3.h"
#include "Solution/J04.h"

int main()
{
	auto solv1 = sol04v1;
	auto solv2 = sol04v2;
	std::string fileName = "J4";

	std::cout << "=== " << fileName << " ===" << std::endl;
	std::cout << "TEST" << std::endl;
	std::cout << "Test solution -1- is : " << solv1("test") << std::endl;
	std::cout << "Test solution -2- is : " << solv2("test") << std::endl;
	std::cout << "REAL" << std::endl;
	std::cout << "Real solution -1- is : " << solv1(fileName) << std::endl;
	std::cout << "Real solution -2- is : " << solv2(fileName) << std::endl;
}
