#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include "managed.h"
#include "native.h"


int main(int ac, char** av)
{
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
}
