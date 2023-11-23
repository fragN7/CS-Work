using System;
using System.Collections.Generic;
using FutureTPL.Implementations;

namespace FutureTPL
{
    public static class Program
    {
        private static List<String> hts = new List<String>();

        static void Main()
        {
            hts.Add("www.cs.ubbcluj.ro/~rlupsa/edu/pdp");
            hts.Add("youtube.com");
            hts.Add("google.com");

            DirCallbacks.run(hts);
            //BaseTask.run(hts, false);
        }

    }
}