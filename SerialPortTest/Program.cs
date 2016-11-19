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
        const int BYTES_PER_BATCH = 100;

        static void Main(string[] args)
        {
            mySerialPort = new SerialPort( "COM4", 9600);
            mySerialPort.Open();

            while (true)
            { 
                String s = Console.ReadLine();
                byte[] bytOutput = new byte[BYTES_PER_BATCH];
                if (s.Equals("h")){
                    for (int i = 0; i < BYTES_PER_BATCH; i++) bytOutput[i] = 1;
                    mySerialPort.Write(bytOutput, 0, BYTES_PER_BATCH);
                }
                else if (s.Equals("l"))
                {
                    for (int i = 0; i < BYTES_PER_BATCH; i++) bytOutput[i] = 0;
                    mySerialPort.Write(bytOutput, 0, BYTES_PER_BATCH);
                }
                else if (System.Text.RegularExpressions.Regex.Match(s, "^[\\d]$").Success)
                {
                    mySerialPort.Write(s);
                    mySerialPort.Write(s);
                    //
                }
                System.Threading.Thread.Sleep(2000);
                Task t = ReadSerial();
                t.Wait();
            }

            
        }

        static async Task ReadSerial()
        {
            byte[] bytSerialEcho = new byte[BYTES_PER_BATCH];
            int intBytesRead = 0;

            while (intBytesRead < BYTES_PER_BATCH)
            {
                intBytesRead += await mySerialPort.BaseStream.ReadAsync(bytSerialEcho, intBytesRead, BYTES_PER_BATCH - intBytesRead);
            }

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
        }
    }
}
