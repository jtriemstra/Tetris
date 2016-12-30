#include "shape_point.cpp"
#include "enums.h"
    
class Shape
{
    private:
      static const int POINTS_PER_SHAPE = 4;
      ShapeEnums::Types m_objType;
      ShapePoint m_objPoints;// = new Point[4]{ new Point(), new Point(), new Point(), new Point()};
      ShapeEnums::ClockwiseRotations m_objCurrentRotation;
            
    public:
      ShapePoint Points() const { return m_objPoints; } 
      ShapeEnums::Types Type() const { return m_objType; } 
      int InitialWidth() const {return 0;}

    Shape(ShapeEnums::Types objType)
    {
        m_objType = objType;
        //for (int i=0; i<POINTS_PER_SHAPE; i++) m_objPoints.Points[i] = new Point();
        
        switch (m_objType)
        {
            case ShapeEnums::I:
                m_objPoints.Points[0].X = 0;
                m_objPoints.Points[0].Y = 0;
                m_objPoints.Points[1].X = 0;
                m_objPoints.Points[1].Y = 1;
                m_objPoints.Points[2].X = 0;
                m_objPoints.Points[2].Y = 2;
                m_objPoints.Points[3].X = 0;
                m_objPoints.Points[3].Y = 3;
                break;
            case ShapeEnums::SQUARE:
                m_objPoints.Points[0].X = 0;
                m_objPoints.Points[0].Y = 0;
                m_objPoints.Points[1].X = 1;
                m_objPoints.Points[1].Y = 0;
                m_objPoints.Points[2].X = 0;
                m_objPoints.Points[2].Y = 1;
                m_objPoints.Points[3].X = 1;
                m_objPoints.Points[3].Y = 1;
                break;
            case ShapeEnums::T:
                m_objPoints.Points[0].X = 0;
                m_objPoints.Points[0].Y = 1;
                m_objPoints.Points[1].X = 1;
                m_objPoints.Points[1].Y = 0;
                m_objPoints.Points[2].X = 1;
                m_objPoints.Points[2].Y = 1;
                m_objPoints.Points[3].X = 2;
                m_objPoints.Points[3].Y = 1;
                break;
            case ShapeEnums::S:
                m_objPoints.Points[0].X = 0;
                m_objPoints.Points[0].Y = 1;
                m_objPoints.Points[1].X = 1;
                m_objPoints.Points[1].Y = 0;
                m_objPoints.Points[2].X = 1;
                m_objPoints.Points[2].Y = 1;
                m_objPoints.Points[3].X = 2;
                m_objPoints.Points[3].Y = 0;
                break;
            case ShapeEnums::Z:
                m_objPoints.Points[0].X = 0;
                m_objPoints.Points[0].Y = 0;
                m_objPoints.Points[1].X = 1;
                m_objPoints.Points[1].Y = 0;
                m_objPoints.Points[2].X = 1;
                m_objPoints.Points[2].Y = 1;
                m_objPoints.Points[3].X = 2;
                m_objPoints.Points[3].Y = 1;
                break;
            case ShapeEnums::J:
                m_objPoints.Points[0].X = 0;
                m_objPoints.Points[0].Y = 0;
                m_objPoints.Points[1].X = 0;
                m_objPoints.Points[1].Y = 1;
                m_objPoints.Points[2].X = 1;
                m_objPoints.Points[2].Y = 1;
                m_objPoints.Points[3].X = 2;
                m_objPoints.Points[3].Y = 1;
                break;
            case ShapeEnums::L:
                m_objPoints.Points[0].X = 0;
                m_objPoints.Points[0].Y = 1;
                m_objPoints.Points[1].X = 1;
                m_objPoints.Points[1].Y = 1;
                m_objPoints.Points[2].X = 2;
                m_objPoints.Points[2].Y = 1;
                m_objPoints.Points[3].X = 2;
                m_objPoints.Points[3].Y = 0;
                break;
        }
    }

    void Center()
    {
        for(int i=0; i<POINTS_PER_SHAPE; i++)
        {
            m_objPoints.Points[i].X += 3;
        }
    }

    int BottomRow () const
    {
        int intReturn = -1000;
        for(int i=0; i<POINTS_PER_SHAPE; i++)
        {
            if (m_objPoints.Points[i].Y > intReturn) intReturn = m_objPoints.Points[i].Y;
        }
        return intReturn;
    }

    void MoveDown(int intMaxRow)
    {
        bool blnLegal = true;
        for(int i=0; i<POINTS_PER_SHAPE; i++)
        {
            if (m_objPoints.Points[i].Y == intMaxRow) blnLegal = false;
        }
        if (blnLegal)
        {
            for(int i=0; i<POINTS_PER_SHAPE; i++)
            {
                m_objPoints.Points[i].Y += 1;
            }
        }
    }

    void MoveLeft(int intMinLeft)
    {
        bool blnLegal = true;
        for(int i=0; i<POINTS_PER_SHAPE; i++)
        {
            if (m_objPoints.Points[i].X == intMinLeft) blnLegal = false;
        }
        if (blnLegal)
        {
            for(int i=0; i<POINTS_PER_SHAPE; i++)
            {
                m_objPoints.Points[i].X -= 1;
            }
        }
    }

    void MoveRight(int intMaxRight)
    {
        bool blnLegal = true;
        for(int i=0; i<POINTS_PER_SHAPE; i++)
        {
            if (m_objPoints.Points[i].X == intMaxRight - 1) blnLegal = false;
        }
        if (blnLegal)
        {
            for(int i=0; i<POINTS_PER_SHAPE; i++)
            {
                m_objPoints.Points[i].X += 1;
            }
        }
    }

    void RotateClockwise(int intMinLeft, int intMaxRight)
    {
        Point objTestPoints[POINTS_PER_SHAPE];
        //for (int i=0; i<POINTS_PER_SHAPE; i++) objTestPoints[i] = new Point();
        
        switch (m_objType)
        {
            case ShapeEnums::SQUARE:
                break;
            case ShapeEnums::I:
                if (m_objCurrentRotation == ShapeEnums::INITIAL)
                {
                    m_objPoints.Points[0].X += 2;
                    m_objPoints.Points[0].Y += 2;
                    m_objPoints.Points[1].X += 1;
                    m_objPoints.Points[1].Y += 1;
                    m_objPoints.Points[3].X -= 1;
                    m_objPoints.Points[3].Y -= 1;                        
                }
                else if (m_objCurrentRotation == ShapeEnums::ONEEIGHTY)
                {
                    m_objPoints.Points[3].X += 2;
                    m_objPoints.Points[3].Y += 2;
                    m_objPoints.Points[2].X += 1;
                    m_objPoints.Points[2].Y += 1;
                    m_objPoints.Points[0].X -= 1;
                    m_objPoints.Points[0].Y -= 1;  
                }
                else if (m_objCurrentRotation == ShapeEnums::NINETY)
                {
                    m_objPoints.Points[0].X -= 1;
                    m_objPoints.Points[0].Y += 1;
                    m_objPoints.Points[2].X += 1;
                    m_objPoints.Points[2].Y -= 1;
                    m_objPoints.Points[3].X += 2;
                    m_objPoints.Points[3].Y -= 2;  
                }
                else if (m_objCurrentRotation == ShapeEnums::TWOSEVENTY)
                {
                    m_objPoints.Points[0].X += 2;
                    m_objPoints.Points[0].Y -= 2;
                    m_objPoints.Points[1].X += 1;
                    m_objPoints.Points[1].Y -= 1;
                    m_objPoints.Points[3].X -= 1;
                    m_objPoints.Points[3].Y += 1;  
                }
                break;
            case ShapeEnums::T:
                if (m_objCurrentRotation == ShapeEnums::INITIAL)
                {
                    m_objPoints.Points[0].X += 1;
                    m_objPoints.Points[0].Y -= 1;
                    m_objPoints.Points[1].X += 1;
                    m_objPoints.Points[1].Y += 1;
                    m_objPoints.Points[3].X -= 1;
                    m_objPoints.Points[3].Y += 1;                        
                }
                else if (m_objCurrentRotation == ShapeEnums::ONEEIGHTY)
                {
                    m_objPoints.Points[3].X += 1;
                    m_objPoints.Points[3].Y -= 1;
                    m_objPoints.Points[1].X -= 1;
                    m_objPoints.Points[1].Y -= 1;
                    m_objPoints.Points[0].X -= 1;
                    m_objPoints.Points[0].Y += 1;  
                }
                else if (m_objCurrentRotation == ShapeEnums::NINETY)
                {
                    m_objPoints.Points[0].X += 1;
                    m_objPoints.Points[0].Y += 1;
                    m_objPoints.Points[1].X -= 1;
                    m_objPoints.Points[1].Y += 1;
                    m_objPoints.Points[3].X -= 1;
                    m_objPoints.Points[3].Y -= 1;  
                }
                else if (m_objCurrentRotation == ShapeEnums::TWOSEVENTY)
                {
                    m_objPoints.Points[0].X -= 1;
                    m_objPoints.Points[0].Y -= 1;
                    m_objPoints.Points[1].X += 1;
                    m_objPoints.Points[1].Y -= 1;
                    m_objPoints.Points[3].X += 1;
                    m_objPoints.Points[3].Y += 1;  
                }
                break;
            case ShapeEnums::S:
                if (m_objCurrentRotation == ShapeEnums::INITIAL)
                {
                    m_objPoints.Points[0].X += 1;
                    m_objPoints.Points[0].Y -= 1;
                    m_objPoints.Points[1].X += 1;
                    m_objPoints.Points[1].Y += 1;
                    m_objPoints.Points[3].X -= 0;
                    m_objPoints.Points[3].Y += 2;                        
                }
                else if (m_objCurrentRotation == ShapeEnums::ONEEIGHTY)
                {
                    m_objPoints.Points[3].X += 1;
                    m_objPoints.Points[3].Y -= 1;
                    m_objPoints.Points[2].X += 1;
                    m_objPoints.Points[2].Y += 1;
                    m_objPoints.Points[0].X -= 0;
                    m_objPoints.Points[0].Y += 2;  
                }
                else if (m_objCurrentRotation == ShapeEnums::NINETY)
                {
                    m_objPoints.Points[0].X += 1;
                    m_objPoints.Points[0].Y += 1;
                    m_objPoints.Points[1].X -= 1;
                    m_objPoints.Points[1].Y += 1;
                    m_objPoints.Points[3].X -= 2;
                    m_objPoints.Points[3].Y -= 0;  
                }
                else if (m_objCurrentRotation == ShapeEnums::TWOSEVENTY)
                {
                    m_objPoints.Points[3].X += 1;
                    m_objPoints.Points[3].Y += 1;
                    m_objPoints.Points[2].X -= 1;
                    m_objPoints.Points[2].Y += 1;
                    m_objPoints.Points[0].X -= 2;
                    m_objPoints.Points[0].Y -= 0;  
                }
                break;
            case ShapeEnums::Z:
                if (m_objCurrentRotation == ShapeEnums::INITIAL)
                {
                    m_objPoints.Points[0].X += 2;
                    m_objPoints.Points[0].Y -= 0;
                    m_objPoints.Points[1].X += 1;
                    m_objPoints.Points[1].Y += 1;
                    m_objPoints.Points[3].X -= 1;
                    m_objPoints.Points[3].Y += 1;                        
                }
                else if (m_objCurrentRotation == ShapeEnums::ONEEIGHTY)
                {
                    m_objPoints.Points[3].X += 2;
                    m_objPoints.Points[3].Y -= 0;
                    m_objPoints.Points[2].X += 1;
                    m_objPoints.Points[2].Y += 1;
                    m_objPoints.Points[0].X -= 1;
                    m_objPoints.Points[0].Y += 1;  
                }
                else if (m_objCurrentRotation == ShapeEnums::NINETY)
                {
                    m_objPoints.Points[0].X += 0;
                    m_objPoints.Points[0].Y += 2;
                    m_objPoints.Points[1].X -= 1;
                    m_objPoints.Points[1].Y += 1;
                    m_objPoints.Points[3].X -= 1;
                    m_objPoints.Points[3].Y -= 1;  
                }
                else if (m_objCurrentRotation == ShapeEnums::TWOSEVENTY)
                {
                    m_objPoints.Points[3].X += 0;
                    m_objPoints.Points[3].Y += 2;
                    m_objPoints.Points[2].X -= 1;
                    m_objPoints.Points[2].Y += 1;
                    m_objPoints.Points[0].X -= 1;
                    m_objPoints.Points[0].Y -= 1;  
                }
                break;
            case ShapeEnums::J:
                if (m_objCurrentRotation == ShapeEnums::INITIAL)
                {
                    m_objPoints.Points[0].X += 2;
                    m_objPoints.Points[0].Y += 0;
                    m_objPoints.Points[1].X += 1;
                    m_objPoints.Points[1].Y -= 1;
                    m_objPoints.Points[3].X -= 1;
                    m_objPoints.Points[3].Y += 1;
                }
                else if (m_objCurrentRotation == ShapeEnums::ONEEIGHTY)
                {
                    m_objPoints.Points[3].X += 1;
                    m_objPoints.Points[3].Y -= 1;
                    m_objPoints.Points[1].X -= 1; 
                    m_objPoints.Points[1].Y += 1;
                    m_objPoints.Points[0].X -= 2;
                    m_objPoints.Points[0].Y += 0;
                }
                else if (m_objCurrentRotation == ShapeEnums::NINETY)
                {
                    m_objPoints.Points[0].X -= 0;
                    m_objPoints.Points[0].Y += 2;
                    m_objPoints.Points[1].X += 1;
                    m_objPoints.Points[1].Y += 1;
                    m_objPoints.Points[3].X -= 1; 
                    m_objPoints.Points[3].Y -= 1;
                }
                else if (m_objCurrentRotation == ShapeEnums::TWOSEVENTY)
                {
                    m_objPoints.Points[3].X += 1;
                    m_objPoints.Points[3].Y += 1;
                    m_objPoints.Points[1].X -= 1;
                    m_objPoints.Points[1].Y -= 1;
                    m_objPoints.Points[0].X += 0;
                    m_objPoints.Points[0].Y -= 2;
                }
                break;
            case ShapeEnums::L:
                if (m_objCurrentRotation == ShapeEnums::INITIAL)
                {
                    m_objPoints.Points[3].X += 0;
                    m_objPoints.Points[3].Y += 2;
                    m_objPoints.Points[2].X -= 1;
                    m_objPoints.Points[2].Y += 1;
                    m_objPoints.Points[0].X += 1;
                    m_objPoints.Points[0].Y -= 1;
                }
                else if (m_objCurrentRotation == ShapeEnums::ONEEIGHTY)
                {
                    m_objPoints.Points[0].X -= 1;
                    m_objPoints.Points[0].Y += 1;
                    m_objPoints.Points[2].X += 1; 
                    m_objPoints.Points[2].Y -= 1;
                    m_objPoints.Points[3].X += 0;
                    m_objPoints.Points[3].Y -= 2;
                }
                else if (m_objCurrentRotation == ShapeEnums::NINETY)
                {
                    m_objPoints.Points[3].X -= 2;
                    m_objPoints.Points[3].Y -= 0;
                    m_objPoints.Points[2].X -= 1;
                    m_objPoints.Points[2].Y -= 1;
                    m_objPoints.Points[0].X += 1; 
                    m_objPoints.Points[0].Y += 1;
                }
                else if (m_objCurrentRotation == ShapeEnums::TWOSEVENTY)
                {
                    m_objPoints.Points[0].X -= 1;
                    m_objPoints.Points[0].Y -= 1;
                    m_objPoints.Points[2].X += 1;
                    m_objPoints.Points[2].Y += 1;
                    m_objPoints.Points[3].X += 2;
                    m_objPoints.Points[3].Y -= 0;
                }
                break;
        }

        switch (m_objCurrentRotation){
            case ShapeEnums::INITIAL:
                m_objCurrentRotation = ShapeEnums::NINETY;
                break;
            case ShapeEnums::NINETY:
                m_objCurrentRotation = ShapeEnums::ONEEIGHTY;
                break;
            case ShapeEnums::ONEEIGHTY:
                m_objCurrentRotation = ShapeEnums::TWOSEVENTY;
                break;
            case ShapeEnums::TWOSEVENTY:
                m_objCurrentRotation = ShapeEnums::INITIAL;
                break;
        }
    }

    void RotateCounterclockwise()
    {
        switch (m_objType)
        {
            case ShapeEnums::SQUARE:
                break;
            case ShapeEnums::I:
                if (m_objCurrentRotation == ShapeEnums::INITIAL)
                {
                    m_objPoints.Points[0].X -= 2;
                    m_objPoints.Points[0].Y += 2;
                    m_objPoints.Points[1].X -= 1;
                    m_objPoints.Points[1].Y += 1;
                    m_objPoints.Points[3].X += 1;
                    m_objPoints.Points[3].Y -= 1;   
                }
                else if (m_objCurrentRotation == ShapeEnums::ONEEIGHTY)
                {
                    m_objPoints.Points[0].X += 1;
                    m_objPoints.Points[0].Y -= 1;
                    m_objPoints.Points[2].X -= 1;
                    m_objPoints.Points[2].Y += 1;
                    m_objPoints.Points[3].X -= 2;
                    m_objPoints.Points[3].Y += 2;                          
                }
                else if (m_objCurrentRotation == ShapeEnums::NINETY)
                {

                    m_objPoints.Points[0].X -= 2;
                    m_objPoints.Points[0].Y -= 2;
                    m_objPoints.Points[1].X -= 1;
                    m_objPoints.Points[1].Y -= 1;
                    m_objPoints.Points[3].X += 1;
                    m_objPoints.Points[3].Y += 1;   
                }
                else if (m_objCurrentRotation == ShapeEnums::TWOSEVENTY)
                {
                    m_objPoints.Points[3].X -= 2;
                    m_objPoints.Points[3].Y -= 2;
                    m_objPoints.Points[2].X -= 1;
                    m_objPoints.Points[2].Y -= 1;
                    m_objPoints.Points[0].X += 1;
                    m_objPoints.Points[0].Y += 1;  
                }
                break;
            case ShapeEnums::T:
                if (m_objCurrentRotation == ShapeEnums::INITIAL)
                {
                    m_objPoints.Points[0].X += 1;
                    m_objPoints.Points[0].Y += 1;
                    m_objPoints.Points[1].X -= 1;
                    m_objPoints.Points[1].Y += 1;
                    m_objPoints.Points[3].X -= 1;
                    m_objPoints.Points[3].Y -= 1;  
                                           
                }
                else if (m_objCurrentRotation == ShapeEnums::ONEEIGHTY)
                {
                    m_objPoints.Points[0].X -= 1;
                    m_objPoints.Points[0].Y -= 1;
                    m_objPoints.Points[1].X += 1;
                    m_objPoints.Points[1].Y -= 1;
                    m_objPoints.Points[3].X += 1;
                    m_objPoints.Points[3].Y += 1;  

                }
                else if (m_objCurrentRotation == ShapeEnums::NINETY)
                {
                    m_objPoints.Points[0].X -= 1;
                    m_objPoints.Points[0].Y += 1;
                    m_objPoints.Points[1].X -= 1;
                    m_objPoints.Points[1].Y -= 1;
                    m_objPoints.Points[3].X += 1;
                    m_objPoints.Points[3].Y -= 1; 

                    
                }
                else if (m_objCurrentRotation == ShapeEnums::TWOSEVENTY)
                {
                    m_objPoints.Points[3].X -= 1;
                    m_objPoints.Points[3].Y += 1;
                    m_objPoints.Points[1].X += 1;
                    m_objPoints.Points[1].Y += 1;
                    m_objPoints.Points[0].X += 1;
                    m_objPoints.Points[0].Y -= 1;  

                }
                break;
            case ShapeEnums::S:
                if (m_objCurrentRotation == ShapeEnums::INITIAL)
                {
                    m_objPoints.Points[3].X -= 1;
                    m_objPoints.Points[3].Y -= 1;
                    m_objPoints.Points[2].X += 1;
                    m_objPoints.Points[2].Y -= 1;
                    m_objPoints.Points[0].X += 2;
                    m_objPoints.Points[0].Y += 0;
                                     
                }
                else if (m_objCurrentRotation == ShapeEnums::ONEEIGHTY)
                {
                    m_objPoints.Points[0].X -= 1;
                    m_objPoints.Points[0].Y -= 1;
                    m_objPoints.Points[1].X += 1;
                    m_objPoints.Points[1].Y -= 1;
                    m_objPoints.Points[3].X += 2;
                    m_objPoints.Points[3].Y += 0;  
                }
                else if (m_objCurrentRotation == ShapeEnums::NINETY)
                {
                    m_objPoints.Points[0].X -= 1;
                    m_objPoints.Points[0].Y += 1;
                    m_objPoints.Points[1].X -= 1;
                    m_objPoints.Points[1].Y -= 1;
                    m_objPoints.Points[3].X += 0;
                    m_objPoints.Points[3].Y -= 2;      
                }
                else if (m_objCurrentRotation == ShapeEnums::TWOSEVENTY)
                {
                    m_objPoints.Points[3].X -= 1;
                    m_objPoints.Points[3].Y += 1;
                    m_objPoints.Points[2].X -= 1;
                    m_objPoints.Points[2].Y -= 1;
                    m_objPoints.Points[0].X += 0;
                    m_objPoints.Points[0].Y -= 2;  
                }
                break;
            case ShapeEnums::Z:
                if (m_objCurrentRotation == ShapeEnums::INITIAL)
                {
                    m_objPoints.Points[3].X -= 0;
                    m_objPoints.Points[3].Y -= 2;
                    m_objPoints.Points[2].X += 1;
                    m_objPoints.Points[2].Y -= 1;
                    m_objPoints.Points[0].X += 1;
                    m_objPoints.Points[0].Y += 1;  
                    
                }
                else if (m_objCurrentRotation == ShapeEnums::ONEEIGHTY)
                {
                    m_objPoints.Points[0].X -= 0;
                    m_objPoints.Points[0].Y -= 2;
                    m_objPoints.Points[1].X += 1;
                    m_objPoints.Points[1].Y -= 1;
                    m_objPoints.Points[3].X += 1;
                    m_objPoints.Points[3].Y += 1;  
                }
                else if (m_objCurrentRotation == ShapeEnums::NINETY)
                {
                    m_objPoints.Points[0].X -= 2;
                    m_objPoints.Points[0].Y += 0;
                    m_objPoints.Points[1].X -= 1;
                    m_objPoints.Points[1].Y -= 1;
                    m_objPoints.Points[3].X += 1;
                    m_objPoints.Points[3].Y -= 1;                        
                }
                else if (m_objCurrentRotation == ShapeEnums::TWOSEVENTY)
                {
                    m_objPoints.Points[3].X -= 2;
                    m_objPoints.Points[3].Y += 0;
                    m_objPoints.Points[2].X -= 1;
                    m_objPoints.Points[2].Y -= 1;
                    m_objPoints.Points[0].X += 1;
                    m_objPoints.Points[0].Y -= 1;  
                }
                break;
            case ShapeEnums::J:
                if (m_objCurrentRotation == ShapeEnums::INITIAL)
                {
                    m_objPoints.Points[3].X -= 1;
                    m_objPoints.Points[3].Y -= 1;
                    m_objPoints.Points[1].X += 1;
                    m_objPoints.Points[1].Y += 1;
                    m_objPoints.Points[0].X -= 0;
                    m_objPoints.Points[0].Y += 2;
                    
                }
                else if (m_objCurrentRotation == ShapeEnums::ONEEIGHTY)
                {
                    m_objPoints.Points[0].X += 0;
                    m_objPoints.Points[0].Y -= 2;
                    m_objPoints.Points[1].X -= 1;
                    m_objPoints.Points[1].Y -= 1;
                    m_objPoints.Points[3].X += 1;
                    m_objPoints.Points[3].Y += 1;

                }
                else if (m_objCurrentRotation == ShapeEnums::NINETY)
                {
                    m_objPoints.Points[0].X -= 2;
                    m_objPoints.Points[0].Y -= 0;
                    m_objPoints.Points[1].X -= 1;
                    m_objPoints.Points[1].Y += 1;
                    m_objPoints.Points[3].X += 1;
                    m_objPoints.Points[3].Y -= 1;
                    
                }
                else if (m_objCurrentRotation == ShapeEnums::TWOSEVENTY)
                {

                    m_objPoints.Points[3].X -= 1;
                    m_objPoints.Points[3].Y += 1;
                    m_objPoints.Points[1].X += 1;
                    m_objPoints.Points[1].Y -= 1;
                    m_objPoints.Points[0].X += 2;
                    m_objPoints.Points[0].Y -= 0;

                    
                }
                break;
            case ShapeEnums::L:
                if (m_objCurrentRotation == ShapeEnums::INITIAL)
                {
                    m_objPoints.Points[0].X += 1;
                    m_objPoints.Points[0].Y += 1;
                    m_objPoints.Points[2].X -= 1;
                    m_objPoints.Points[2].Y -= 1;
                    m_objPoints.Points[3].X -= 2;
                    m_objPoints.Points[3].Y += 0;
                }
                else if (m_objCurrentRotation == ShapeEnums::ONEEIGHTY)
                {
                    m_objPoints.Points[3].X += 2;
                    m_objPoints.Points[3].Y += 0;
                    m_objPoints.Points[2].X += 1;
                    m_objPoints.Points[2].Y += 1;
                    m_objPoints.Points[0].X -= 1;
                    m_objPoints.Points[0].Y -= 1;

                }
                else if (m_objCurrentRotation == ShapeEnums::NINETY)
                {
                    m_objPoints.Points[3].X -= 0;
                    m_objPoints.Points[3].Y -= 2;
                    m_objPoints.Points[2].X += 1;
                    m_objPoints.Points[2].Y -= 1;
                    m_objPoints.Points[0].X -= 1;
                    m_objPoints.Points[0].Y += 1;

                }
                else if (m_objCurrentRotation == ShapeEnums::TWOSEVENTY)
                {

                    m_objPoints.Points[0].X += 1;
                    m_objPoints.Points[0].Y -= 1;
                    m_objPoints.Points[2].X -= 1;
                    m_objPoints.Points[2].Y += 1;
                    m_objPoints.Points[3].X -= 0;
                    m_objPoints.Points[3].Y += 2;

                }
                break;
        }
        switch (m_objCurrentRotation)
        {
            case ShapeEnums::INITIAL:
                m_objCurrentRotation = ShapeEnums::TWOSEVENTY;
                break;
            case ShapeEnums::NINETY:
                m_objCurrentRotation = ShapeEnums::INITIAL;
                break;
            case ShapeEnums::ONEEIGHTY:
                m_objCurrentRotation = ShapeEnums::NINETY;
                break;
            case ShapeEnums::TWOSEVENTY:
                m_objCurrentRotation = ShapeEnums::ONEEIGHTY;
                break;
        }
    }
};

