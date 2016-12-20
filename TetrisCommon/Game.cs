using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TetrisCommon
{
    public class Game
    {
        public delegate void RefreshDisplay(Shape.Types[,] points);
        public delegate Command ReceiveInput();

        private DateTime m_dtNextDrop;
        private Shape m_objCurrentShape;
        private Grid m_objGrid = new Grid();
        private State m_objCurrentState = State.IDLE;
        private int m_intDropDelay = 1000;
        private RefreshDisplay m_fnRefreshDisplay;
        private ReceiveInput m_fnReceiveInput;
        private DateTime m_dtStopClearing;

        public enum State
        {
            IDLE = 0,
            SHAPE_LIVE = 1,
            LOCKED = 2,
            CLEARING = 3
        }

        public enum Command
        {
            NONE = 0,
            LEFT = 1,
            RIGHT = 2,
            CLOCKWISE = 3,
            COUNTERCLOCKWISE = 4,
            DOWN = 5
        }

        public Shape.Types[,] CurrentDisplay
        {
            get {
                Shape.Types[,] objReturn = m_objGrid.StaticPoints.Clone() as Shape.Types[,];
                foreach (Point p in m_objCurrentShape.Points)
                {
                    objReturn[p.X,p.Y] = m_objCurrentShape.Type;
                }
                return objReturn;
            }
        }

        public Game(RefreshDisplay fnRefreshDisplay, ReceiveInput fnReceiveInput)
        {
            m_fnRefreshDisplay = fnRefreshDisplay;
            m_fnReceiveInput = fnReceiveInput;
        }

        public void play()
        {
            bool blnUpdateDisplay;
            while (true)
            {
                blnUpdateDisplay = false;
                blnUpdateDisplay = blnUpdateDisplay || tryGenerate();
                blnUpdateDisplay = blnUpdateDisplay || receiveInput();
                blnUpdateDisplay = blnUpdateDisplay || tryDrop();
                tryClear();
                refreshDisplay(blnUpdateDisplay);
            }
        }

        public bool tryGenerate()
        {
            if (m_objCurrentState == State.IDLE)
            {
                Random objRand = new Random();

                m_objCurrentState = State.SHAPE_LIVE;
                m_objCurrentShape = new Shape((Shape.Types) objRand.Next(1,8));
                m_objCurrentShape.Center();
                return true;
            }

            return false;
        }

        public bool receiveInput()
        {
            if (m_objCurrentState == State.SHAPE_LIVE)
            {
                Command objThisCommand = m_fnReceiveInput();
                switch (objThisCommand)
                {
                    case Command.LEFT:
                        m_objCurrentShape.MoveLeft(Grid.LEFT_EDGE);
                        break;
                    case Command.RIGHT:
                        m_objCurrentShape.MoveRight(Grid.LEFT_EDGE + Grid.WIDTH);
                        break;
                    case Command.CLOCKWISE:
                        m_objCurrentShape.RotateClockwise(Grid.LEFT_EDGE, Grid.LEFT_EDGE + Grid.WIDTH);
                        break;
                    case Command.COUNTERCLOCKWISE:
                        m_objCurrentShape.RotateCounterclockwise();
                        break;
                    case Command.DOWN:
                        if (m_objGrid.ShapeCanDrop(m_objCurrentShape))
                        {
                            m_objCurrentShape.MoveDown(Grid.HEIGHT - 1);
                        }
                        break;
                }
                return objThisCommand != Command.NONE;
            }
            return false;
        }

        public bool tryDrop()
        {
            if (m_objCurrentState == State.SHAPE_LIVE)
            {
                if (DateTime.Now >= m_dtNextDrop)
                {
                    if (m_objGrid.ShapeCanDrop(m_objCurrentShape))
                    {
                        m_objCurrentShape.MoveDown(Grid.HEIGHT - 1);
                        m_dtNextDrop = DateTime.Now.AddMilliseconds(m_intDropDelay);
                    }
                    else
                    {
                        m_objGrid.LockShape(m_objCurrentShape);
                        m_objCurrentState = State.LOCKED;            
                    }
                    return true;
                }
            }

            return false;
        }

        public void tryClear()
        {
            if (m_objCurrentState == State.LOCKED)
            {
                if (m_objGrid.TryClear(m_objCurrentShape.BottomRow()))
                {
                    m_objCurrentState = State.CLEARING;
                    m_dtStopClearing = DateTime.Now.AddMilliseconds(1000);

                }
                else
                {
                    m_objCurrentState = State.IDLE;
                }
            }
            else if (m_objCurrentState == State.CLEARING)
            {
                if (DateTime.Now > m_dtStopClearing)
                {
                    m_objGrid.FinishClear();
                    m_dtStopClearing = DateTime.MaxValue;
                    m_objCurrentState = State.IDLE;
                }
            }
        }

        public void refreshDisplay(bool blnDoUpdate)
        {
            if (blnDoUpdate)
            {
                if (m_objCurrentState == State.SHAPE_LIVE || m_objCurrentState == State.CLEARING)
                {
                    m_fnRefreshDisplay(this.CurrentDisplay);
                }
            }
        }

    }
}
