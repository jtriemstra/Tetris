using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TetrisCommon
{
    public class Shape
    {
        private Types m_objType;
        private Point[] m_objPoints = new Point[]{ new Point(), new Point(), new Point(), new Point()};
        private ClockwiseRotations m_objCurrentRotation;
        
        public enum Types
        {
            NULL,
            I,
            T,
            S,
            Z,
            SQUARE,
            L,
            J
        }

        public enum ClockwiseRotations
        {
            INITIAL,
            NINETY,
            ONEEIGHTY,
            TWOSEVENTY
        }

        public Point[] Points { get { return m_objPoints; } }
        public Types Type { get { return m_objType; } }
        public int InitialWidth{get{return 0;}}

        public Shape(Types objType)
        {
            m_objType = objType;
            switch (m_objType)
            {
                case Types.I:
                    m_objPoints[0].X = 0;
                    m_objPoints[0].Y = 0;
                    m_objPoints[1].X = 0;
                    m_objPoints[1].Y = 1;
                    m_objPoints[2].X = 0;
                    m_objPoints[2].Y = 2;
                    m_objPoints[3].X = 0;
                    m_objPoints[3].Y = 3;
                    break;
                case Types.SQUARE:
                    m_objPoints[0].X = 0;
                    m_objPoints[0].Y = 0;
                    m_objPoints[1].X = 1;
                    m_objPoints[1].Y = 0;
                    m_objPoints[2].X = 0;
                    m_objPoints[2].Y = 1;
                    m_objPoints[3].X = 1;
                    m_objPoints[3].Y = 1;
                    break;
                case Types.T:
                    m_objPoints[0].X = 0;
                    m_objPoints[0].Y = 1;
                    m_objPoints[1].X = 1;
                    m_objPoints[1].Y = 0;
                    m_objPoints[2].X = 1;
                    m_objPoints[2].Y = 1;
                    m_objPoints[3].X = 2;
                    m_objPoints[3].Y = 1;
                    break;
                case Types.S:
                    m_objPoints[0].X = 0;
                    m_objPoints[0].Y = 1;
                    m_objPoints[1].X = 1;
                    m_objPoints[1].Y = 0;
                    m_objPoints[2].X = 1;
                    m_objPoints[2].Y = 1;
                    m_objPoints[3].X = 2;
                    m_objPoints[3].Y = 0;
                    break;
                case Types.Z:
                    m_objPoints[0].X = 0;
                    m_objPoints[0].Y = 0;
                    m_objPoints[1].X = 1;
                    m_objPoints[1].Y = 0;
                    m_objPoints[2].X = 1;
                    m_objPoints[2].Y = 1;
                    m_objPoints[3].X = 2;
                    m_objPoints[3].Y = 1;
                    break;
                case Types.J:
                    m_objPoints[0].X = 0;
                    m_objPoints[0].Y = 0;
                    m_objPoints[1].X = 0;
                    m_objPoints[1].Y = 1;
                    m_objPoints[2].X = 1;
                    m_objPoints[2].Y = 1;
                    m_objPoints[3].X = 2;
                    m_objPoints[3].Y = 1;
                    break;
                case Types.L:
                    m_objPoints[0].X = 0;
                    m_objPoints[0].Y = 1;
                    m_objPoints[1].X = 1;
                    m_objPoints[1].Y = 1;
                    m_objPoints[2].X = 2;
                    m_objPoints[2].Y = 1;
                    m_objPoints[3].X = 2;
                    m_objPoints[3].Y = 0;
                    break;
            }
        }

        public void Center()
        {
            foreach (Point p in m_objPoints)
            {
                p.X += 3;
            }
        }

        public int BottomRow()
        {
            int intReturn = Int32.MinValue;
            foreach (Point p in m_objPoints)
            {
                if (p.Y > intReturn) intReturn = p.Y;
            }
            return intReturn;
        }

        public void MoveDown()
        {
            foreach (Point p in m_objPoints)
            {
                p.Y += 1;
            }
        }

        public void MoveLeft(int intMinLeft)
        {
            bool blnLegal = true;
            foreach (Point p in m_objPoints)
            {
                if (p.X == intMinLeft) blnLegal = false;
            }
            if (blnLegal)
            {
                foreach (Point p in m_objPoints)
                {
                    p.X -= 1;
                }
            }
        }

        public void MoveRight(int intMaxRight)
        {
            bool blnLegal = true;
            foreach (Point p in m_objPoints)
            {
                if (p.X == intMaxRight) blnLegal = false;
            }
            if (blnLegal)
            {
                foreach (Point p in m_objPoints)
                {
                    p.X += 1;
                }
            }
        }

        public void RotateClockwise(int intMinLeft, int intMaxRight)
        {
            Point[] objTestPoints = new Point[] { new Point(), new Point(), new Point(), new Point() };
            switch (m_objType)
            {
                case Types.SQUARE:
                    break;
                case Types.I:
                    if (m_objCurrentRotation == ClockwiseRotations.INITIAL)
                    {
                        m_objPoints[0].X += 2;
                        m_objPoints[0].Y += 2;
                        m_objPoints[1].X += 1;
                        m_objPoints[1].Y += 1;
                        m_objPoints[3].X -= 1;
                        m_objPoints[3].Y -= 1;                        
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.ONEEIGHTY)
                    {
                        m_objPoints[3].X += 2;
                        m_objPoints[3].Y += 2;
                        m_objPoints[2].X += 1;
                        m_objPoints[2].Y += 1;
                        m_objPoints[0].X -= 1;
                        m_objPoints[0].Y -= 1;  
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.NINETY)
                    {
                        m_objPoints[0].X -= 1;
                        m_objPoints[0].Y += 1;
                        m_objPoints[2].X += 1;
                        m_objPoints[2].Y -= 1;
                        m_objPoints[3].X += 2;
                        m_objPoints[3].Y -= 2;  
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.TWOSEVENTY)
                    {
                        m_objPoints[0].X += 2;
                        m_objPoints[0].Y -= 2;
                        m_objPoints[1].X += 1;
                        m_objPoints[1].Y -= 1;
                        m_objPoints[3].X -= 1;
                        m_objPoints[3].Y += 1;  
                    }
                    break;
                case Types.T:
                    if (m_objCurrentRotation == ClockwiseRotations.INITIAL)
                    {
                        m_objPoints[0].X += 1;
                        m_objPoints[0].Y -= 1;
                        m_objPoints[1].X += 1;
                        m_objPoints[1].Y += 1;
                        m_objPoints[3].X -= 1;
                        m_objPoints[3].Y += 1;                        
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.ONEEIGHTY)
                    {
                        m_objPoints[3].X += 1;
                        m_objPoints[3].Y -= 1;
                        m_objPoints[1].X -= 1;
                        m_objPoints[1].Y -= 1;
                        m_objPoints[0].X -= 1;
                        m_objPoints[0].Y += 1;  
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.NINETY)
                    {
                        m_objPoints[0].X += 1;
                        m_objPoints[0].Y += 1;
                        m_objPoints[1].X -= 1;
                        m_objPoints[1].Y += 1;
                        m_objPoints[3].X -= 1;
                        m_objPoints[3].Y -= 1;  
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.TWOSEVENTY)
                    {
                        m_objPoints[0].X -= 1;
                        m_objPoints[0].Y -= 1;
                        m_objPoints[1].X += 1;
                        m_objPoints[1].Y -= 1;
                        m_objPoints[3].X += 1;
                        m_objPoints[3].Y += 1;  
                    }
                    break;
                case Types.S:
                    if (m_objCurrentRotation == ClockwiseRotations.INITIAL)
                    {
                        m_objPoints[0].X += 1;
                        m_objPoints[0].Y -= 1;
                        m_objPoints[1].X += 1;
                        m_objPoints[1].Y += 1;
                        m_objPoints[3].X -= 0;
                        m_objPoints[3].Y += 2;                        
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.ONEEIGHTY)
                    {
                        m_objPoints[3].X += 1;
                        m_objPoints[3].Y -= 1;
                        m_objPoints[2].X += 1;
                        m_objPoints[2].Y += 1;
                        m_objPoints[0].X -= 0;
                        m_objPoints[0].Y += 2;  
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.NINETY)
                    {
                        m_objPoints[0].X += 1;
                        m_objPoints[0].Y += 1;
                        m_objPoints[1].X -= 1;
                        m_objPoints[1].Y += 1;
                        m_objPoints[3].X -= 2;
                        m_objPoints[3].Y -= 0;  
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.TWOSEVENTY)
                    {
                        m_objPoints[3].X += 1;
                        m_objPoints[3].Y += 1;
                        m_objPoints[2].X -= 1;
                        m_objPoints[2].Y += 1;
                        m_objPoints[0].X -= 2;
                        m_objPoints[0].Y -= 0;  
                    }
                    break;
                case Types.Z:
                    if (m_objCurrentRotation == ClockwiseRotations.INITIAL)
                    {
                        m_objPoints[0].X += 2;
                        m_objPoints[0].Y -= 0;
                        m_objPoints[1].X += 1;
                        m_objPoints[1].Y += 1;
                        m_objPoints[3].X -= 1;
                        m_objPoints[3].Y += 1;                        
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.ONEEIGHTY)
                    {
                        m_objPoints[3].X += 2;
                        m_objPoints[3].Y -= 0;
                        m_objPoints[2].X += 1;
                        m_objPoints[2].Y += 1;
                        m_objPoints[0].X -= 1;
                        m_objPoints[0].Y += 1;  
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.NINETY)
                    {
                        m_objPoints[0].X += 0;
                        m_objPoints[0].Y += 2;
                        m_objPoints[1].X -= 1;
                        m_objPoints[1].Y += 1;
                        m_objPoints[3].X -= 1;
                        m_objPoints[3].Y -= 1;  
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.TWOSEVENTY)
                    {
                        m_objPoints[3].X += 0;
                        m_objPoints[3].Y += 2;
                        m_objPoints[2].X -= 1;
                        m_objPoints[2].Y += 1;
                        m_objPoints[0].X -= 1;
                        m_objPoints[0].Y -= 1;  
                    }
                    break;
                case Types.J:
                    if (m_objCurrentRotation == ClockwiseRotations.INITIAL)
                    {
                        m_objPoints[0].X += 2;
                        m_objPoints[0].Y += 0;
                        m_objPoints[1].X += 1;
                        m_objPoints[1].Y -= 1;
                        m_objPoints[3].X -= 1;
                        m_objPoints[3].Y += 1;
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.ONEEIGHTY)
                    {
                        m_objPoints[3].X += 1;
                        m_objPoints[3].Y -= 1;
                        m_objPoints[1].X -= 1; 
                        m_objPoints[1].Y += 1;
                        m_objPoints[0].X -= 2;
                        m_objPoints[0].Y += 0;
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.NINETY)
                    {
                        m_objPoints[0].X -= 0;
                        m_objPoints[0].Y += 2;
                        m_objPoints[1].X += 1;
                        m_objPoints[1].Y += 1;
                        m_objPoints[3].X -= 1; 
                        m_objPoints[3].Y -= 1;
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.TWOSEVENTY)
                    {
                        m_objPoints[3].X += 1;
                        m_objPoints[3].Y += 1;
                        m_objPoints[1].X -= 1;
                        m_objPoints[1].Y -= 1;
                        m_objPoints[0].X += 0;
                        m_objPoints[0].Y -= 2;
                    }
                    break;
                case Types.L:
                    if (m_objCurrentRotation == ClockwiseRotations.INITIAL)
                    {
                        m_objPoints[3].X += 0;
                        m_objPoints[3].Y += 2;
                        m_objPoints[2].X -= 1;
                        m_objPoints[2].Y += 1;
                        m_objPoints[0].X += 1;
                        m_objPoints[0].Y -= 1;
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.ONEEIGHTY)
                    {
                        m_objPoints[0].X -= 1;
                        m_objPoints[0].Y += 1;
                        m_objPoints[2].X += 1; 
                        m_objPoints[2].Y -= 1;
                        m_objPoints[3].X += 0;
                        m_objPoints[3].Y -= 2;
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.NINETY)
                    {
                        m_objPoints[3].X -= 2;
                        m_objPoints[3].Y -= 0;
                        m_objPoints[2].X -= 1;
                        m_objPoints[2].Y -= 1;
                        m_objPoints[0].X += 1; 
                        m_objPoints[0].Y -= 1;
                    }
                    else if (m_objCurrentRotation == ClockwiseRotations.TWOSEVENTY)
                    {
                        m_objPoints[0].X -= 1;
                        m_objPoints[0].Y -= 1;
                        m_objPoints[2].X += 1;
                        m_objPoints[2].Y += 1;
                        m_objPoints[3].X += 2;
                        m_objPoints[3].Y -= 0;
                    }
                    break;
            }

            switch (m_objCurrentRotation){
                case ClockwiseRotations.INITIAL:
                    m_objCurrentRotation = ClockwiseRotations.NINETY;
                    break;
                case ClockwiseRotations.NINETY:
                    m_objCurrentRotation = ClockwiseRotations.ONEEIGHTY;
                    break;
                case ClockwiseRotations.ONEEIGHTY:
                    m_objCurrentRotation = ClockwiseRotations.TWOSEVENTY;
                    break;
                case ClockwiseRotations.TWOSEVENTY:
                    m_objCurrentRotation = ClockwiseRotations.INITIAL;
                    break;
            }
        }

        public void RotateCounterclockwise()
        {

            switch (m_objCurrentRotation)
            {
                case ClockwiseRotations.INITIAL:
                    m_objCurrentRotation = ClockwiseRotations.TWOSEVENTY;
                    break;
                case ClockwiseRotations.NINETY:
                    m_objCurrentRotation = ClockwiseRotations.INITIAL;
                    break;
                case ClockwiseRotations.ONEEIGHTY:
                    m_objCurrentRotation = ClockwiseRotations.NINETY;
                    break;
                case ClockwiseRotations.TWOSEVENTY:
                    m_objCurrentRotation = ClockwiseRotations.ONEEIGHTY;
                    break;
            }
        }
    }
}
