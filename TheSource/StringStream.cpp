#include <sstream>
#include <vector>
#include <iostream>
#include "StringStream.h"


StringStream::StringStream()
{
}


StringStream::~StringStream()
{
}

std::vector<int> StringStream::parseInts(std::string str)
{
	std::vector<int> SSVector;
	std::stringstream ss(str);

	int element;
	char ch;
	while (ss) // if stream is good
	{
		if (ss >> element)	// attempt extraction
		{
			// extraction successful
			SSVector.push_back(element);
			if (!(ss >> ch)) // extract comma
			{
				break;
			}
		}
		else
		{
			break;
		}
	}

	return SSVector;
}


void StringStream::Execute()
{
	std::string str;
	std::cin >> str;
	std::vector<int> integers = parseInts(str);

	for (auto element : integers)
	{
		std::cout << element << std::endl;
	}
}