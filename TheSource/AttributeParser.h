#pragma once
#include <string>

/// hackerrank: https://www.hackerrank.com/challenges/attribute-parser

class AttributeParser
{

private:

	std::string FindTagName(std::string _TagLine, std::size_t _FoundTagPos);

public:
	AttributeParser();

	void Execute();
};

