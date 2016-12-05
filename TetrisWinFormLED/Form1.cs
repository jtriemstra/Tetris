using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using TetrisCommon;
using System.IO;
using System.IO.Ports;


namespace TetrisWinFormLED
{
    public partial class Form1 : Form
    {
        
        private static SerialPort m_objSerial;
        private static int m_intLoopCount = 0;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            m_objSerial = new SerialPort("COM4", 9600);
            m_objSerial.DataBits = 8;
            m_objSerial.Parity = Parity.None;
            m_objSerial.StopBits = StopBits.One;
            m_objSerial.Handshake = Handshake.None;
            m_objSerial.Encoding = System.Text.Encoding.Default;
            m_objSerial.Open();

            Game g = new Game(RefreshConsole);
            g.play();
        }



        public static void RefreshConsole(Shape.Types[,] objPoints)
        {
            byte[] bytRow = new byte[Grid.WIDTH / 2];

            for (int y = 0; y < Grid.HEIGHT; y++)
            {
                for (int x = 0; x < Grid.WIDTH; x += 2)
                {
                    bytRow[x / 2] = (byte)((GetColor(objPoints[x, y]) << 4) | GetColor(objPoints[x + 1, y]));
                }
                if (m_intLoopCount > -1)
                {
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
            }

            m_intLoopCount++;

            Task t = ReadSerialEcho();
            t.Wait();
        }

        private static async Task ReadSerialEcho()
        {
            int intBytesRead = 0;
            byte[] bytSerialEcho = new byte[2 * 24 * Grid.HEIGHT];
            while (intBytesRead < 2 * 24 * Grid.HEIGHT)
            {
                intBytesRead += await m_objSerial.BaseStream.ReadAsync(bytSerialEcho, intBytesRead, 2 * 24 * Grid.HEIGHT - intBytesRead);
                int y = 0;
            }

            for (int i = 0; i < bytSerialEcho.Length; i += 2)
            {
                for (int j = 0; j < 8; j++)
                {
                    //if (((1 << (7 - j)) & bytSerialEcho[i]) > 0) System.Diagnostics.Debug.Write("1");
                    //else System.Diagnostics.Debug.Write("0");
                }
                System.Diagnostics.Debug.Write(" ");
                for (int j = 0; j < 8; j++)
                {
                    //if (((1 << (7 - j)) & bytSerialEcho[i + 1]) > 0) System.Diagnostics.Debug.Write("1");
                    //else System.Diagnostics.Debug.Write("0");
                }
                System.Diagnostics.Debug.WriteLine("");
            }
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
