/*
	Author: The Wover
	Description: Defines the data structures used in loading the payload.
*/

#pragma once

enum PAYLOAD_TYPE { DLL, EXE }; // Type of the .NET Assembly to load

/*
Contains the .NET Assembly payload and the information required to execute it.
We can comfortably use standard data structures because both the initializer and the loader of the struct will be C++.
	Don't have to do everything using C strings, so why bother? ;-)

This data structure is serialized, stored somewhere like a URL or a resource, and then obtained at runtime by the loader.
*/
typedef struct INSTANCE {
	unsigned char* assembly; // The .NET Assembly as a C++ vector.
	size_t lengthAssembly; // Size of the .NET Assembly
	PAYLOAD_TYPE type; // Whether the .NET Assembly is an EXE or DLL
	size_t numParams; // Number of string parameters to pass in.
	const char** params; //Parameters to pass into entry point.
	const char* className; // Namespace.Class of entry point. Unused for EXE payloads.
	const char* methodName; // Method name of Entry Point. Unused for EXE payloads.
} *PINSTANCE;