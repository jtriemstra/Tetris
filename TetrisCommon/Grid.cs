using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TetrisCommon
{
    public class Grid
    {
        public const int WIDTH = 10;
        public const int HEIGHT = 20;
        public const int LEFT_EDGE = 0;

        private Shape.Types[,] m_objStaticPoints = new Shape.Types[WIDTH,HEIGHT];
        private List<int> m_lstClearingRows = new List<int>();

        public List<int> ClearingRows { get { return m_lstClearingRows; } }

        public Grid()
        {
            for(int x=0; x<WIDTH; x++){
                for(int y=0; y<HEIGHT; y++){
                    m_objStaticPoints[x,y] = Shape.Types.NULL;
                }
            }
        }

        public void LockShape(Shape objShape)
        {
            foreach (Point p in objShape.Points)
            {
                m_objStaticPoints[p.X,p.Y] = objShape.Type;
            }
        }

        public Shape.Types[,] StaticPoints { get { return m_objStaticPoints; } }

        public bool TryClear(int intStartRow)
        {
            for (int row = intStartRow; row > intStartRow - 4 && row >= 0; row--)
            {
                bool blnIsFull = true;
                for (int column = LEFT_EDGE; column < LEFT_EDGE + WIDTH; column++)
                {
                    if (m_objStaticPoints[column,row] == Shape.Types.NULL) blnIsFull = false;
                }
                if (blnIsFull)
                {
                    m_lstClearingRows.Add(row);
                    for (int column = LEFT_EDGE; column < LEFT_EDGE + WIDTH; column++)
                    {
                        m_objStaticPoints[column, row] = Shape.Types.CLEARING;
                    }
                }
            }

            return m_lstClearingRows.Count > 0;
        }

        public void FinishClear()
        {
            int intRowsToDrop = 0;

            for (int row = HEIGHT - 1; row >= 0; row--)
            {
                if (m_lstClearingRows.Contains(row))
                {
                    intRowsToDrop++;
                }

                if (row < intRowsToDrop){
                    for (int column = LEFT_EDGE; column < LEFT_EDGE + WIDTH; column++)
                    {
                        m_objStaticPoints[column, row] = Shape.Types.NULL;
                    }
                }
                else if (intRowsToDrop > 0 && !m_lstClearingRows.Contains(row))
                {
                    for (int column = LEFT_EDGE; column < LEFT_EDGE + WIDTH; column++)
                    {
                        m_objStaticPoints[column, row + intRowsToDrop] = m_objStaticPoints[column, row];
                    }
                }
            }

            m_lstClearingRows.Clear();
        }

        public bool ShapeCanDrop(Shape objShape)
        {
            if (objShape == null) throw new Exception("no shape");

            if (objShape.BottomRow() == HEIGHT - 1) return false;

            bool blnReturn = true;
            foreach (Point p in objShape.Points)
            {
                if (m_objStaticPoints[p.X,p.Y + 1] != Shape.Types.NULL) blnReturn = false;
            }
            return blnReturn;
        }
    }
}
