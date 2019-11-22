/*
	Author: The Wover
	Description: Provides example managed functions to demonstrate moving between managed and unmanaged code.
*/
#include "stdafx.h"
#include "managed.h"
#using <System.dll>
#using <mscorlib.dll>

//using namespace System;

/* UNCOMMENT TO USE!!!! */
//These functions are provided as examples of how to call native code from managed code.

//An example native function that just prints a hello statement.
void Example_Managed_SayHello(std::string message)
{
	//Convert the C++ string to a C-style string, then to a managed string.
	System::String^ managedMessage =
		System::Runtime::InteropServices::Marshal::PtrToStringAnsi(
		(System::IntPtr) (char*) message.c_str());

	//Print the string that was passed in.
	System::Console::WriteLine("Hello from managed code! Message: " + managedMessage);

}

//An example native function that just prints pops a command prompt.
void Example_Managed_PopCmd()
{
	System::Diagnostics::Process^ process = gcnew System::Diagnostics::Process();
	process->StartInfo->FileName = "C:\\WINDOWS\\system32\\cmd.exe";
	process->Start();
}

//An example managed function that calls native functions.
void Example_Managed_CallNative()
{
	//Call the native function to print a message.
	Example_Native_SayHello("I was invoked by a managed function.");

	//Call the native function to pop a calculator
	Example_Native_PopCalc();
}