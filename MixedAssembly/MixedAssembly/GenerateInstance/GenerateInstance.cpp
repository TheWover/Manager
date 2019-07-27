/*
	Author: The Wover
	Description: Generates an instance file from an Assembly and user input.
*/

#include <iostream>
#include "structs.h"
#include <vector>

void GetRandomBytes(unsigned char* bytes, int amount);

void ParseArgs(std::vector<std::string> strings, INSTANCE* instance);

bool Help(std::vector<std::string> strings);


int main(int argc, char** argv)
{
	//The instance to create from the Assembly
	//INSTANCE *instance = static_cast<INSTANCE*>(malloc(sizeof(INSTANCE)));
	INSTANCE* instance = new INSTANCE;

	//Parse argv for C++ style strings to make things easier

	//Convert the command-line arguments to a set of std::string to make them easier to work with.
	std::vector<std::string> strings(argv, argv + (argc));

	ParseArgs(strings, instance);

	//TODO: Serialize instance, encrypt it with a random key and IV, and store it as a file with a name like AssemblyName.instance

    std::cout << "Hello World!\n";

	std::cin;
}

//Used to get a random key for encryption
void GetRandomBytes(unsigned char* bytes, int amount)
{
	for (int i = 0; i < amount; i++)
	{
		bytes[i] = rand() % 0xFF;
	}
}


//TODO: Finish
void ParseArgs(std::vector<std::string> strings, INSTANCE* instance)
{
	if (Help(strings) == true)
		exit(0);


}


bool Help(std::vector<std::string> strings)
{
	//Iterate through args, ignoring the first because it is the file path of this executable
	for (int i = 1; i < strings.size(); i++)
	{
		if(strings[i] == "-h")
		{
			std::cout << "GenerateInstance.exe || TheWover, @TheRealWover" << "\n";
			std::cout << "Usage: GenerateInstance.exe <path_to_.NET_Assembly [-c] [-m] [-p]" << "\n\n";

			std::cout << "-c <namespace.class>\t\tOptional class name. (required for DLL)" << "\n";
			std::cout << "-m <method>\t\t\tMethod name. (required for DLL)" << "\n";
			std::cout << "-p <arg1,arg2...>\t\tOptional parameters or command line, separated by comma or semi-colon." << "\n";
			//We found a request for help.
			return true;
		}
	}
	return false;
}
