#include <iostream>
#include <chrono>
#include "Solution/Visualiser/Application.h"
#include "Solution/J1.h"
#include "Solution/J2.h"
#include "Solution/J3.h"
#include "Solution/J04.h"
#include "Solution/J05.h"
#include "Solution/J06.h"
#include "Solution/J07.h"
#include "Solution/J08.h"
#include "Solution/J09.h"
#include "Solution/J10.h"
#include "Solution/J11.h"
#include "Solution/J12.h"

int main()
{
	auto solv1 = sol12v1;
	auto solv2 = sol12v2;
	std::string fileName = "J12";

	std::cout << "=== " << fileName << " ===" << std::endl;
	auto startTest1 = std::chrono::steady_clock::now();
	std::cout << "TEST solution -1- is : " << solv1("test") << std::endl;
	auto endTest1 = std::chrono::steady_clock::now();
	auto diff = endTest1 - startTest1;
	std::cout << "in " << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;

	std::cout << "REAL solution -1- is : " << solv1(fileName) << std::endl;
	auto endReal1 = std::chrono::steady_clock::now();
	diff = endReal1 - endTest1;
	std::cout << "in " << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;

	std::cout << std::endl;
	std::cout << "TEST solution -2- is : " << solv2("test") << std::endl;
	auto endTest2 = std::chrono::steady_clock::now();
	diff = endTest2 - endReal1;
	std::cout << "in " << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;
	std::cout << "REAL solution -2- is : " << solv2(fileName) << std::endl;
	auto endReal2 = std::chrono::steady_clock::now();
	diff = endReal2 - endTest2;
	std::cout << "in " << std::chrono::duration<double, std::milli>(diff).count() << "ms" << std::endl;

	//StartApplication(fileName);
}
