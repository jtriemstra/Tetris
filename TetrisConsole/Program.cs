using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TetrisCommon;

namespace TetrisConsole
{
    class Program
    {
        static void Main(string[] args)
        {
            Game g = new Game(RefreshConsole, ReceiveInput);
            g.play();
        }

        public static Game.Command ReceiveInput()
        {
            return Game.Command.NONE;
        }

        public static void RefreshConsole(Shape.Types[,] objPoints)
        {
            Console.Clear();
            for (int y = 0; y < Grid.HEIGHT; y++)
            {
                Console.Write("|");
                for (int x = 0; x < Grid.WIDTH; x++)
                {
                    if (objPoints[x,y] == Shape.Types.NULL) Console.Write(" ");
                    else Console.Write("X");
                }
                Console.WriteLine("|");
            }

            for (int x = 0; x < Grid.WIDTH; x++)
            {
                Console.Write("-");
            }
            Console.WriteLine();
        }
    }
}
