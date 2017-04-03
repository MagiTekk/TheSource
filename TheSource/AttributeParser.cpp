#include "AttributeParser.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm> // std::count

//#define INT_MAX       2147483647    // maximum (signed) int value

class Tag
{
	void ParseAttributes()
	{
		// Using the TagContents, parse all attributes
		std::size_t lastFoundPos = 0;
		
		int AssignmentCount = std::count(TagContents.begin(), TagContents.end(), '=');
		for (int i = 0; i < AssignmentCount; ++i)
		{
			// Find the next "=" sign
			lastFoundPos = TagContents.find_first_of("=", lastFoundPos + 1);

			// Copy contents from left side
			auto attrName = SubstrValueFromContent(lastFoundPos, true);

			// Copy contents from right side
			auto attrValue = SubstrValueFromContent(lastFoundPos, false);

			//std::cout << "attrName found!: " << attrName << std::endl;
			//std::cout << "attrValue found!: " << attrValue << std::endl;

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
					substringStart = somePos + 1; // +1: Do not count empty space
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

	std::string TagName;
	std::string TagContents;
	std::vector<Tag> ChildrenTags;
	std::map<std::string, std::string> TagAttributes;

	Tag(){}

	Tag(std::string _TagName, std::string _TagContents)
	{
		TagName = _TagName;
		TagContents = _TagContents;
		ParseAttributes();
	}

	bool HasChildren() const { return ChildrenTags.size() > 0; }

	// Adds a new tag to our children
	void AddChildTag(Tag _NewChild)
	{
		ChildrenTags.push_back(_NewChild);
	}

	// Find any child tags given a tag name
	Tag FindChildTagByName(std::string _TagName)
	{
		for (auto TagRef : ChildrenTags)
		{
			if (TagRef.TagName == _TagName)
			{
				return TagRef;
			}
		}
	}

	std::string FindAttrValueByAttrName(std::string _AttrName)
	{
		for (auto TagAttr : TagAttributes)
		{
			if (TagAttr.first == _AttrName)
			{
				return TagAttr.second;
			}
		}
		return "";
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

Tag AttributeParser::FindTagByName(std::vector<Tag> _HRMLTags, std::string _TagName)
{
	for (auto TagRef : _HRMLTags)
	{
		if (TagRef.TagName == _TagName)
		{
			return TagRef;
		}
	}
	return Tag();
}

std::string AttributeParser::FindTagNameFromTagLine(std::string _TagLine, std::size_t _FoundTagPos)
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
	//std::cout << "Please insert the number of lines and number of queries. e.g. 2 1" << std::endl;

	std::vector<Tag> HRMLTags;
	std::vector<std::string> Queries;
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

	// Read lines "Tags"
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
			//std::cout << "Line is a tag" << std::endl;

			if (TagOpened)
			{
				// This is a child Tag, get a reference to the parent tag and add it to the list
				std::string TagName = FindTagNameFromTagLine(line, foundTag);
				Tag NewTag(TagName, line);
				
				// TODO: find which tag has closed to add tag to the proper parent
				// Add tag to the last tag "parent" added
				HRMLTags.back().AddChildTag(NewTag);
			}
			else
			{
				TagOpened = true;

				// Find tag name using the starting pos on TagOpened
				std::string TagName = FindTagNameFromTagLine(line, foundTag);

				// Create a new Tag
				Tag NewTag(TagName, line);
				HRMLTags.push_back(NewTag);
			}

		}
		else if (foundSlash == std::string::npos)
		{
			// Line was something else, handle exception
			std::cout << "The line you inserted is neither a tag or an ending tag, please try again" << std::endl;
		}
		else
		{
			// TODO: find which tag has closed to add tag to the proper parent
			// Line was an ending tag
			//std::cout << "line is an ending tag :: Line: " << line << std::endl;
			TagOpened = false;
		}
	}

	// Store queries
	for (int i = 0; i < QueryAmount; ++i)
	{
		// Store query
		std::string query;
		std::getline(std::cin, query);

		Queries.push_back(query);
	}

	// Finally process queries and output values!
	for (int i = 0; i < static_cast<int>(Queries.size()); ++i)
	{
		auto query = Queries[i];

		// query example: tag1.tag2~name

		// find tag
		std::size_t foundTilde = query.find("~");

		int DotCount = std::count(query.begin(), query.end(), '.');
		if (DotCount > 0)
		{
			// found a dot, take parent name and try to find the child being called
			std::size_t foundDot = query.find(".");
			auto ParentTagName = query.substr(0, foundDot);
			auto TagQueried = FindTagByName(HRMLTags, ParentTagName);

			for (int i = 0; i < DotCount; ++i)
			{
				if (DotCount > 1)
				{
					auto firstDot = query.find_first_of(".", foundDot + 1); // Find next dot after the one we found on the parent
					auto subTagName = query.substr(foundDot, firstDot);

					if (TagQueried.HasChildren())
					{
						TagQueried = TagQueried.FindChildTagByName(subTagName);
					}
					else
					{
						break;
					}
				}
				else
				{
					auto subTagName = query.substr(foundDot + 1, foundDot);

					if (TagQueried.HasChildren())
					{
						TagQueried = TagQueried.FindChildTagByName(subTagName);
					}
					else
					{
						break;
					}
				}
			}

			// find attr
			auto attrToRead = query.substr(foundTilde + 1, query.size());
			auto attrValue = TagQueried.FindAttrValueByAttrName(attrToRead);

			// output query
			auto output = attrValue != "" ? attrValue : "Not Found!";
			std::cout << output << std::endl;
		}
		else if (foundTilde != std::string::npos)
		{
			auto tagName = query.substr(0, foundTilde);
			auto TagQueried = FindTagByName(HRMLTags, tagName);
			auto attrToRead = query.substr(foundTilde + 1, query.size());
			auto attrValue = TagQueried.FindAttrValueByAttrName(attrToRead);

			// output query
			auto output = attrValue != "" ? attrValue : "Not Found!";
			std::cout << output << std::endl;
		}
	}
}


