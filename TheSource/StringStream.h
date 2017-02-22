#pragma once
#include <vector>

class StringStream
{
public:
	StringStream();
	~StringStream();

	void Execute();

private:
	std::vector<int> parseInts(std::string str);
};

