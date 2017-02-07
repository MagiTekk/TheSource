#include "Uniqueptr.h"
#include <iostream>
#include <memory>


Uniqueptr::Uniqueptr()
{
}


Uniqueptr::~Uniqueptr()
{
}

struct Hen
{
	unsigned id;
	float eggs;

	Hen(unsigned id_, float eggs_) : id{ id_ }, eggs{ eggs_ } {}

	~Hen()
	{
		std::cout << "Chicken soup!" << std::endl;
	}
};

// how does the caller know who knows the Hen object?
//auto GetHen_badway() -> Hen*
//{
// could come from a lot of different ways
// maybe a cached maintained by the Hen function
// maybe a singleton
// there is no way to know, the developer will have to take a look
// at the documentation or rely on some investigations
//}

auto GetHen() -> std::unique_ptr<Hen>
{
	// now you avoid any confusion
	return std::make_unique<Hen>(2, 3.9f);
}

auto UpdateHen(std::unique_ptr<Hen> hen) ->std::unique_ptr<Hen>
{
	hen->eggs += 1.8f;
	return hen;
}

void Uniqueptr::Execute()
{
	// Unique Pointer
	//auto sp = std::unique_ptr<int> {}; // this initializes the pointer to a nullptr automatically
	//auto sp = std::unique_ptr<int> { new int {123}; };
	//auto sp = std::make_unique<int>(123);    // this should be my first choice, make_unique is a variadic template

	auto hen = std::make_unique<Hen>(1, 5.6f);

	if (hen) { std::cout << "'hen' owns the Hen!" << std::endl; };
	//auto hen2 = hen; // Will not work! because unique pointers cannot be copied
	auto hen2 = std::move(hen); // but can be moved!

	if (hen) { std::cout << "'hen' owns the Hen!" << std::endl; };
	if (hen2) { std::cout << "'hen2' owns the Hen!" << std::endl; };

	//-- if you run this piece of code you will notice that the move constructor moved the ownership of the Hen into hen2
	//-- Hen's destructor will only be called once! by the pointer that happened to own the Hen object in the end!

	// Some operations with the unique_ptr are:

	//Hen a_copy = *hen; // create a copy of the pointer
	//Hen& a_ref = *hen; // create a reference if copy is costly
	//Hen* a_ptr = hen.get();   // obtain a pointer by calling get()
	//Hen* a_ptr_release = hen.release(); // create a copy and release the ownership of the hen
	//hen.reset();                        //another option instead of release

	// Transfer ownership to a function
	auto heny = GetHen();
	std::cout << "eggs " << heny->eggs << std::endl;

	// Using a function to update my pointer
	//heny = UpdateHen(heny); // won't work since we cannot copy a unique_ptr
	heny = UpdateHen(std::move(heny));   // but we can move it in and out of the function

	std::cout << "eggs " << heny->eggs << std::endl;
}