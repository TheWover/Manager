/*
	Author: The Wover
	Description: Declares the signatures of managed C++/CLI functions.
*/

#pragma once

#include "native.h"
#include <string>

using namespace std;

extern void LaunchDll(
	unsigned char *dll, size_t dllLength,
	char const *className, char const *methodName,
	size_t numParams, char const **params);

extern void LaunchEXE(
	unsigned char *dll, size_t dllLength);


/* UNCOMMENT TO USE!!!! */
//These functions are provided as examples of how to call native code from managed code.

//An example managed function that just prints a hello statement.
extern void Example_Managed_SayHello(std::string message);

//An example managed function that just prints pops a command prompt.
extern void Example_Managed_PopCmd();

//An example managed function that calls native functions.
extern void Example_Managed_CallNative();

/* UNCOMMENT TO USE!!!! */