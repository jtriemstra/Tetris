class Shape
{
    private:
      Shape::Types m_objType;
      Point[] m_objPoints = new Point[]{ new Point(), new Point(), new Point(), new Point()};
      ClockwiseRotations m_objCurrentRotation;
    
    public:
      enum Types
      {
          NULL,
          I,
          T,
          S,
          Z,
          SQUARE,
          L,
          J,
          CLEARING
      }

      enum ClockwiseRotations
      {
          INITIAL,
          NINETY,
          ONEEIGHTY,
          TWOSEVENTY
      }

      Point[] Points() { return m_objPoints; } 
      Types Type() { return m_objType; } 
      int InitialWidth() {return 0;}

    Shape(Types objType)
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

    void Center()
    {
        foreach (Point p in m_objPoints)
        {
            p.X += 3;
        }
    }

    int BottomRow()
    {
        int intReturn = Int32.MinValue;
        foreach (Point p in m_objPoints)
        {
            if (p.Y > intReturn) intReturn = p.Y;
        }
        return intReturn;
    }

    void MoveDown(int intMaxRow)
    {
        bool blnLegal = true;
        foreach (Point p in m_objPoints)
        {
            if (p.Y == intMaxRow) blnLegal = false;
        }
        if (blnLegal)
        {
            foreach (Point p in m_objPoints)
            {
                p.Y += 1;
            }
        }
    }

    void MoveLeft(int intMinLeft)
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

    void MoveRight(int intMaxRight)
    {
        bool blnLegal = true;
        foreach (Point p in m_objPoints)
        {
            if (p.X == intMaxRight - 1) blnLegal = false;
        }
        if (blnLegal)
        {
            foreach (Point p in m_objPoints)
            {
                p.X += 1;
            }
        }
    }

    void RotateClockwise(int intMinLeft, int intMaxRight)
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
                    m_objPoints[0].Y += 1;
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

    void RotateCounterclockwise()
    {
        switch (m_objType)
        {
            case Types.SQUARE:
                break;
            case Types.I:
                if (m_objCurrentRotation == ClockwiseRotations.INITIAL)
                {
                    m_objPoints[0].X -= 2;
                    m_objPoints[0].Y += 2;
                    m_objPoints[1].X -= 1;
                    m_objPoints[1].Y += 1;
                    m_objPoints[3].X += 1;
                    m_objPoints[3].Y -= 1;   
                }
                else if (m_objCurrentRotation == ClockwiseRotations.ONEEIGHTY)
                {
                    m_objPoints[0].X += 1;
                    m_objPoints[0].Y -= 1;
                    m_objPoints[2].X -= 1;
                    m_objPoints[2].Y += 1;
                    m_objPoints[3].X -= 2;
                    m_objPoints[3].Y += 2;                          
                }
                else if (m_objCurrentRotation == ClockwiseRotations.NINETY)
                {

                    m_objPoints[0].X -= 2;
                    m_objPoints[0].Y -= 2;
                    m_objPoints[1].X -= 1;
                    m_objPoints[1].Y -= 1;
                    m_objPoints[3].X += 1;
                    m_objPoints[3].Y += 1;   
                }
                else if (m_objCurrentRotation == ClockwiseRotations.TWOSEVENTY)
                {
                    m_objPoints[3].X -= 2;
                    m_objPoints[3].Y -= 2;
                    m_objPoints[2].X -= 1;
                    m_objPoints[2].Y -= 1;
                    m_objPoints[0].X += 1;
                    m_objPoints[0].Y += 1;  
                }
                break;
            case Types.T:
                if (m_objCurrentRotation == ClockwiseRotations.INITIAL)
                {
                    m_objPoints[0].X += 1;
                    m_objPoints[0].Y += 1;
                    m_objPoints[1].X -= 1;
                    m_objPoints[1].Y += 1;
                    m_objPoints[3].X -= 1;
                    m_objPoints[3].Y -= 1;  
                                           
                }
                else if (m_objCurrentRotation == ClockwiseRotations.ONEEIGHTY)
                {
                    m_objPoints[0].X -= 1;
                    m_objPoints[0].Y -= 1;
                    m_objPoints[1].X += 1;
                    m_objPoints[1].Y -= 1;
                    m_objPoints[3].X += 1;
                    m_objPoints[3].Y += 1;  

                }
                else if (m_objCurrentRotation == ClockwiseRotations.NINETY)
                {
                    m_objPoints[0].X -= 1;
                    m_objPoints[0].Y += 1;
                    m_objPoints[1].X -= 1;
                    m_objPoints[1].Y -= 1;
                    m_objPoints[3].X += 1;
                    m_objPoints[3].Y -= 1; 

                    
                }
                else if (m_objCurrentRotation == ClockwiseRotations.TWOSEVENTY)
                {
                    m_objPoints[3].X -= 1;
                    m_objPoints[3].Y += 1;
                    m_objPoints[1].X += 1;
                    m_objPoints[1].Y += 1;
                    m_objPoints[0].X += 1;
                    m_objPoints[0].Y -= 1;  

                }
                break;
            case Types.S:
                if (m_objCurrentRotation == ClockwiseRotations.INITIAL)
                {
                    m_objPoints[3].X -= 1;
                    m_objPoints[3].Y -= 1;
                    m_objPoints[2].X += 1;
                    m_objPoints[2].Y -= 1;
                    m_objPoints[0].X += 2;
                    m_objPoints[0].Y += 0;
                                     
                }
                else if (m_objCurrentRotation == ClockwiseRotations.ONEEIGHTY)
                {
                    m_objPoints[0].X -= 1;
                    m_objPoints[0].Y -= 1;
                    m_objPoints[1].X += 1;
                    m_objPoints[1].Y -= 1;
                    m_objPoints[3].X += 2;
                    m_objPoints[3].Y += 0;  
                }
                else if (m_objCurrentRotation == ClockwiseRotations.NINETY)
                {
                    m_objPoints[0].X -= 1;
                    m_objPoints[0].Y += 1;
                    m_objPoints[1].X -= 1;
                    m_objPoints[1].Y -= 1;
                    m_objPoints[3].X += 0;
                    m_objPoints[3].Y -= 2;      
                }
                else if (m_objCurrentRotation == ClockwiseRotations.TWOSEVENTY)
                {
                    m_objPoints[3].X -= 1;
                    m_objPoints[3].Y += 1;
                    m_objPoints[2].X -= 1;
                    m_objPoints[2].Y -= 1;
                    m_objPoints[0].X += 0;
                    m_objPoints[0].Y -= 2;  
                }
                break;
            case Types.Z:
                if (m_objCurrentRotation == ClockwiseRotations.INITIAL)
                {
                    m_objPoints[3].X -= 0;
                    m_objPoints[3].Y -= 2;
                    m_objPoints[2].X += 1;
                    m_objPoints[2].Y -= 1;
                    m_objPoints[0].X += 1;
                    m_objPoints[0].Y += 1;  
                    
                }
                else if (m_objCurrentRotation == ClockwiseRotations.ONEEIGHTY)
                {
                    m_objPoints[0].X -= 0;
                    m_objPoints[0].Y -= 2;
                    m_objPoints[1].X += 1;
                    m_objPoints[1].Y -= 1;
                    m_objPoints[3].X += 1;
                    m_objPoints[3].Y += 1;  
                }
                else if (m_objCurrentRotation == ClockwiseRotations.NINETY)
                {
                    m_objPoints[0].X -= 2;
                    m_objPoints[0].Y += 0;
                    m_objPoints[1].X -= 1;
                    m_objPoints[1].Y -= 1;
                    m_objPoints[3].X += 1;
                    m_objPoints[3].Y -= 1;                        
                }
                else if (m_objCurrentRotation == ClockwiseRotations.TWOSEVENTY)
                {
                    m_objPoints[3].X -= 2;
                    m_objPoints[3].Y += 0;
                    m_objPoints[2].X -= 1;
                    m_objPoints[2].Y -= 1;
                    m_objPoints[0].X += 1;
                    m_objPoints[0].Y -= 1;  
                }
                break;
            case Types.J:
                if (m_objCurrentRotation == ClockwiseRotations.INITIAL)
                {
                    m_objPoints[3].X -= 1;
                    m_objPoints[3].Y -= 1;
                    m_objPoints[1].X += 1;
                    m_objPoints[1].Y += 1;
                    m_objPoints[0].X -= 0;
                    m_objPoints[0].Y += 2;
                    
                }
                else if (m_objCurrentRotation == ClockwiseRotations.ONEEIGHTY)
                {
                    m_objPoints[0].X += 0;
                    m_objPoints[0].Y -= 2;
                    m_objPoints[1].X -= 1;
                    m_objPoints[1].Y -= 1;
                    m_objPoints[3].X += 1;
                    m_objPoints[3].Y += 1;

                }
                else if (m_objCurrentRotation == ClockwiseRotations.NINETY)
                {
                    m_objPoints[0].X -= 2;
                    m_objPoints[0].Y -= 0;
                    m_objPoints[1].X -= 1;
                    m_objPoints[1].Y += 1;
                    m_objPoints[3].X += 1;
                    m_objPoints[3].Y -= 1;
                    
                }
                else if (m_objCurrentRotation == ClockwiseRotations.TWOSEVENTY)
                {

                    m_objPoints[3].X -= 1;
                    m_objPoints[3].Y += 1;
                    m_objPoints[1].X += 1;
                    m_objPoints[1].Y -= 1;
                    m_objPoints[0].X += 2;
                    m_objPoints[0].Y -= 0;

                    
                }
                break;
            case Types.L:
                if (m_objCurrentRotation == ClockwiseRotations.INITIAL)
                {
                    m_objPoints[0].X += 1;
                    m_objPoints[0].Y += 1;
                    m_objPoints[2].X -= 1;
                    m_objPoints[2].Y -= 1;
                    m_objPoints[3].X -= 2;
                    m_objPoints[3].Y += 0;
                }
                else if (m_objCurrentRotation == ClockwiseRotations.ONEEIGHTY)
                {
                    m_objPoints[3].X += 2;
                    m_objPoints[3].Y += 0;
                    m_objPoints[2].X += 1;
                    m_objPoints[2].Y += 1;
                    m_objPoints[0].X -= 1;
                    m_objPoints[0].Y -= 1;

                }
                else if (m_objCurrentRotation == ClockwiseRotations.NINETY)
                {
                    m_objPoints[3].X -= 0;
                    m_objPoints[3].Y -= 2;
                    m_objPoints[2].X += 1;
                    m_objPoints[2].Y -= 1;
                    m_objPoints[0].X -= 1;
                    m_objPoints[0].Y += 1;

                }
                else if (m_objCurrentRotation == ClockwiseRotations.TWOSEVENTY)
                {

                    m_objPoints[0].X += 1;
                    m_objPoints[0].Y -= 1;
                    m_objPoints[2].X -= 1;
                    m_objPoints[2].Y += 1;
                    m_objPoints[3].X -= 0;
                    m_objPoints[3].Y += 2;

                }
                break;
        }
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
};
