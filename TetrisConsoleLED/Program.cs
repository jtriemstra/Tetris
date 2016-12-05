using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TetrisCommon;
using System.IO;
using System.IO.Ports;

namespace TetrisConsoleLED
{
    public class Program
    {
        private static SerialPort m_objSerial;
        private static int m_intLoopCount = 0;

        static void Main(string[] args)
        {
            m_objSerial = new SerialPort("COM4", 9600);
            m_objSerial.Open();

            Game g = new Game(RefreshConsole);
            g.play();
        }

        public static void RefreshConsole(Shape.Types[,] objPoints)
        {
            byte[] bytRow = new byte[Grid.WIDTH / 2];

            for (int y = 0; y < Grid.HEIGHT; y++)
            {
                for (int x = 0; x < Grid.WIDTH; x+=2)
                {
                    bytRow[x / 2] = (byte)((GetColor(objPoints[x, y]) << 4) | GetColor(objPoints[x + 1, y]));
                }
                
                m_objSerial.Write(bytRow, 0, Grid.WIDTH / 2);
                Console.Write(bytRow[0]);
                Console.Write(" ");
                Console.Write(bytRow[1]);
                Console.Write(" ");
                Console.Write(bytRow[2]);
                Console.Write(" ");
                Console.Write(bytRow[3]);
                Console.Write(" ");
                Console.Write(bytRow[4]);
                Console.WriteLine(" ");
                
            }

            m_intLoopCount++;

            //TODO: figure out why these fix the output
            Task t = ReadSerial();
            t.Wait();
        }

        private static int GetColor(Shape.Types objType)
        {
            switch (objType)
            {
                case Shape.Types.I:
                    return 1;                   
                case Shape.Types.J:
                    return 2;
                case Shape.Types.L:
                    return 3;
                case Shape.Types.NULL:
                    return 0;
                case Shape.Types.S:
                    return 4;
                case Shape.Types.SQUARE:
                    return 1;
                case Shape.Types.T:
                    return 5;
                case Shape.Types.Z:
                    return 6;
            }

            return 0;
        }

        const int BYTES_PER_BATCH = 2;

        static async Task ReadSerial()
        {
            byte[] bytSerialEcho = new byte[BYTES_PER_BATCH];
            int intBytesRead = 0;

            while (intBytesRead < BYTES_PER_BATCH)
            {
                intBytesRead += await m_objSerial.BaseStream.ReadAsync(bytSerialEcho, intBytesRead, BYTES_PER_BATCH - intBytesRead);
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
