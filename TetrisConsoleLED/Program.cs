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
    }
}
