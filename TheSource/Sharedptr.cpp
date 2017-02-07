#include "Sharedptr.h"
#include <memory>
#include <iostream>
#include <cassert>

#define ASSERT _ASSERTE


Sharedptr::Sharedptr()
{
}


Sharedptr::~Sharedptr()
{
}

void Sharedptr::Execute()
{
	// let's create an empty shared_ptr
	auto sp = std::shared_ptr<int>{};

	assert(!sp);                    //it's pointing to nullptr
	assert(sp.use_count() == 0);    // it has no uses
	assert(!sp.unique());           // it's not unique

									// I can reset the smart pointer and give it an object to manage
									//sp.reset(new int {123});

									// But in general it's going to be more efficient to use make_shared to achieve the same thing
	sp = std::make_shared<int>(123);

	assert(sp);
	assert(sp.use_count() == 1);

	// unique() only determines if the reference use count is 1
	assert(sp.unique());

	auto sp2 = sp;

	assert(sp.use_count() == 2);
	assert(!sp.unique());

	// The same assertions hold for the copied smart pointer
	assert(sp2.use_count() == 2);
	assert(!sp2.unique());

	int copy = *sp;
	int& ref = *sp;
	int* ptr = sp.get();

	assert(sp.get() == sp2.get());
	assert(sp == sp2);
}