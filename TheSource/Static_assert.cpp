#include <iostream>
#include <string>
#include <type_traits>
#include "Static_assert.h"



Static_assert::Static_assert()
{
}


Static_assert::~Static_assert()
{
}

// C++11 Compile time assertions
// useful to allow the compiler to check for undesired errors that can be caused at runtime

int int_magic(int a, int b)
{
	static_assert(sizeof(int) <= 4, "int must be not more than 4 bytes");
	// ... do things with a and b
	return 0;
}

template<unsigned int dimensions>
struct Matrix
{
	Matrix()
	{
		static_assert(dimensions <= 3, "dimensions must not exceed 3");
	}
};

class Base
{
public:
	Base() {}
	virtual ~Base() {}
};

template<typename T>
class Derived : public T
{
public:
	Derived() {}
	virtual ~Derived() {}

	//std::has_virtual_destructor implemented from <type_traits>
	static_assert(std::has_virtual_destructor<T>::value, "The base class must have a virtual destructor");
};

void Static_assert::Execute()
{
	Matrix<3> m3;           // Ok
							//Matrix<4> m4;           // error: static assertion failed: dimensions must not exceed 3

	Derived<Base> d;        //Ok
							//Derived<std::string> s; // error: static assertion failed: The base class must have a virtual destructor|

	std::cout << std::endl;
	std::cout << "---END" << std::endl;
}
