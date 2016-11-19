using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TetrisCommon;

namespace Tetris
{
    class Program
    {
        static void Main(string[] args)
        {
            Shape objCurrentShape = null;

            while (true)
            {
                String input = Console.ReadLine();
                switch (input)
                {
                    case "i":
                        objCurrentShape = new Shape(Shape.Types.I);
                        break;
                    case "t":
                        objCurrentShape = new Shape(Shape.Types.T);
                        break;
                    case "q":
                        objCurrentShape = new Shape(Shape.Types.SQUARE);
                        break;
                    case "s":
                        objCurrentShape = new Shape(Shape.Types.S);
                        break;
                    case "z":
                        objCurrentShape = new Shape(Shape.Types.Z);
                        break;
                    case "l":
                        objCurrentShape.MoveLeft(0);
                        break;
                    case "r":
                        objCurrentShape.MoveRight(10);
                        break;
                    case "g":
                        objCurrentShape.RotateClockwise(0,10);
                        break;
                }

                if (objCurrentShape != null)
                {
                    for (int y = 0; y < 11; y++)
                    {
                        for (int x = 0; x < 11; x++)
                        {
                            bool blnIsOutput = false;
                            for (int i = 0; i < objCurrentShape.Points.Length; i++)
                            {
                                if (objCurrentShape.Points[i].X == x && objCurrentShape.Points[i].Y == y)
                                {
                                    Console.Write("X");
                                    blnIsOutput = true;
                                }                                
                            }
                            if (!blnIsOutput) Console.Write(" ");
                        }
                        Console.WriteLine();
                    }
                }
            }
        }
    }
}
