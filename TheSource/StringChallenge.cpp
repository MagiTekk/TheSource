#include "StringChallenge.h"
#include <iostream>
#include <string>


StringChallenge::StringChallenge()
{
}


StringChallenge::~StringChallenge()
{
}

void StringChallenge::Execute()
{
	std::string a = "";
	std::string b = "";

	std::cin >> a >> b;
	std::cout << a.size() << " " << b.size() << std::endl;
	std::cout << a + b << std::endl;

	// swap fist char of each string
	char fChar = a[0];
	char sChar = b[0];
	a[0] = sChar;
	b[0] = fChar;
	std::cout << a << " " << b << std::endl;
}