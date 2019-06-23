/*
	Author: The Wover
	Description: Defines the data structures used in loading the payload.
*/

#pragma once

#include "constants.h"
#include <vector>

using namespace std;

// Whether to load from a URL or a resource
// If you add your own sources, update this enum.
enum SOURCE_TYPE { URL, RESOURCE };

enum PAYLOAD_TYPE { DLL, EXE }; // Type of the .NET Assembly to load

// Defines a custom type for 
typedef const char *RESOURCE_TYPE;

/*
Contains the .NET Assembly payload and the information required to execute it.
We can comfortably use standard data structures because both the initializer and the loader of the struct will be C++.
	Don't have to do everything using C strings, so why bother? ;-)
*/
typedef struct INSTANCE {
	std::vector<unsigned char> assembly; // The .NET Assembly as a C++ vector.
	size_t lengthAssembly; // Size of the .NET Assembly
	PAYLOAD_TYPE type; // Whether the .NET Assembly is an EXE or DLL
	size_t numParams; // Number of string parameters to pass in.
	std::string params[MAX_PARAMS]; //Parameters to pass into entry point.
	std::string className; // Namespace.Class of entry point. Unused for EXE payloads.
	std::string methodName; // Method name of Entry Point. Unused for EXE payloads.
} *PINSTANCE;

/*
Contains the options required to know how to obtain and load the instance.
*/
typedef struct OPTIONS {
	SOURCE_TYPE source; // Whether we should load from a URL or a resource
	const char *url; //The URL to download from, if the source type is URL.
	int rescNum;
} *POPTIONS;
