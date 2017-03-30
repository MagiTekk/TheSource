#include "AttributeParser.h"
#include <iostream>
#include <string>
#include <vector>


AttributeParser::AttributeParser()
{
}

/*	
	The opening tags follow the format:
	<tag-name attribute1-name = "value1" attribute2-name = "value2" ... >

	The closing tags follow the format:
	< /tag-name >

	--Sample Input
	4 3
	<tag1 value = "HelloWorld">
	<tag2 name = "Name1">
	< / tag2>
	< / tag1>
	tag1.tag2~name
	tag1~name
	tag1~value

	--Sample Output
	Name1
	Not Found!
	HelloWorld
*/

void AttributeParser::Execute()
{
	std::cout << "Please insert the number of lines and number of queries. e.g. 2 1" << std::endl;

	std::vector<std::string> HRMLTags;
	std::vector<int> Queries;
	int NumberOfLines;
	int QueryAmount;

	// Read amount of tags and queries
	std::cin >> NumberOfLines >> QueryAmount;

	// This will clear out the input buffer, in case we have any withespaces after reading the numbers
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	bool TagOpened = false;

	// Read line
	for (int i = 0; i < NumberOfLines; ++i)
	{
		std::cout << "Please insert line number " << i+1 << std::endl;

		// Store line
		std::string line;
		std::getline(std::cin, line);

		// Check if it's a starting tag or an ending tag
		std::size_t foundSlash = line.find("/");
		std::size_t foundTag = line.find("tag");
		if (foundSlash == std::string::npos && foundTag != std::string::npos)
		{
			// Found a tag
			std::cout << "Line is a tag" << std::endl;
			HRMLTags.push_back(line);
		}
		else if (foundSlash == std::string::npos)
		{
			// Line was something else, handle exception
			std::cout << "The line you inserted is neither a tag or an ending tag, please try again" << std::endl;
		}
		else
		{
			// Line was an ending tag
			std::cout << "line is an ending tag :: Line: " << line << std::endl;
		}
	}

	//std::cout << TagsAmount << " -- " << QueryAmount << std::endl;
}
