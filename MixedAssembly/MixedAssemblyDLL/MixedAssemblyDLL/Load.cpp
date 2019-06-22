#using <mscorlib.dll>
#include "stdafx.h"
#include "native.h" //Lets you call your native functions.

// Load a managed DLL from a byte array and call a static method in the DLL.
// dll - the byte array containing the DLL
// dllLength - the length of 'dll'
// className - the name of the class with a static method to call.
// methodName - the static method to call. Must expect no parameters.
void LaunchDll(
	unsigned char *dll, size_t dllLength,
	char const *className, char const *methodName,
	size_t numParams, )//TODO: Get an array of parameters passed in and working.
{
	// convert passed in parameter to managed values
	cli::array<unsigned char>^ mdll = gcnew cli::array<unsigned char>(dllLength);
	System::Runtime::InteropServices::Marshal::Copy(
		(System::IntPtr)dll, mdll, 0, mdll->Length);
	System::String^ cn =
		System::Runtime::InteropServices::Marshal::PtrToStringAnsi(
		(System::IntPtr)(char*)className);
	System::String^ mn =
		System::Runtime::InteropServices::Marshal::PtrToStringAnsi(
		(System::IntPtr)(char*)methodName);

	// used the converted parameters to load the DLL, find, and call the method.
	System::Reflection::Assembly^ a = System::Reflection::Assembly::Load(mdll);
	a->GetType(cn)->GetMethod(mn)->Invoke(nullptr, nullptr);
}

// Load a managed EXE from a byte array and invoke the main entry point.
// exe - the byte array containing the EXE
// dllLength - the length of 'exe'
void LaunchEXE(
	unsigned char *exe, size_t exeLength)
{
	//Create an array of managed Objects with a length of 1.
	array< System::Object^ >^ arr = gcnew array< System::Object^ >(1);

	// convert passed in parameter to managed values
	cli::array<unsigned char>^ mexe = gcnew cli::array<unsigned char>(exeLength);
	System::Runtime::InteropServices::Marshal::Copy(
		(System::IntPtr)exe, mexe, 0, mexe->Length);

	// Create array of Strings to pass in as parameters to EXE Entry Point
	// .NET EXEs take an Object Array containing a string array of command-line arguments
	array< System::Object^ >^ args = gcnew array< System::Object^ >(1)
	//TODO: Get an array of parameters passed in and working.

	//Create an array of managed Objects.
	array< System::Object^ >^ arr = gcnew array< System::Object^ >(1);

	//Add in the parameters.
	arr[0] = mexe;


	// used the converted parameters to load the DLL, find, and call the method.
	System::Reflection::Assembly^ a = System::Reflection::Assembly::Load(mexe);
	a->EntryPoint->Invoke(nullptr, nullptr);
	//TODO: Fix this later ^^. https://docs.microsoft.com/en-us/cpp/dotnet/how-to-use-arrays-in-cpp-cli?view=vs-2017
}