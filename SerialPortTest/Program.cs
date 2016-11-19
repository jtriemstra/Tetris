using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.IO;


namespace SerialPortTest
{
    class Program
    {
        static SerialPort mySerialPort;

        static void Main(string[] args)
        {
            mySerialPort = new SerialPort( "COM4", 9600);
            mySerialPort.Open();

            while (true)
            { 
                String s = Console.ReadLine();
                if (s.Equals("h")){
                    mySerialPort.Write(new byte[] { 1 }, 0, 1);
                }
                else if (s.Equals("l"))
                {
                    mySerialPort.Write(new byte[] { 0 }, 0, 1);
                }
                else if (System.Text.RegularExpressions.Regex.Match(s, "^[\\d]$").Success)
                {
                    mySerialPort.Write(s);
                    mySerialPort.Write(s);
                    //
                }

                Task t = ReadSerial();
                t.Wait();
            }

            
        }

        static async Task ReadSerial()
        {
            byte[] bytSerialEcho = { 255 };
            await mySerialPort.BaseStream.ReadAsync(bytSerialEcho, 0, 1);

            for (int i = 0; i < bytSerialEcho.Length; i += 1)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (((1 << (7 - j)) & bytSerialEcho[i]) > 0) System.Diagnostics.Debug.Write("1");
                    else System.Diagnostics.Debug.Write("0");
                }
               
                System.Diagnostics.Debug.WriteLine("");
            }
        }
    }
}
