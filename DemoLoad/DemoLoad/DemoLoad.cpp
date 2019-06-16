// DemoLoad.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Author: The Wover does not remember. The Wover copied this from somewhere on the Interwebs, but has totally forgotten where from because that was a while ago.
//

#include "pch.h"
#include <iostream>
#include <string>

#include <windows.h>

typedef bool(*testFunction)();

testFunction dllFunction;

using namespace std;

int main(int argc, char** argv)
{
	string path = "example.dll";

	if (argc > 0)
		path = argv[1];

	cout << "Loading: " << path << '\n';

	HINSTANCE hDll = LoadLibraryA(path.c_str());

	//Use if you want to call a function from the DLL.
	if (hDll)
	{
		//dllFunction = (testFunction)GetProcAddress(hDll, "example");
		//dllFunction();
	}

	//Pause for input. Continues the main program and gives the chance for your loaded DLL's DllMain functionality to run.
	system("pause");

	return 0;
}