/*
	Author: The Wover
	Description: Contains the definitions of native functions in the DLL. All functions should be declared in "native.h".
		Includes both:
		- The proxy function used to invoke the managed load functions
		- And any utility functions that you wish to invoke from managed code.
*/
#include "stdafx.h"
#include "native.h"
#include "managed.h"

/* UNCOMMENT TO USE!!!! */
//These functions are provided as examples of how to call managed code from native code.

//An example native function that just prints a hello statement.
void Example_Native_SayHello(std::string message)
{
	std::cout << "Hello from native code! Message: " << message;
}

//An example native function that just prints pops a command prompt.
void Example_Native_PopCalc()
{
	//For some reason ShellExecute was not imported from windows.h, so we are using CreateProcess.

	// additional information
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// start the program up
	CreateProcess(L"C:\\WINDOWS\\system32\\calc.exe",   // the path
		NULL,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	);
	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

//An example native function that invokes managed functions.
void Example_Native_CallManaged()
{
	//Call the managed function to print a message.
	Example_Managed_SayHello("I was invoked by a native function.");

	//Call the managed function to pop a command prompt
	Example_Managed_PopCmd();
}

/* UNCOMMENT TO USE!!!! */