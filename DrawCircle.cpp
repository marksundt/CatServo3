#include <Arduino.h>
#include <Servo.h>
#include "DrawCircle.h"

DrawCircle::DrawCircle()
{

}

void DrawCircle::next_move(int x, int radius, Servo s1, Servo s2)
{
   //float x = (float)(radius * Math.Cos(angleInDegrees * Math.PI / 180F)) + origin.X;
   //float y = (float)(radius * Math.Sin(angleInDegrees * Math.PI / 180F)) + origin.Y;

   int Cx = (int)(radius * (cos((x * 3.14159F)/180.0F)) + 90.0F);
   int Cy = (int)(radius * (sin((x * 3.14159F)/180.0F)) + 90.0F);

   s1.write(Cx);
   s2.write(Cy);
   
   Serial.print(x);
   Serial.print(", ");
   Serial.print(Cx);
   Serial.print(", ");
   Serial.print(Cy);
   Serial.print(", ");
   Serial.println(radius);

}

