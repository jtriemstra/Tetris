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

        private DateTime m_dtNextDrop;
        private Shape m_objCurrentShape;
        private Grid m_objGrid = new Grid();
        private State m_objCurrentState = State.IDLE;
        private int m_intDropDelay = 2000;
        private RefreshDisplay m_fnRefreshDisplay;
        private DateTime m_dtStopClearing;

        public enum State
        {
            IDLE = 0,
            SHAPE_LIVE = 1,
            LOCKED = 2,
            CLEARING = 3
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

        public Game(RefreshDisplay fnRefreshDisplay)
        {
            m_fnRefreshDisplay = fnRefreshDisplay;
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
                m_objCurrentState = State.SHAPE_LIVE;
                m_objCurrentShape = new Shape(Shape.Types.SQUARE);
                return true;
            }

            return false;
        }

        public bool receiveInput()
        {
            if (m_objCurrentState == State.SHAPE_LIVE)
            {
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
                        m_objCurrentShape.MoveDown();
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
                    m_dtStopClearing = DateTime.MaxValue;
                    m_objCurrentState = State.IDLE;
                }
            }
        }

        public void refreshDisplay(bool blnDoUpdate)
        {
            if (blnDoUpdate)
            {
                if (m_objCurrentState == State.CLEARING)
                {
                }
                else if (m_objCurrentState == State.SHAPE_LIVE)
                {
                    m_fnRefreshDisplay(this.CurrentDisplay);
                }
            }
        }

    }
}
