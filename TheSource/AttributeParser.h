#pragma once
#include <string>
#include <vector>

/// hackerrank: https://www.hackerrank.com/challenges/attribute-parser

class Tag;

class AttributeParser
{

private:

	Tag FindTagByName(std::vector<Tag> _HRMLTags, std::string _TagName);
	std::string FindTagNameFromTagLine(std::string _TagLine, std::size_t _FoundTagPos);

public:
	AttributeParser();

	void Execute();
};

