#include "shape.cpp"
#include "grid_point.cpp"

class Grid{
  private:
    static const int MAX_CLEARED_ROWS = 4;
    int m_lstClearingRows[MAX_CLEARED_ROWS];
    int m_intActualClearingRows = 0;
    GridPoint m_objStaticPoints;
    
    bool shouldClearThisRow(int intRow)
    {
      for(int i : m_lstClearingRows)
      {
        if (intRow == i) return true;
      }
      return false;
    }

  public:
    static const int WIDTH = 10;
    static const int HEIGHT = 20;
    static const int LEFT_EDGE = 0;
    
    int getStaticPoint(int intColumn, int intRow)
    {
      return m_objStaticPoints.Points[intColumn][intRow];
    }

    int getActualClearingRows()
    {
      return m_intActualClearingRows;
    }

    
    Grid()
    {
        for(int x=0; x<WIDTH; x++){
            for(int y=0; y<HEIGHT; y++){
                m_objStaticPoints.Points[x][y] = ShapeEnums::NONE;
            }
        }
    }

    void lockShape(const Shape* objShape)
    {
        for (Point& p : objShape->getPoints().Points)
        {
            m_objStaticPoints.Points[p.X][p.Y] = objShape->getType();
        }
    }

    bool tryClear(const int intStartRow)
    {
        m_intActualClearingRows = 0;
        for (int row = intStartRow; row > intStartRow - MAX_CLEARED_ROWS && row >= 0; row--)
        {
            bool blnIsFull = true;
            for (int column = LEFT_EDGE; column < LEFT_EDGE + WIDTH; column++)
            {
                if (m_objStaticPoints.Points[column][row] == ShapeEnums::NONE) blnIsFull = false;
            }
            if (blnIsFull)
            {
                m_lstClearingRows[m_intActualClearingRows++] = row;
                for (int column = LEFT_EDGE; column < LEFT_EDGE + WIDTH; column++)
                {
                    m_objStaticPoints.Points[column][row] = ShapeEnums::CLEARING;
                }
            }
        }
  
        return m_intActualClearingRows > 0;
    }

    void finishClear()
    {
        int intRowsToDrop = 0;
  
        for (int row = HEIGHT - 1; row >= 0; row--)
        {
            if (shouldClearThisRow(row))
            {
                intRowsToDrop++;
            }
  
            if (row < intRowsToDrop){
                for (int column = LEFT_EDGE; column < LEFT_EDGE + WIDTH; column++)
                {
                    m_objStaticPoints.Points[column][row] = ShapeEnums::NONE;
                }
            }
            else if (intRowsToDrop > 0 && !shouldClearThisRow(row))
            {
                for (int column = LEFT_EDGE; column < LEFT_EDGE + WIDTH; column++)
                {
                    m_objStaticPoints.Points[column][row + intRowsToDrop] = m_objStaticPoints.Points[column][row];
                }
            }
        }
  
        m_intActualClearingRows = 0;
    }

    bool isCollision(const Shape* objShape) const
    {
        if (objShape->getRight() >= WIDTH) return true;
        if (objShape->getLeft() < LEFT_EDGE) return true;
        if (objShape->getBottomRow() == HEIGHT) return true;
  
        bool blnReturn = false;
        for (Point p : objShape->getPoints().Points)
        {
            ShapeEnums::Types objTest = m_objStaticPoints.Points[p.X][p.Y];
            if (objTest != ShapeEnums::NONE) blnReturn = true;
        }
        return blnReturn;
    }

};

