#include "grid.cpp"
#include "grid_enums.h"
#include "Arduino.h"
 
class Game{
    private:
      unsigned long m_lngNextDrop = 0;
      unsigned long m_lngStopClearing = 0;
      unsigned long m_lngDropDelay = 1000000;
      
      Shape* m_objCurrentShape;
      Grid m_objGrid;
      GridEnums::State m_objCurrentState = GridEnums::IDLE;
      
      void (*m_fnRefreshDisplay)();
      GridEnums::Command (*m_fnReceiveInput)();
      
    public:
      int CurrentDisplay(int intColumn, int intRow)
      {
        for (Point &p : m_objCurrentShape->getPoints().Points)
          {
              if (p.X == intColumn && p.Y == intRow) return (int) m_objCurrentShape->getType();                
          }
        return m_objGrid.getStaticPoint(intColumn, intRow);
      }

      Game(void (*fnRefreshDisplay)(), GridEnums::Command(*fnReceiveInput)())
      {
          m_fnRefreshDisplay = fnRefreshDisplay;
          m_fnReceiveInput = fnReceiveInput;
      }

      void play()
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

      bool tryGenerate()
      {
          if (m_objCurrentState == GridEnums::IDLE)
          {
              m_objCurrentState = GridEnums::SHAPE_LIVE;
              m_objCurrentShape = new Shape(static_cast<ShapeEnums::Types>((int)random(1,8)));
              m_objCurrentShape->center();
              return true;
          }

          return false;
      }

      bool receiveInput()
      {
          if (m_objCurrentState == GridEnums::SHAPE_LIVE)
          {
              GridEnums::Command objThisCommand = m_fnReceiveInput();
              switch (objThisCommand)
              {
                  case GridEnums::LEFT:
                      m_objCurrentShape->moveLeft();
                      break;
                  case GridEnums::RIGHT:
                      m_objCurrentShape->moveRight();
                      break;
                  case GridEnums::CLOCKWISE:
                      m_objCurrentShape->rotateClockwise();
                      break;
                  case GridEnums::COUNTERCLOCKWISE:
                      m_objCurrentShape->rotateCounterclockwise();
                      break;
                  case GridEnums::DOWN:
                      m_objCurrentShape->moveDown();
                      break;
              }

              if (m_objGrid.isCollision(m_objCurrentShape))
              {
                  m_objCurrentShape->restoreState();
              }

              return objThisCommand != GridEnums::NONE;
          }
          return false;
      }

      bool tryDrop()
      {
          if (m_objCurrentState == GridEnums::SHAPE_LIVE)
          {
              if (micros() >= m_lngNextDrop)
              {
                  m_objCurrentShape->moveDown();
                  if (!m_objGrid.isCollision(m_objCurrentShape))
                  {
                      m_lngNextDrop = micros() + m_lngDropDelay;                      
                  }
                  else
                  {
                      m_objCurrentShape->restoreState();
                      m_objGrid.lockShape(m_objCurrentShape);
                      delete m_objCurrentShape;
                      m_objCurrentState = GridEnums::LOCKED;            
                  }
                  return true;
              }
          }

          return false;
      }

      void tryClear()
      {
          if (m_objCurrentState == GridEnums::LOCKED)
          {
              if (m_objGrid.tryClear(m_objCurrentShape->getBottomRow()))
              {
                  m_objCurrentState = GridEnums::CLEARING;
                  m_lngStopClearing = micros() + 1000000;

              }
              else
              {
                  m_objCurrentState = GridEnums::IDLE;
              }
          }
          else if (m_objCurrentState == GridEnums::CLEARING)
          {
              if (micros() > m_lngStopClearing)
              {
                  m_objGrid.finishClear();
                  m_lngStopClearing = 60 * 60 * 1000 * 1000; //an hour. micros() will roll over soon after anyway, and you shouldn't play this that long :)
                  m_objCurrentState = GridEnums::IDLE;
              }
          }
      }

      void refreshDisplay(bool blnDoUpdate)
      {
          if (blnDoUpdate)
          {
              if (m_objCurrentState == GridEnums::SHAPE_LIVE || m_objCurrentState == GridEnums::CLEARING)
              {
                  m_fnRefreshDisplay();
              }
          }
      }
};

