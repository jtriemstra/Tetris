#ifndef GRIDENUMS_HEADER
#define GRIDENUMS_HEADER

namespace GridEnums{
  enum State
  {
      IDLE = 0,
      SHAPE_LIVE = 1,
      LOCKED = 2,
      CLEARING = 3
  };

  enum Command
  {
      NONE = 0,
      LEFT = 1,
      RIGHT = 2,
      CLOCKWISE = 3,
      COUNTERCLOCKWISE = 4,
      DOWN = 5
  };
}

#endif
