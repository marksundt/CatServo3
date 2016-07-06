#ifndef DrawCircle_h
#define DrawCircle_h

#include <Servo.h>

struct Coordinates {
  int x;
  int y;
};

class DrawCircle
{
  public: 
    DrawCircle();
    void next_move(int x, int radius, Servo s1, Servo s2);
private:
 
};


#endif
