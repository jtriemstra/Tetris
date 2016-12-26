#include "point.cpp"

namespace Shape{
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
  };

   enum ClockwiseRotations
    {
        INITIAL,
        NINETY,
        ONEEIGHTY,
        TWOSEVENTY
    };
    
  class Shape
  {
      private:
        static const int POINTS_PER_SHAPE = 4;
        Types m_objType;
        Point m_objPoints[POINTS_PER_SHAPE];// = new Point[4]{ new Point(), new Point(), new Point(), new Point()};
        ClockwiseRotations m_objCurrentRotation;
              
      public:
        Point* Points() { return m_objPoints; } 
        Types Type() { return m_objType; } 
        int InitialWidth() {return 0;}
  
      Shape(Types objType)
      {
          m_objType = objType;
          //for (int i=0; i<POINTS_PER_SHAPE; i++) m_objPoints[i] = new Point();
          
          switch (m_objType)
          {
              case I:
                  m_objPoints[0].X = 0;
                  m_objPoints[0].Y = 0;
                  m_objPoints[1].X = 0;
                  m_objPoints[1].Y = 1;
                  m_objPoints[2].X = 0;
                  m_objPoints[2].Y = 2;
                  m_objPoints[3].X = 0;
                  m_objPoints[3].Y = 3;
                  break;
              case SQUARE:
                  m_objPoints[0].X = 0;
                  m_objPoints[0].Y = 0;
                  m_objPoints[1].X = 1;
                  m_objPoints[1].Y = 0;
                  m_objPoints[2].X = 0;
                  m_objPoints[2].Y = 1;
                  m_objPoints[3].X = 1;
                  m_objPoints[3].Y = 1;
                  break;
              case T:
                  m_objPoints[0].X = 0;
                  m_objPoints[0].Y = 1;
                  m_objPoints[1].X = 1;
                  m_objPoints[1].Y = 0;
                  m_objPoints[2].X = 1;
                  m_objPoints[2].Y = 1;
                  m_objPoints[3].X = 2;
                  m_objPoints[3].Y = 1;
                  break;
              case S:
                  m_objPoints[0].X = 0;
                  m_objPoints[0].Y = 1;
                  m_objPoints[1].X = 1;
                  m_objPoints[1].Y = 0;
                  m_objPoints[2].X = 1;
                  m_objPoints[2].Y = 1;
                  m_objPoints[3].X = 2;
                  m_objPoints[3].Y = 0;
                  break;
              case Z:
                  m_objPoints[0].X = 0;
                  m_objPoints[0].Y = 0;
                  m_objPoints[1].X = 1;
                  m_objPoints[1].Y = 0;
                  m_objPoints[2].X = 1;
                  m_objPoints[2].Y = 1;
                  m_objPoints[3].X = 2;
                  m_objPoints[3].Y = 1;
                  break;
              case J:
                  m_objPoints[0].X = 0;
                  m_objPoints[0].Y = 0;
                  m_objPoints[1].X = 0;
                  m_objPoints[1].Y = 1;
                  m_objPoints[2].X = 1;
                  m_objPoints[2].Y = 1;
                  m_objPoints[3].X = 2;
                  m_objPoints[3].Y = 1;
                  break;
              case L:
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
          for(int i=0; i<POINTS_PER_SHAPE; i++)
          {
              m_objPoints[i].X += 3;
          }
      }
  
      int BottomRow()
      {
          int intReturn = -1000;
          for(int i=0; i<POINTS_PER_SHAPE; i++)
          {
              if (m_objPoints[i].Y > intReturn) intReturn = m_objPoints[i].Y;
          }
          return intReturn;
      }
  
      void MoveDown(int intMaxRow)
      {
          bool blnLegal = true;
          for(int i=0; i<POINTS_PER_SHAPE; i++)
          {
              if (m_objPoints[i].Y == intMaxRow) blnLegal = false;
          }
          if (blnLegal)
          {
              for(int i=0; i<POINTS_PER_SHAPE; i++)
              {
                  m_objPoints[i].Y += 1;
              }
          }
      }
  
      void MoveLeft(int intMinLeft)
      {
          bool blnLegal = true;
          for(int i=0; i<POINTS_PER_SHAPE; i++)
          {
              if (m_objPoints[i].X == intMinLeft) blnLegal = false;
          }
          if (blnLegal)
          {
              for(int i=0; i<POINTS_PER_SHAPE; i++)
              {
                  m_objPoints[i].X -= 1;
              }
          }
      }
  
      void MoveRight(int intMaxRight)
      {
          bool blnLegal = true;
          for(int i=0; i<POINTS_PER_SHAPE; i++)
          {
              if (m_objPoints[i].X == intMaxRight - 1) blnLegal = false;
          }
          if (blnLegal)
          {
              for(int i=0; i<POINTS_PER_SHAPE; i++)
              {
                  m_objPoints[i].X += 1;
              }
          }
      }
  
      void RotateClockwise(int intMinLeft, int intMaxRight)
      {
          Point objTestPoints[POINTS_PER_SHAPE];
          //for (int i=0; i<POINTS_PER_SHAPE; i++) objTestPoints[i] = new Point();
          
          switch (m_objType)
          {
              case SQUARE:
                  break;
              case I:
                  if (m_objCurrentRotation == INITIAL)
                  {
                      m_objPoints[0].X += 2;
                      m_objPoints[0].Y += 2;
                      m_objPoints[1].X += 1;
                      m_objPoints[1].Y += 1;
                      m_objPoints[3].X -= 1;
                      m_objPoints[3].Y -= 1;                        
                  }
                  else if (m_objCurrentRotation == ONEEIGHTY)
                  {
                      m_objPoints[3].X += 2;
                      m_objPoints[3].Y += 2;
                      m_objPoints[2].X += 1;
                      m_objPoints[2].Y += 1;
                      m_objPoints[0].X -= 1;
                      m_objPoints[0].Y -= 1;  
                  }
                  else if (m_objCurrentRotation == NINETY)
                  {
                      m_objPoints[0].X -= 1;
                      m_objPoints[0].Y += 1;
                      m_objPoints[2].X += 1;
                      m_objPoints[2].Y -= 1;
                      m_objPoints[3].X += 2;
                      m_objPoints[3].Y -= 2;  
                  }
                  else if (m_objCurrentRotation == TWOSEVENTY)
                  {
                      m_objPoints[0].X += 2;
                      m_objPoints[0].Y -= 2;
                      m_objPoints[1].X += 1;
                      m_objPoints[1].Y -= 1;
                      m_objPoints[3].X -= 1;
                      m_objPoints[3].Y += 1;  
                  }
                  break;
              case T:
                  if (m_objCurrentRotation == INITIAL)
                  {
                      m_objPoints[0].X += 1;
                      m_objPoints[0].Y -= 1;
                      m_objPoints[1].X += 1;
                      m_objPoints[1].Y += 1;
                      m_objPoints[3].X -= 1;
                      m_objPoints[3].Y += 1;                        
                  }
                  else if (m_objCurrentRotation == ONEEIGHTY)
                  {
                      m_objPoints[3].X += 1;
                      m_objPoints[3].Y -= 1;
                      m_objPoints[1].X -= 1;
                      m_objPoints[1].Y -= 1;
                      m_objPoints[0].X -= 1;
                      m_objPoints[0].Y += 1;  
                  }
                  else if (m_objCurrentRotation == NINETY)
                  {
                      m_objPoints[0].X += 1;
                      m_objPoints[0].Y += 1;
                      m_objPoints[1].X -= 1;
                      m_objPoints[1].Y += 1;
                      m_objPoints[3].X -= 1;
                      m_objPoints[3].Y -= 1;  
                  }
                  else if (m_objCurrentRotation == TWOSEVENTY)
                  {
                      m_objPoints[0].X -= 1;
                      m_objPoints[0].Y -= 1;
                      m_objPoints[1].X += 1;
                      m_objPoints[1].Y -= 1;
                      m_objPoints[3].X += 1;
                      m_objPoints[3].Y += 1;  
                  }
                  break;
              case S:
                  if (m_objCurrentRotation == INITIAL)
                  {
                      m_objPoints[0].X += 1;
                      m_objPoints[0].Y -= 1;
                      m_objPoints[1].X += 1;
                      m_objPoints[1].Y += 1;
                      m_objPoints[3].X -= 0;
                      m_objPoints[3].Y += 2;                        
                  }
                  else if (m_objCurrentRotation == ONEEIGHTY)
                  {
                      m_objPoints[3].X += 1;
                      m_objPoints[3].Y -= 1;
                      m_objPoints[2].X += 1;
                      m_objPoints[2].Y += 1;
                      m_objPoints[0].X -= 0;
                      m_objPoints[0].Y += 2;  
                  }
                  else if (m_objCurrentRotation == NINETY)
                  {
                      m_objPoints[0].X += 1;
                      m_objPoints[0].Y += 1;
                      m_objPoints[1].X -= 1;
                      m_objPoints[1].Y += 1;
                      m_objPoints[3].X -= 2;
                      m_objPoints[3].Y -= 0;  
                  }
                  else if (m_objCurrentRotation == TWOSEVENTY)
                  {
                      m_objPoints[3].X += 1;
                      m_objPoints[3].Y += 1;
                      m_objPoints[2].X -= 1;
                      m_objPoints[2].Y += 1;
                      m_objPoints[0].X -= 2;
                      m_objPoints[0].Y -= 0;  
                  }
                  break;
              case Z:
                  if (m_objCurrentRotation == INITIAL)
                  {
                      m_objPoints[0].X += 2;
                      m_objPoints[0].Y -= 0;
                      m_objPoints[1].X += 1;
                      m_objPoints[1].Y += 1;
                      m_objPoints[3].X -= 1;
                      m_objPoints[3].Y += 1;                        
                  }
                  else if (m_objCurrentRotation == ONEEIGHTY)
                  {
                      m_objPoints[3].X += 2;
                      m_objPoints[3].Y -= 0;
                      m_objPoints[2].X += 1;
                      m_objPoints[2].Y += 1;
                      m_objPoints[0].X -= 1;
                      m_objPoints[0].Y += 1;  
                  }
                  else if (m_objCurrentRotation == NINETY)
                  {
                      m_objPoints[0].X += 0;
                      m_objPoints[0].Y += 2;
                      m_objPoints[1].X -= 1;
                      m_objPoints[1].Y += 1;
                      m_objPoints[3].X -= 1;
                      m_objPoints[3].Y -= 1;  
                  }
                  else if (m_objCurrentRotation == TWOSEVENTY)
                  {
                      m_objPoints[3].X += 0;
                      m_objPoints[3].Y += 2;
                      m_objPoints[2].X -= 1;
                      m_objPoints[2].Y += 1;
                      m_objPoints[0].X -= 1;
                      m_objPoints[0].Y -= 1;  
                  }
                  break;
              case J:
                  if (m_objCurrentRotation == INITIAL)
                  {
                      m_objPoints[0].X += 2;
                      m_objPoints[0].Y += 0;
                      m_objPoints[1].X += 1;
                      m_objPoints[1].Y -= 1;
                      m_objPoints[3].X -= 1;
                      m_objPoints[3].Y += 1;
                  }
                  else if (m_objCurrentRotation == ONEEIGHTY)
                  {
                      m_objPoints[3].X += 1;
                      m_objPoints[3].Y -= 1;
                      m_objPoints[1].X -= 1; 
                      m_objPoints[1].Y += 1;
                      m_objPoints[0].X -= 2;
                      m_objPoints[0].Y += 0;
                  }
                  else if (m_objCurrentRotation == NINETY)
                  {
                      m_objPoints[0].X -= 0;
                      m_objPoints[0].Y += 2;
                      m_objPoints[1].X += 1;
                      m_objPoints[1].Y += 1;
                      m_objPoints[3].X -= 1; 
                      m_objPoints[3].Y -= 1;
                  }
                  else if (m_objCurrentRotation == TWOSEVENTY)
                  {
                      m_objPoints[3].X += 1;
                      m_objPoints[3].Y += 1;
                      m_objPoints[1].X -= 1;
                      m_objPoints[1].Y -= 1;
                      m_objPoints[0].X += 0;
                      m_objPoints[0].Y -= 2;
                  }
                  break;
              case L:
                  if (m_objCurrentRotation == INITIAL)
                  {
                      m_objPoints[3].X += 0;
                      m_objPoints[3].Y += 2;
                      m_objPoints[2].X -= 1;
                      m_objPoints[2].Y += 1;
                      m_objPoints[0].X += 1;
                      m_objPoints[0].Y -= 1;
                  }
                  else if (m_objCurrentRotation == ONEEIGHTY)
                  {
                      m_objPoints[0].X -= 1;
                      m_objPoints[0].Y += 1;
                      m_objPoints[2].X += 1; 
                      m_objPoints[2].Y -= 1;
                      m_objPoints[3].X += 0;
                      m_objPoints[3].Y -= 2;
                  }
                  else if (m_objCurrentRotation == NINETY)
                  {
                      m_objPoints[3].X -= 2;
                      m_objPoints[3].Y -= 0;
                      m_objPoints[2].X -= 1;
                      m_objPoints[2].Y -= 1;
                      m_objPoints[0].X += 1; 
                      m_objPoints[0].Y += 1;
                  }
                  else if (m_objCurrentRotation == TWOSEVENTY)
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
              case INITIAL:
                  m_objCurrentRotation = NINETY;
                  break;
              case NINETY:
                  m_objCurrentRotation = ONEEIGHTY;
                  break;
              case ONEEIGHTY:
                  m_objCurrentRotation = TWOSEVENTY;
                  break;
              case TWOSEVENTY:
                  m_objCurrentRotation = INITIAL;
                  break;
          }
      }
  
      void RotateCounterclockwise()
      {
          switch (m_objType)
          {
              case SQUARE:
                  break;
              case I:
                  if (m_objCurrentRotation == INITIAL)
                  {
                      m_objPoints[0].X -= 2;
                      m_objPoints[0].Y += 2;
                      m_objPoints[1].X -= 1;
                      m_objPoints[1].Y += 1;
                      m_objPoints[3].X += 1;
                      m_objPoints[3].Y -= 1;   
                  }
                  else if (m_objCurrentRotation == ONEEIGHTY)
                  {
                      m_objPoints[0].X += 1;
                      m_objPoints[0].Y -= 1;
                      m_objPoints[2].X -= 1;
                      m_objPoints[2].Y += 1;
                      m_objPoints[3].X -= 2;
                      m_objPoints[3].Y += 2;                          
                  }
                  else if (m_objCurrentRotation == NINETY)
                  {
  
                      m_objPoints[0].X -= 2;
                      m_objPoints[0].Y -= 2;
                      m_objPoints[1].X -= 1;
                      m_objPoints[1].Y -= 1;
                      m_objPoints[3].X += 1;
                      m_objPoints[3].Y += 1;   
                  }
                  else if (m_objCurrentRotation == TWOSEVENTY)
                  {
                      m_objPoints[3].X -= 2;
                      m_objPoints[3].Y -= 2;
                      m_objPoints[2].X -= 1;
                      m_objPoints[2].Y -= 1;
                      m_objPoints[0].X += 1;
                      m_objPoints[0].Y += 1;  
                  }
                  break;
              case T:
                  if (m_objCurrentRotation == INITIAL)
                  {
                      m_objPoints[0].X += 1;
                      m_objPoints[0].Y += 1;
                      m_objPoints[1].X -= 1;
                      m_objPoints[1].Y += 1;
                      m_objPoints[3].X -= 1;
                      m_objPoints[3].Y -= 1;  
                                             
                  }
                  else if (m_objCurrentRotation == ONEEIGHTY)
                  {
                      m_objPoints[0].X -= 1;
                      m_objPoints[0].Y -= 1;
                      m_objPoints[1].X += 1;
                      m_objPoints[1].Y -= 1;
                      m_objPoints[3].X += 1;
                      m_objPoints[3].Y += 1;  
  
                  }
                  else if (m_objCurrentRotation == NINETY)
                  {
                      m_objPoints[0].X -= 1;
                      m_objPoints[0].Y += 1;
                      m_objPoints[1].X -= 1;
                      m_objPoints[1].Y -= 1;
                      m_objPoints[3].X += 1;
                      m_objPoints[3].Y -= 1; 
  
                      
                  }
                  else if (m_objCurrentRotation == TWOSEVENTY)
                  {
                      m_objPoints[3].X -= 1;
                      m_objPoints[3].Y += 1;
                      m_objPoints[1].X += 1;
                      m_objPoints[1].Y += 1;
                      m_objPoints[0].X += 1;
                      m_objPoints[0].Y -= 1;  
  
                  }
                  break;
              case S:
                  if (m_objCurrentRotation == INITIAL)
                  {
                      m_objPoints[3].X -= 1;
                      m_objPoints[3].Y -= 1;
                      m_objPoints[2].X += 1;
                      m_objPoints[2].Y -= 1;
                      m_objPoints[0].X += 2;
                      m_objPoints[0].Y += 0;
                                       
                  }
                  else if (m_objCurrentRotation == ONEEIGHTY)
                  {
                      m_objPoints[0].X -= 1;
                      m_objPoints[0].Y -= 1;
                      m_objPoints[1].X += 1;
                      m_objPoints[1].Y -= 1;
                      m_objPoints[3].X += 2;
                      m_objPoints[3].Y += 0;  
                  }
                  else if (m_objCurrentRotation == NINETY)
                  {
                      m_objPoints[0].X -= 1;
                      m_objPoints[0].Y += 1;
                      m_objPoints[1].X -= 1;
                      m_objPoints[1].Y -= 1;
                      m_objPoints[3].X += 0;
                      m_objPoints[3].Y -= 2;      
                  }
                  else if (m_objCurrentRotation == TWOSEVENTY)
                  {
                      m_objPoints[3].X -= 1;
                      m_objPoints[3].Y += 1;
                      m_objPoints[2].X -= 1;
                      m_objPoints[2].Y -= 1;
                      m_objPoints[0].X += 0;
                      m_objPoints[0].Y -= 2;  
                  }
                  break;
              case Z:
                  if (m_objCurrentRotation == INITIAL)
                  {
                      m_objPoints[3].X -= 0;
                      m_objPoints[3].Y -= 2;
                      m_objPoints[2].X += 1;
                      m_objPoints[2].Y -= 1;
                      m_objPoints[0].X += 1;
                      m_objPoints[0].Y += 1;  
                      
                  }
                  else if (m_objCurrentRotation == ONEEIGHTY)
                  {
                      m_objPoints[0].X -= 0;
                      m_objPoints[0].Y -= 2;
                      m_objPoints[1].X += 1;
                      m_objPoints[1].Y -= 1;
                      m_objPoints[3].X += 1;
                      m_objPoints[3].Y += 1;  
                  }
                  else if (m_objCurrentRotation == NINETY)
                  {
                      m_objPoints[0].X -= 2;
                      m_objPoints[0].Y += 0;
                      m_objPoints[1].X -= 1;
                      m_objPoints[1].Y -= 1;
                      m_objPoints[3].X += 1;
                      m_objPoints[3].Y -= 1;                        
                  }
                  else if (m_objCurrentRotation == TWOSEVENTY)
                  {
                      m_objPoints[3].X -= 2;
                      m_objPoints[3].Y += 0;
                      m_objPoints[2].X -= 1;
                      m_objPoints[2].Y -= 1;
                      m_objPoints[0].X += 1;
                      m_objPoints[0].Y -= 1;  
                  }
                  break;
              case J:
                  if (m_objCurrentRotation == INITIAL)
                  {
                      m_objPoints[3].X -= 1;
                      m_objPoints[3].Y -= 1;
                      m_objPoints[1].X += 1;
                      m_objPoints[1].Y += 1;
                      m_objPoints[0].X -= 0;
                      m_objPoints[0].Y += 2;
                      
                  }
                  else if (m_objCurrentRotation == ONEEIGHTY)
                  {
                      m_objPoints[0].X += 0;
                      m_objPoints[0].Y -= 2;
                      m_objPoints[1].X -= 1;
                      m_objPoints[1].Y -= 1;
                      m_objPoints[3].X += 1;
                      m_objPoints[3].Y += 1;
  
                  }
                  else if (m_objCurrentRotation == NINETY)
                  {
                      m_objPoints[0].X -= 2;
                      m_objPoints[0].Y -= 0;
                      m_objPoints[1].X -= 1;
                      m_objPoints[1].Y += 1;
                      m_objPoints[3].X += 1;
                      m_objPoints[3].Y -= 1;
                      
                  }
                  else if (m_objCurrentRotation == TWOSEVENTY)
                  {
  
                      m_objPoints[3].X -= 1;
                      m_objPoints[3].Y += 1;
                      m_objPoints[1].X += 1;
                      m_objPoints[1].Y -= 1;
                      m_objPoints[0].X += 2;
                      m_objPoints[0].Y -= 0;
  
                      
                  }
                  break;
              case L:
                  if (m_objCurrentRotation == INITIAL)
                  {
                      m_objPoints[0].X += 1;
                      m_objPoints[0].Y += 1;
                      m_objPoints[2].X -= 1;
                      m_objPoints[2].Y -= 1;
                      m_objPoints[3].X -= 2;
                      m_objPoints[3].Y += 0;
                  }
                  else if (m_objCurrentRotation == ONEEIGHTY)
                  {
                      m_objPoints[3].X += 2;
                      m_objPoints[3].Y += 0;
                      m_objPoints[2].X += 1;
                      m_objPoints[2].Y += 1;
                      m_objPoints[0].X -= 1;
                      m_objPoints[0].Y -= 1;
  
                  }
                  else if (m_objCurrentRotation == NINETY)
                  {
                      m_objPoints[3].X -= 0;
                      m_objPoints[3].Y -= 2;
                      m_objPoints[2].X += 1;
                      m_objPoints[2].Y -= 1;
                      m_objPoints[0].X -= 1;
                      m_objPoints[0].Y += 1;
  
                  }
                  else if (m_objCurrentRotation == TWOSEVENTY)
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
              case INITIAL:
                  m_objCurrentRotation = TWOSEVENTY;
                  break;
              case NINETY:
                  m_objCurrentRotation = INITIAL;
                  break;
              case ONEEIGHTY:
                  m_objCurrentRotation = NINETY;
                  break;
              case TWOSEVENTY:
                  m_objCurrentRotation = ONEEIGHTY;
                  break;
          }
      }
  };
}
