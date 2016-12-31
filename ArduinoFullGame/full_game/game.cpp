#include "grid.cpp"
#include "grid_enums.h"
#include "Arduino.h"

class Game{
        private:
          unsigned long m_lngNextDrop;
          Shape* m_objCurrentShape;
          Grid m_objGrid;
          GridEnums::State m_objCurrentState = GridEnums::IDLE;
          int m_intDropDelay = 1000000;
          void (*m_fnRefreshDisplay)(GridPoint);
          GridEnums::Command (*m_fnReceiveInput)();
          unsigned long m_lngStopClearing;
          

      public:
        GridPoint CurrentDisplay() const
        {
          GridPoint objReturn = m_objGrid.StaticPoints();
          for (Point &p : m_objCurrentShape->Points().Points)
          {
              objReturn.Points[p.X][p.Y] = m_objCurrentShape->Type();
          }
          return objReturn;
        }

        Game(void (*fnRefreshDisplay)(GridPoint), GridEnums::Command(*fnReceiveInput)())
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
                m_objCurrentShape->Center();
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
                        m_objCurrentShape->MoveLeft(m_objGrid.LEFT_EDGE);
                        break;
                    case GridEnums::RIGHT:
                        m_objCurrentShape->MoveRight(m_objGrid.LEFT_EDGE + m_objGrid.WIDTH);
                        break;
                    case GridEnums::CLOCKWISE:
                        m_objCurrentShape->RotateClockwise(m_objGrid.LEFT_EDGE, m_objGrid.LEFT_EDGE + m_objGrid.WIDTH);
                        break;
                    case GridEnums::COUNTERCLOCKWISE:
                        m_objCurrentShape->RotateCounterclockwise();
                        break;
                    case GridEnums::DOWN:
                        if (m_objGrid.ShapeCanDrop(m_objCurrentShape))
                        {
                            m_objCurrentShape->MoveDown(m_objGrid.HEIGHT - 1);
                        }
                        break;
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
                    if (m_objGrid.ShapeCanDrop(m_objCurrentShape))
                    {
                        m_objCurrentShape->MoveDown(m_objGrid.HEIGHT - 1);
                        m_lngNextDrop = micros() + m_intDropDelay;
                    }
                    else
                    {
                        m_objGrid.LockShape(m_objCurrentShape);
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
                if (m_objGrid.TryClear(m_objCurrentShape->BottomRow()))
                {
                    m_objCurrentState = GridEnums::CLEARING;
                    m_lngStopClearing = micros() + 1000000);

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
                    m_objGrid.FinishClear();
                    m_lngStopClearing = 60 * 60 * 1000 * 1000;
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
                    m_fnRefreshDisplay(this.CurrentDisplay);
                }
            }
        }
};

