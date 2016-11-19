using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DebugTest
{
    class Program
    {
        static void Main(string[] args)
        {
            byte[] bytSerialEcho = new byte[] { 0, 17, 63, 255 };

            for (int i = 0; i < bytSerialEcho.Length; i += 2)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (((1 << (7 - j)) & bytSerialEcho[i]) > 0) System.Diagnostics.Debug.Write("1");
                    else System.Diagnostics.Debug.Write("0");
                }
                System.Diagnostics.Debug.Write(" ");
                for (int j = 0; j < 8; j++)
                {
                    if (((1 << (7 - j)) & bytSerialEcho[i + 1]) > 0) System.Diagnostics.Debug.Write("1");
                    else System.Diagnostics.Debug.Write("0");
                }
                System.Diagnostics.Debug.WriteLine("");
            }

            Console.ReadLine();
        }
    }
}
