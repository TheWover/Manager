// dllmain.cpp : Defines the entry point for the DLL application.
#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "resource.h"
extern void LaunchDll(
	unsigned char *dll, size_t dllLength,
	char const *className, char const *methodName);

extern void LaunchEXE(
	unsigned char *dll, size_t dllLength);

static DWORD WINAPI launcher(void* h)
{

	std::cout << "Created thread...";

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

				//TODO: Get it to pass in arguments. Preferably using a String Table Resource.

				//Update this with the correct fully-qualified class name and method name
				LaunchDll(dll, len, "DemoAssemblyDLL.Demo", "Test"); 

				//Use this instead if the payload is an EXE.
				//LaunchEXE(dll, len);
			}
		}
	}
	return 0;
}
extern "C" BOOL APIENTRY DllMain(HMODULE h, DWORD reasonForCall, void* resv)
{
	if (reasonForCall == DLL_PROCESS_ATTACH)
	{
		CreateThread(0, 0, launcher, h, 0, 0);
	}
	return TRUE;
}