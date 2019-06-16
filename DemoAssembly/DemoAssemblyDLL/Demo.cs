using System;
using System.Diagnostics;

namespace DemoAssemblyDLL
{
    /// <summary>
    /// Procs an executable to demonstrate that the method has been successfully called.
    /// </summary>
    public static class Demo
    {
        public static void Test(string[] args)
        {
            Console.WriteLine("[!] Arguments: ");

            foreach (string arg in args)
            {
                Console.WriteLine("{0,15}{1}", "[+]", arg);
            }

            //Default executable to proc
            string exec = @"cmd.exe";

            if (args.Length > 0)
            {
                exec = args[0];
            }

            Console.WriteLine("[+] Proccing an executable...");

            try
            {
                //Proc an executable to demonstrate 
                Process myProcess = new Process();
                myProcess.StartInfo.FileName = exec;
                myProcess.Start();
                myProcess.WaitForExit();
            }
            catch (Exception ex)
            {
                Console.WriteLine("[!] Could not proc {0}!", exec);
                Console.Error.WriteLine("{0,15} Type: {1}", "[+]", ex.GetType());
                Console.Error.WriteLine("{0,15} Message: {1}", "[+]", ex.Message);
            }
        }
    }
}
