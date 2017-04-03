#include "AttributeParser.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm> // std::count

class Tag
{
private:

	std::string TagName;
	std::string TagContents;
	std::vector<Tag*> ChildrenTags;
	std::map<std::string, std::string> TagAttributes;

	void ParseAttributes()
	{
		// Using the TagContents, parse all attributes
		std::size_t lastFoundPos = 0;
		
		std::size_t AssignmentCount = std::count(TagContents.begin(), TagContents.end(), '=');
		for (int i = 0; i < AssignmentCount; ++i)
		{
			// Find the next "=" sign
			lastFoundPos = TagContents.find_first_of("=", lastFoundPos + 1);

			// Copy contents from left side
			auto attrName = SubstrValueFromContent(lastFoundPos, true);

			// Copy contents from right side
			auto attrValue = SubstrValueFromContent(lastFoundPos, false);

			std::cout << "attrName found!: " << attrName << std::endl;
			std::cout << "attrValue found!: " << attrValue << std::endl;

			// Add to map
			TagAttributes.insert(std::make_pair(attrName, attrValue));
		}
	}

	std::string SubstrValueFromContent(std::size_t assignmentPos, bool bSubstrToTheLeft)
	{
		bool bEndReached = false;
		auto somePos = assignmentPos;
		std::size_t substringStart = 0;
		std::size_t substringEnd = 0;
		std::string AttrValue = "";

		// Copy contents from left side
		if (bSubstrToTheLeft)
		{
			while (!bEndReached)
			{
				auto _char = TagContents[--somePos];
				if (_char != ' ' && substringEnd == 0)
				{
					substringEnd = somePos;
				}
				else if (_char == ' ' && substringEnd != 0 && substringStart == 0)
				{
					substringStart = somePos;
					bEndReached = true;
				}
			}
			auto AmountToSubstr = (substringEnd - substringStart) + 1;
			AttrValue = TagContents.substr(substringStart, AmountToSubstr);
		}
		else
		{
			while (!bEndReached)
			{
				auto _char = TagContents[++somePos];
				if (_char == '"' && substringStart == 0)
				{
					substringStart = somePos + 1; // +1: Do not count the quotes
				}
				else if (_char == '"' && substringEnd == 0 && substringStart != 0)
				{
					substringEnd = somePos - 1; // -1: Do not count the quotes
					bEndReached = true;
				}
			}
			auto AmountToSubstr = (substringEnd - substringStart) + 1;
			AttrValue = TagContents.substr(substringStart, AmountToSubstr);
		}
		return AttrValue;
	}

public:

	Tag(std::string _TagName, std::string _TagContents)
	{
		TagName = _TagName;
		TagContents = _TagContents;
		ParseAttributes();
	}

	bool HasChildren() const { return ChildrenTags.size() > 0; }

	// Adds a new tag to our children
	void AddChildTag(Tag* _NewChild)
	{
		ChildrenTags.push_back(_NewChild);
	}

	// Find any child tags given a tag name
	Tag* FindChildTagByName(std::string _TagName)
	{
		for (auto TagRef : ChildrenTags)
		{
			if (TagRef->TagName == _TagName)
			{
				return TagRef;
			}
		}
		return nullptr;
	}
};

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

std::string AttributeParser::FindTagName(std::string _TagLine, std::size_t _FoundTagPos)
{
	// Go to _FoundTagPos and copy each char until you have a space or eol
	std::string TagName = "";

	for (uint32_t i = _FoundTagPos; i < _TagLine.length(); ++i)
	{
		auto character = _TagLine[i];
		if (!isspace(character) && (character != NULL) && (character != '\0') )
		{
			TagName.push_back(character);
		}
		else
		{
			break;
		}
	}
	
	return TagName;
}

AttributeParser::AttributeParser()
{
}

void AttributeParser::Execute()
{
	std::cout << "Please insert the number of lines and number of queries. e.g. 2 1" << std::endl;

	std::vector<Tag*> HRMLTags;
	std::vector<int> Queries;
	int NumberOfLines;
	int QueryAmount;

	// Read amount of tags and queries
	std::cin >> NumberOfLines >> QueryAmount;

	// Constraints
	if (NumberOfLines < 1 || NumberOfLines > 20 || QueryAmount < 1 || QueryAmount > 20)
	{
		return;
	}

	// This will clear out the input buffer, in case we have any withespaces after reading the numbers
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	bool TagOpened = false;
	Tag* StoredParentTag = nullptr;

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

			if (TagOpened)
			{
				// This is a child Tag, get a reference to the parent tag and add it to the list
				std::string TagName = FindTagName(line, foundTag);
				Tag NewTag(TagName, line);
				StoredParentTag->AddChildTag(&NewTag);
			}
			else
			{
				TagOpened = true;

				// Find tag name using the starting pos on TagOpened
				std::string TagName = FindTagName(line, foundTag);

				// Create a new Tag
				Tag NewTag(TagName, line);
				HRMLTags.push_back(&NewTag);
				StoredParentTag = (&NewTag);
			}

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
			TagOpened = false;
		}
	}

	// TODO: Process queries on the saved Tags
	/*for (int i = 0; i < QueryAmount; ++i)
	{

	}*/

	
}


