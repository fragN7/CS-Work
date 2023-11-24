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
            hts.Add("www.cs.ubbcluj.ro/~rlupsa/edu/pdp/lecture-2-handling-concurrency.html");
            hts.Add("www.zhr-ucr.ro/index.php");
            hts.Add("www.flashscore.ro");

            DirCallbacks.run(hts);
            //BaseTask.run(hts, true);
            //Console.WriteLine("\n\n\n Test test \n\n\n");
            //BaseTask.run(hts, false);
        }

    }
}