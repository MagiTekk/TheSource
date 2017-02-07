#include "Weakptr.h"
#include <cassert>
#include <memory>
#include <iostream>


Weakptr::Weakptr()
{
}


Weakptr::~Weakptr()
{
}

void Weakptr::Execute()
{
	auto sp = std::make_shared<int>(123);

	auto wp = std::weak_ptr<int>(sp);
	// wp = sp; Not needed since I initialized the weak pointer upon construction

	assert(!wp.expired());
	assert(wp.use_count() == 1);

	// the use count will only return if the shared pointer still exists, there is no guarantee of that unless...
	if (auto locked = wp.lock())
	{
		std::cout << "locked! v1" << std::endl;
	}

	// now let's destroy our shared_ptr
	sp = nullptr;

	assert(wp.expired());
	assert(wp.use_count() == 0);

	if (auto locked = wp.lock())
	{
		std::cout << "locked! v2" << std::endl;
	}
	else
	{
		// we do this because even though the weak_ptr does not have an assigned shared:ptr
		// the memory block where it resides may linger unless we reset the weak_ptr
		wp.reset();
	}

}