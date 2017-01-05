#include "shape.cpp"
#include "grid_point.cpp"

class Grid{
  private:
    static const int MAX_CLEARED_ROWS = 4;
    GridPoint m_objStaticPoints;
    int m_lstClearingRows[MAX_CLEARED_ROWS];
    int m_intActualClearingRows = 0;

    bool ShouldClearThisRow(int intRow)
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
    int* ClearingRows() const { return m_lstClearingRows;  }
    GridPoint StaticPoints() const {  return m_objStaticPoints; } 
    
    Grid()
    {
        for(int x=0; x<WIDTH; x++){
            for(int y=0; y<HEIGHT; y++){
                m_objStaticPoints.Points[x][y] = ShapeEnums::NULL;
            }
        }
    }

    void LockShape(const Shape* objShape)
    {
        for (Point& p : objShape->Points().Points)
        {
            m_objStaticPoints.Points[p.X][p.Y] = objShape->Type();
        }
    }

    bool TryClear(const int intStartRow)
    {
        m_intActualClearingRows = 0;
        for (int row = intStartRow; row > intStartRow - MAX_CLEARED_ROWS && row >= 0; row--)
        {
            bool blnIsFull = true;
            for (int column = LEFT_EDGE; column < LEFT_EDGE + WIDTH; column++)
            {
                if (m_objStaticPoints.Points[column][row] == ShapeEnums::NULL) blnIsFull = false;
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

    void FinishClear()
    {
        int intRowsToDrop = 0;
  
        for (int row = HEIGHT - 1; row >= 0; row--)
        {
            if (ShouldClearThisRow(row))
            {
                intRowsToDrop++;
            }
  
            if (row < intRowsToDrop){
                for (int column = LEFT_EDGE; column < LEFT_EDGE + WIDTH; column++)
                {
                    m_objStaticPoints.Points[column][row] = ShapeEnums::NULL;
                }
            }
            else if (intRowsToDrop > 0 && !ShouldClearThisRow(row))
            {
                for (int column = LEFT_EDGE; column < LEFT_EDGE + WIDTH; column++)
                {
                    m_objStaticPoints.Points[column][row + intRowsToDrop] = m_objStaticPoints.Points[column][row];
                }
            }
        }
  
        m_intActualClearingRows = 0;
    }

    bool ShapeCanDrop(const Shape* objShape) const
    {
        if (objShape->BottomRow() == HEIGHT - 1) return false;
  
        bool blnReturn = true;
        for (Point p : objShape->Points().Points)
        {
            ShapeEnums::Types objTest = m_objStaticPoints.Points[p.X][p.Y + 1];
            if (objTest != ShapeEnums::NULL) blnReturn = false;
        }
        return blnReturn;
    }  
};

