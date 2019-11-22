Library for reflectively loading .NET Assemblies using only the unmanaged CLR Hosting APIs provided by `mscoree.dll`. This imitates how the Windows Loader loads .NET EXEs and DLLS. This is the most OpSec friendly way to load Assemblies, since it is bootstrapped by an unmanaged executable (and is therefore harder to reverse) and does not use any .NET Framework libraries (such as System.Reflection). Because the result is an unmanaged PE-formatted EXE or DLL, the result may be injected into processes using standard process injection techniques. Therefore, managed Assemblies may be injected into unmanaged processes. Additionally, unmanaged on-disk stagers (written in C/C++) may be built that load .NET payloads (written in C#, etc.).

CLR Hosting API documentation: https://docs.microsoft.com/en-us/dotnet/framework/unmanaged-api/hosting/clr-hosting-interfaces

Microsoft also provides related APIs for profiling, debugging, thread management, and more, all of which can be combined to create highly customized loaders tailored for your particular use case.


# Projects

* None of mine for now. :-P Check out the following projects by other people:
    * https://github.com/ambray/DotNetReflectiveLoading
    * (By Casey Smith. I just forked the repo before it was deleted) https://github.com/TheWover/AssemblyLoader
    * Donut contains a CLR Host loader that is converted to shellcode: https://github.com/TheWover/donut 
