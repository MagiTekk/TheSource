
#include <iostream>
#include <string>
#include <crtdbg.h>
#include <windows.h>
#include "Verify.h"

#define ASSERT _ASSERTE

#ifdef _DEBUG
#define VERIFY ASSERT
#else
#define VERIFY(expression) (expression)
#endif

struct LastException
{
	DWORD result;

	LastException() : result{ GetLastError() } {}
};

struct ManualResetEvent
{
	HANDLE m_handle;

	ManualResetEvent()
	{
		// This is a kernel object and it's possible that this fails
		// in that case it will return a nullptr
		m_handle = CreateEvent(nullptr,
			true,
			false,
			nullptr);

		if (!m_handle)
		{
			throw LastException();
		}
	}

	~ManualResetEvent()
	{
		// we have to close that handle upon destruction
		VERIFY(CloseHandle(m_handle));
	}
};

Verify::Verify()
{
}


Verify::~Verify()
{
}

void Verify::Execute()
{
	auto e = ManualResetEvent();
	// e2 destructor will throw an error since we didn't declare a copy constructor and the compiler
	// generated an implicit one that copied the value of the handle but we cannot close it
	// verify checks on this error and throws an exception at runtime!
	// still this is not what verify is for, that would happen even without it
	// if you use VERIFY you will get an error code when running the debug build inside or outside the compiler
	// but for release builds outside the compiler it will strip out the VERIFY and run normally, unless you run
	// the release build inside the compiler!
	auto e2 = e;
}
