#include <iostream>
#include <iomanip>
#include "BasicDataTypes.h"



BasicDataTypes::BasicDataTypes()
{
}


BasicDataTypes::~BasicDataTypes()
{
}

//https://www.hackerrank.com/challenges/c-tutorial-basic-data-types
void BasicDataTypes::Execute()
{
	int value_int = 0;
	long value_long = 0;
	long long value_longlong = 0;
	char value_char = '-';
	float value_float = 0;
	double value_double = 0;

	//std::cout << "Insert all space-separated values" << std::endl;
	std::cin >> value_int >> value_long >> value_longlong >> value_char >> value_float >> value_double;


	std::cout << value_int << std::endl;
	std::cout << value_long << std::endl;
	std::cout << value_longlong << std::endl;
	std::cout << value_char << std::endl;

	std::cout << std::fixed;
	std::cout << std::setprecision(3) << value_float << std::endl;
	std::cout << std::setprecision(9) << value_double << std::endl;
}
