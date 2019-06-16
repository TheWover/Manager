# Manager
NOTE: For some reason, even though the code is all the same, the MixedAssemblyDLL is not loading correctly with DemoLoad. I noticed that the folder structure is unusual and different than DotNetReflectiveLoadTest. That one is normal and works. Not sure what's going on. The only possible other thing, is that the ModuleInit Assembly (which the latter uses) has a module initializer. Try loading that through MixedAssemblyDLL, rather than DemoAssembly.

Library of examples for bootstrapping Managed Assemblies using Mixed Assemblies through C++/CLI. The entry point for the wrapper code is written in natively-compiled C++ and can be the normal Main function or DLLMain. It creates a new thread (to avoid loader lock), using a second unmanaged bootstrap function. The second unmanaged function makes a call to a managed function (compiled through C++/CLI with the /clr flag for MSBuild). C++/CLI will load the CLR if it is not already present so that it may make the call. The managed function then loads the target Assembly through System.Reflection.Assembly.Load(). Ideally, this target would either be downloaded or embedded as a packed resource. Examples are provided for both.

This can be used to create C# payloads that can be ingested through DLLMain. When LoadLibrary is called on the C++ DLL, DLLMain is called. DLLMain creates a thread that gets the embedded resource and calls LaunchDLL. LaunchDLL is a C++/CLI function that calls Assembly.Load on the bytes obtained from the resource. The Reflection API is used to load the Assembly and invoke the specified static type and method.

Manager's MixedAssembly library avoids the Loader Lock issue by not invoking the target payload directly in DllMain or the main entry point. Instead, the entry point creates a new thread to transition into managed code and load the target. This lets the CLR load safely. It also means that MixedAssembly DLLs may be used as payloads for DLL side-loading or similar attacks. They do not disturb the main functionality of the host process. And, they isolate the host process from any failure that may occur in the payload-execution/staging process.

Mixed Assemblies provide two uses for offensive tools:
    1) As a way to load managed code from unmanaged code.
    2) To build offensive tools that can take advantage of both the .NET libraries and features as well as the capabilities and advantages of the C++/C standard libraries. Mixed Assemblies can be loaded normally using System.Reflection.Assembly.Load, and can be uses as references in C# projects.
        * Reflection in C++/CLI: https://docs.microsoft.com/en-us/cpp/dotnet/reflection-cpp-cli?view=vs-2017
        * Library support in C++/CLI: https://docs.microsoft.com/en-us/cpp/dotnet/library-support-for-mixed-assemblies?view=vs-2017 
        * Using Costura with Mixed-Mode Assemblies: https://github.com/Fody/Costura#unmanaged32assemblies--unmanaged64assemblies

## Usage

Rather than providing a library of classes or functions like most code libraries, this is a collection of examples along with detailed explanation. The important takeaway from this library is not a set of code to import into your project, but the knowledge that these techniques are possible. I have not personally seen anyone else using C++/CLI in their offensive tooling. As such, I think that an overview of the offensive possibilities for C++/CLI is more useful. I have not provided any generic, turnkey solution for staging .NET Assemblies from memory and do not intend to. However, the code in this repo should provide you with everything you need create such solutions on your own. 

The MixedAssembly solution contains two examples:

* MixedAssemblyDLL - A DLL that bootstraps an Assembly through DllMain while avoiding Loader Lock. 
* MixedAssemblyEXE - An EXE that runs an Assembly, passing in the command-line arguments to the payload.

Both examples demonstrate how to handle loading Assemblies in either DLL or EXE format.

The target Assembly payload may be passed in through your favorite mechanism. My favorite is as a packed resource embedded into the stager. Doing so results in only one "file" on-disk and essentiallly wraps your easily-reversible .NET payload in a less-reversible unmanaged program. That is the example that is provided. The section below explains how to do this in Visual Studios. Other options include as an embedded string, a file downloaded through WebClient, or as a command-line argument. Really, it is up to you, so figure out yourself. ;-)

Using C++/CLI can take some getting used it. Each module must be designated as CLR code in Visual Studios. Furthermore, several properties and settings must be turned on/off for a build to be successful. My current strategy is keep running the "Build" command and Googling the errors until I stop getting them. When I have developed a better technique, I will update this Readme. ;-) This link can help in the meantime: https://blogs.msdn.microsoft.com/calvin_hsia/2013/08/30/call-managed-code-from-your-c-code/

### Using a Resource for Payload Delivery



## Further Reading

* Loader Lock: https://docs.microsoft.com/en-us/cpp/dotnet/initialization-of-mixed-assemblies?view=vs-2017
* How C++/CLI Initializes Assemblies (and avoids loader lock): https://docs.microsoft.com/en-us/cpp/dotnet/initialization-of-mixed-assemblies?view=vs-2017
* Run a PE from memory: https://github.com/TheWover/RunPE Good expansion for this to run PEs, too. 


## Credits
This whole project is based off of a hunch I had, confirmed by a response to this StackOverflow question: https://stackoverflow.com/questions/8206736/c-sharp-equivalent-of-dllmain-in-c-winapi/9745422#9745422

This project began as a PoC of that article, and has been cleaned up and expanded to make it more generally useful.

## To-Do:

TODO:
See if you can include the managed assembly as a reference somehow, so that you don't have to use Assembly.Load().
Clean up code
Turn into one solution
Write up tutorial to reproduce it.