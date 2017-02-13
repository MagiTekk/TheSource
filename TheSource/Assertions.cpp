#include <crtdbg.h>
#include <cassert>
#include <iostream>
#include <string>
#include "Assertions.h"

#define ASSERT _ASSERTE

Assertions::Assertions()
{
}


Assertions::~Assertions()
{
}

// ASSERTIONS
// assertions are for debug builds, and they provide clarity to the application where code can work in an undesirable way
// #include <crtdbg.h> to use _ASSERTE, this one provides more information about the assertion error
// you can "#define ASSERT _ASSERTE" to make sure this assertions work well in other environments (like for example windows phone)

/*
The _ASSERT_EXPR, _ASSERT and _ASSERTE macros provide an application with a clean and simple mechanism for checking assumptions
during the debugging process. They are very flexible because they do not need to be enclosed in #ifdef statements to prevent them
from being called in a retail build of an application. This flexibility is achieved by using the _DEBUG macro.
_ASSERT_EXPR, _ASSERT and _ASSERTE are only available when _DEBUG is defined at compile time. When _DEBUG is not defined,
calls to these macros are removed during preprocessing.
*/

// assertions can be done with #include <cassert> and "assert" but depending on the compiler will not give out much information.
// "assert" is a macro and it breaks the naming convention for the rules for macros on C++ "UPPERCASE" but this one inherits from the
// C style asserts and that's why it looks like that
// static_assert works for checking errors at compile time rather than runtime and don't require a particular library


// assertion will throw an error when compiling since sizeof(double) is 8
// it is important to say that static assertions are checked at compile time, before your application ships to customers
// so there is no reason not to use them liberally
//static_assert(sizeof(double) == 4, "can't serialize floats!");

void Assertions::Execute()
{
	// Better option than "assert" using the #include <crtdbg.h>, this will work for debug builds
	ASSERT(4 == 5);

	// Run-time assertions are typically conditionally compiled and included only in debug builds
	// and stripped out of release or free builds
	// this assertion works, but to understand the error you must take a look at the console
	//assert(2 + 2 == 5);
}
