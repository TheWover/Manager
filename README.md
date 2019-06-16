# Manager
Toolset and Libraries for reflectively running/bootstrapping managed code from unmanaged code using the .NET Framework. There are three techniques represented here:

1) CLRHosting: Load Assemblies using Microsoft's official Unmanaged CLR Hosting APIs.
    * Documentation: https://docs.microsoft.com/en-us/dotnet/framework/unmanaged-api/hosting/clr-hosting-interfaces 
2) Shellcode: Various PICs or tools (some are just links) for injecting .NET Assemblies through native shellcode.
2) MixedAssembly: Load Assemblies using C++/CLI, a version of C++ that can mix both unmanaged machine code and managed MSIL code on a per-module or even per-function basis.
    * Documentation: https://docs.microsoft.com/en-us/cpp/dotnet/mixed-native-and-managed-assemblies?view=vs-2017

Additionally, the DemoAssembly project is provided that includes an Assembly that pops up a command prompt. This can be used as an easy test payload. It is provided in both DLL and EXE format.

The DemoLoad project is a simple program that loads a DLL through LoadLibrary. It is useful for testing a generated DLL payload.

## Purpose

The capability to load managed code from unmanaged code can serve many purposes. However, from the perspective of a red-teamer, this represents the ability to inject .NET code into arbitrary Windows processes. It can also provide a more Op-Sec friendly way of crafting stagers for .NET Assemblies that does not rely upon putting easily reversable managed code onto disk.
