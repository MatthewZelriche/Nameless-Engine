using System;
using System.Reflection;
using System.Runtime.InteropServices;


namespace NLSharp {
    [StructLayout(LayoutKind.Sequential)]
    public partial class Component {
    }


    public class ScriptBase : Component {

    }

    public class ScriptComponent {

        public ScriptComponent(object instance, MethodInfo[] methods) {
            scriptComponentInstance = instance;

            scriptMethods = methods;
        }
        public object scriptComponentInstance;

        MethodInfo[] scriptMethods;
    }

    [StructLayout(LayoutKind.Sequential)]
    public partial class Position : Component {
        public float x;
        public float y;
        public float z;
    }


}