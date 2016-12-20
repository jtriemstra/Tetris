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
        private static Game.Command m_objLastCommand = Game.Command.NONE;
        private static bool m_blnIsDisplaying = false;

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


            System.Threading.Thread t = new System.Threading.Thread(PlayGame);
            t.Start();
        }

        public static void PlayGame()
        {
            Game g = new Game(RefreshConsole, ReceiveInput);
            g.play();
        }

        public static Game.Command ReceiveInput()
        {
            Game.Command objTemp = m_objLastCommand;
            m_objLastCommand = Game.Command.NONE;
            return objTemp;
        }

        public static void RefreshConsole(Shape.Types[,] objPoints)
        {
            Console.WriteLine("refresh called");
            if (m_blnIsDisplaying) return;
            Console.WriteLine("doing refresh");
            m_blnIsDisplaying = true;
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
            Console.WriteLine("Loop: " + m_intLoopCount);
            m_intLoopCount++;

            //TODO: figure out why these fix the output
            //Task t = ReadSerial();
            
            //bool blnTimeout = t.Wait(1000);
            
            //Console.WriteLine("task completed? " + blnTimeout);
            m_blnIsDisplaying = false;
        }

        const int BYTES_PER_BATCH = Grid.HEIGHT * Grid.WIDTH / 2;

        static async Task ReadSerial()
        {
            byte[] bytSerialEcho = new byte[BYTES_PER_BATCH];
            int intBytesRead = 0;

            while (intBytesRead < BYTES_PER_BATCH)
            {
                intBytesRead += await m_objSerial.BaseStream.ReadAsync(bytSerialEcho, intBytesRead, BYTES_PER_BATCH - intBytesRead);
                Console.Write(intBytesRead + " bytes read");
            }

            Console.WriteLine("all bytes read");
            m_blnIsDisplaying = false;

            for (int i = 0; i < bytSerialEcho.Length; i += 5)
            {
                Console.Write(bytSerialEcho[i]);
                Console.Write(bytSerialEcho[i+1]);
                Console.Write(bytSerialEcho[i+2]);
                Console.Write(bytSerialEcho[i+3]);
                Console.WriteLine(bytSerialEcho[i+4]);
            }

            /*for (int i = 0; i < bytSerialEcho.Length; i += 2)
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
            }*/
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
                case Shape.Types.CLEARING:
                    return 7;
            }

            return 0;
        }


        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == Keys.Left)
            {
                m_objLastCommand = Game.Command.LEFT;
                return true;
            }
            if (keyData == Keys.Right)
            {
                m_objLastCommand = Game.Command.RIGHT;
                return true;
            }
            if (keyData == Keys.F1)
            {
                m_objLastCommand = Game.Command.COUNTERCLOCKWISE;
                return true;
            }
            if (keyData == Keys.F2)
            {
                m_objLastCommand = Game.Command.CLOCKWISE;
                return true;
            }
            if (keyData == Keys.Down)
            {
                m_objLastCommand = Game.Command.DOWN;
                return true;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }
    }
}
