/*
	Author: The Wover
	Description: Declares native functions that are defined in native.cpp.
		Also imports the other header files used by native code.
*/
#pragma once

#include <windows.h>
#include <iostream>
#include "resource.h"
#include "managed.h"
#include "structs.h"

/* UNCOMMENT TO USE!!!! */
//These functions are provided as examples of how to call native code from managed code.

//An example native function that just prints a hello statement.
void Example_Native_SayHello(std::string message);

//An example native function that just prints pops a command prompt.
void Example_Native_PopCalc();

//An example native function that invokes a managed function.
void Example_Native_CallManaged();

/* UNCOMMENT TO USE!!!! */