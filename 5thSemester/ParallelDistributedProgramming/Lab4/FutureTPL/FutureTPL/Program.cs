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
            hts.Add("www.dspcluj.ro/HTML/CORONAVIRUS/incidenta.html");
            hts.Add("www.zhr-ucr.ro/index.php");
            hts.Add("w");
            
            try
            {
                //DirCallbacks.run(hts);
                BaseTask.run(hts, false);
                // BaseTask.run(hts, true);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception handled");
            }
        }

    }
}