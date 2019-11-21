#NOTE: By using this script, I found out that Mixed Assemblies CANNOT be loaded from memory with the Reflection API.

$filename = (Get-Location).Path + "\\MixedAssembly\\x64\Debug\\MixedAssemblyDLL.dll"

#Loads an Assembly from a path. In our case, it is our Mixed Assembly DLL.
#If it works, then you can inspect it like with normal Assemblies.
#If the DLL exports DllMain, then the code in that function will execute when the DLL is loaded.
#NOTE: The Mixed Assembly that you load must be compiled for the same architecture as your current process.
#[System.Reflection.Assembly]::LoadFile($filename)

#Works the same way as LoadFile, but can also load from a URL
$assem = [System.Reflection.Assembly]::LoadFrom($filename)

#$b64  = [Convert]::ToBase64String([IO.File]::ReadAllBytes($filename))

#[System.Reflection.Assembly]::Load([Convert]::FromBase64String($b64))
