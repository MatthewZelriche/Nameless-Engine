using System;
using System.Reflection;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using MessagePack;

namespace NLSharp {
[MessagePackObject]
public class MyClass
{
    // Key attributes take a serialization index (or string name)
    // The values must be unique and versioning has to be considered as well.
    // Keys are described in later sections in more detail.
    [Key(0)]
    public int Age { get; set; }

    [Key(1)]
    public string FirstName { get; set; }

    [Key(2)]
    public string LastName { get; set; }

    // All fields or properties that should not be serialized must be annotated with [IgnoreMember].
    [IgnoreMember]
    public string FullName { get { return FirstName + LastName; } }
}

    class ScriptCreator {

        [UnmanagedCallersOnly]
        public static void CreateNewScriptComponent(IntPtr name, IntPtr projectName) {
            CSharpCompiler.Compiler.SaveScriptToFile(CSharpCompiler.Compiler.GenerateScript(Marshal.PtrToStringAuto(name)), Marshal.PtrToStringAuto(projectName), Marshal.PtrToStringAuto(name));
            CSharpCompiler.Compiler.CompileScript(Marshal.PtrToStringAuto(projectName), Marshal.PtrToStringAuto(name), "TempAssemblyName");


            Assembly assembly = Assembly.LoadFrom("/home/nerevar/Programming/Zelriche/Nameless-Engine/Projects/MyTestProject/bin/TempAssemblyName.dll");
            //var test = assembly.DefinedTypes;
        }

    }

/*
    public class MyScript : ScriptBase {
        public int garbo {get; set; } = 5;
        public void OnCreate() {
            Console.WriteLine("Tes1");
        }

        public void OnUpdate() {

        }

        public void Dgaf() {
            Console.WriteLine("goob");
        }
    }


    public class Script2 : ScriptBase {
        public int garbo = 12;
    }

*/


}