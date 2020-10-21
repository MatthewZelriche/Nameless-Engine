using System;


namespace NLSharp {

    public class Roslyn {
        public delegate void GenerateScriptDelegate(int damage);
        public static void GenerateScript(int damage) {
            Console.WriteLine(damage * 4);
        }

    }


}