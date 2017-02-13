#include <iostream>
#include "DynamicArrays.h"


DynamicArrays::DynamicArrays()
{
}


DynamicArrays::~DynamicArrays()
{
}

//https://www.hackerrank.com/challenges/variable-sized-arrays
void DynamicArrays::Execute()
{
	int nArrays = 0;
	int nQueries = 0;
	std::cin >> nArrays >> nQueries;

	//** Input Array Section

	// Dynamic resized array, can be resized in any direction, and isn't necessarily square.
	int** VariableSize = new int*[nArrays];
	for (int i = 0; i < nArrays; ++i)
	{
		int arrayLength = 0;
		std::cin >> arrayLength;

		int* SubArray = new int[arrayLength];
		for (int j = 0; j < arrayLength; ++j)
		{
			int element = 0;
			std::cin >> element;
			*(SubArray + j) = element;
		}
		// Fill Array
		*(VariableSize + i) = SubArray;
	}

	//** Query Section

	// Dynamic resized array, can be resized in any direction, and isn't necessarily square.
	int** QueryVariableArray = new int*[nQueries];
	for (int w = 0; w < nQueries; ++w)
	{
		int queryOnePos = 0;
		int queryTwoPos = 0;
		std::cin >> queryOnePos >> queryTwoPos;

		int* QuerySubArray = new int[2];
		*(QuerySubArray) = queryOnePos;
		*(QuerySubArray + 1) = queryTwoPos;

		// Fill Array
		*(QueryVariableArray + w) = QuerySubArray;
	}

	//** Output
	for (int z = 0; z < nQueries; ++z)
	{
		int* QueryArray = QueryVariableArray[z];
		std::cout << VariableSize[QueryArray[0]][QueryArray[1]] << std::endl;
	}

	// Free Memory
	delete VariableSize;
	delete QueryVariableArray;
}
