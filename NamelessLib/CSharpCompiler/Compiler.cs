using System;
using System.Runtime;
using System.Reflection;
using System.IO;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;


namespace CSharpCompiler {
    public class Compiler {
        //[DllImport("/home/nerevar/Programming/Zelriche/Nameless-Engine/build/Debug/bin/libNamelessLib.so")]
        //public static extern bool ExampleClassMethodBinding(Position pos);

        public static void CCCCCreateNewScriptComponent(string name, string projectName) {
            //Directory.CreateDirectory("../../../Projects/" + Marshal.PtrToStringAuto(projectName) + "/" + "bin/");
            //SaveScriptToFile(GenerateScript(Marshal.PtrToStringAuto(name)), Marshal.PtrToStringAuto(projectName), Marshal.PtrToStringAuto(name));


            //Type type = Type.GetType("NLSharp.")
            //var instance = Activator.CreateInstance()
            //var temp = new ScriptComponent();
        }

        public static void SaveScriptToFile(string scriptContents, string projectName, string scriptName) {
            Directory.CreateDirectory("../../../Projects/" + projectName + "/" + "Scripts/");
            File.WriteAllText("../../../Projects/" + projectName + "/" + "Scripts/" + scriptName + ".scr", scriptContents);
        }

        public static void CompileScript(string projectName, string name) {
                        // Test
            var dotNetCoreDir = Path.GetDirectoryName(typeof(object).GetTypeInfo().Assembly.Location);
            var runtimeRef = MetadataReference.CreateFromFile(Path.Combine(dotNetCoreDir, "System.Runtime.dll"));

            // CompileScript(name)
            var source = File.ReadAllText("../../../Projects/" + projectName + "/" + "Scripts/" + name + ".scr");
            var syntaxTree = CSharpSyntaxTree.ParseText(source);
            string assemblyName = "Test.dll";
            var objectRef = MetadataReference.CreateFromFile(typeof(object).Assembly.Location);
            var NLSharpRef = MetadataReference.CreateFromFile("NLSharp/NLSharp.dll");
            var options = new CSharpCompilationOptions(OutputKind.DynamicallyLinkedLibrary, assemblyIdentityComparer: DesktopAssemblyIdentityComparer.Default);
            var testt = CSharpCompilation.Create(assemblyName, new SyntaxTree[] { syntaxTree }, new MetadataReference[] { objectRef, NLSharpRef, runtimeRef }, options);

            //var hashTest = source.GetHashCode();
            //Console.WriteLine(hashTest);

            var result = testt.Emit("../../../Projects/" + projectName + "/" + "bin/" + assemblyName);

            if (!result.Success) {
                foreach(var diagnostic in result.Diagnostics)
                {
                    Console.WriteLine(diagnostic.ToString());
                }
            }
        }

        public static string GenerateScript(string name) {
            var script = SyntaxFactory.CompilationUnit();
            Microsoft.CodeAnalysis.CSharp.Syntax.UsingDirectiveSyntax[] usingStatements = new Microsoft.CodeAnalysis.CSharp.Syntax.UsingDirectiveSyntax[] {
                                                                    SyntaxFactory.UsingDirective(SyntaxFactory.ParseName("System")),
                                                                    SyntaxFactory.UsingDirective(SyntaxFactory.ParseName("System.Runtime")),
                                                                    SyntaxFactory.UsingDirective(SyntaxFactory.ParseName("NLSharp"))};
            script = script.AddUsings(usingStatements);
            
            var scriptClass = SyntaxFactory.ClassDeclaration(name);
            scriptClass = scriptClass.AddModifiers(SyntaxFactory.Token(SyntaxKind.PublicKeyword));

            scriptClass = scriptClass.AddBaseListTypes(SyntaxFactory.SimpleBaseType(SyntaxFactory.ParseTypeName("NLSharp.ScriptBase")));


            var onCreateMethod = SyntaxFactory.MethodDeclaration(SyntaxFactory.ParseTypeName("void"), "OnCreate")
                                                .AddModifiers(SyntaxFactory.Token(SyntaxKind.PublicKeyword))
                                                .WithBody(SyntaxFactory.Block(null));
            
            var onUpdateMethod = SyntaxFactory.MethodDeclaration(SyntaxFactory.ParseTypeName("void"), "OnUpdate")
                                                .AddModifiers(SyntaxFactory.Token(SyntaxKind.PublicKeyword))
                                                .WithBody(SyntaxFactory.Block(null));

            scriptClass = scriptClass.AddMembers(onCreateMethod, onUpdateMethod);

            script = script.AddMembers(scriptClass);

            return script.NormalizeWhitespace().ToFullString();

            /*
            EntityManager manager = new EntityManager();
            manager.CreateNewEntityArchetype();
            manager.GetEntityArchetype(0).AddComponentToEntity<Position>(new Position());
            Position bab = manager.GetEntityArchetype(0).GetComponent<Position>();
            bab.x = 45;

            manager.GetEntityArchetype(0).AddComponentToEntity<MyScript>(new MyScript());

            ExampleClassMethodBinding(manager.GetEntityArchetype(0).GetComponent<Position>());

            List<System.Reflection.MethodInfo> myList = new List<System.Reflection.MethodInfo>();


            /*
            // PROTOTYPE

            List<ScriptComponent> components = new List<ScriptComponent>();

            Type myType = Type.GetType("NLSharp.MyScript, NLSharp");
            Type myType2 = Type.GetType("NLSharp.Script2, NLSharp");
            var boobab = myType.GetMethod("OnCreate");
            var instance = Activator.CreateInstance(myType);
            var instance2 = Activator.CreateInstance(myType2);
            var newObj1 = new ScriptComponent(instance);
            var newObj2 = new ScriptComponent(instance2);

            newObj1.scriptComponentInstance = instance;
            newObj2.scriptComponentInstance = instance2;

            components.Add((ScriptComponent)newObj1);
            components.Add((ScriptComponent)newObj2);


            // For getting one script from another script.
            foreach (var element in components) {
                if (element.scriptComponentInstance.GetType() == typeof(MyScript)) {
                    ((MyScript)element.scriptComponentInstance).OnCreate();
                }
            }


            /*

            Use Roslyn to generate script file. 
            Compile Script
            Get Type of newly compiled script
            Use GetMethod on the type to check for magic methods, and store them in their respective MethodInfo lists on the entity. (tuple? or store the method in the Script Object?MethodInfo needs access to the instance.)
            Create new Script with CreateInstance.
            Store the script instance in a new ScriptObject
            Add ScriptObject to list of components on entity. 

            //var methodd = myType.GetMethod("OnCreate");

            //var testo = myType.GetFields(System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Public);

            //methodd.Invoke(instance, null);
            //byte[] buffer = new byte[maxBytesNeeded];
            //int bytesWritten = FlatBufferSerializer.Default.Serialize(fuckass, buffer);

            

            /* Pseudocode

            Roslyn::CreateScript(name, entity) {
                GenerateNewScriptFile(name);

                CreateNewScriptInstanceOfType(name, entity); -> would just generate manager.GetEntityArchetype(0).AddComponentToEntity<NewScriptComponent>()
                                                             -> Then would call manager.GetEntityArchetype(0).GetComponent<NewScriptComponent>().mEntityID = entity
            }

            From here, iterate over all entities, check if they contain ScriptComponents, and if they do attempt to Invoke appropriate Method (eg OnUpdate() in the update loop, etc)
            Like below:
            */
        }

    }
}