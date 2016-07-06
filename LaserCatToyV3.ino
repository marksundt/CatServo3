// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.
#include <Servo.h> 
#include <SimbleeForMobile.h>

#include "DrawCircle.h"

DrawCircle drawCircle;
Coordinates cord;
 Servo myservo[2];  // create servo objects to control a servo 
unsigned long lastUpdate;
int pos = 0;    // variable to store the rotation position 
int updateInterval;
int radius;
bool makeCircle;
int8_t servo;
uint8_t value[4];
uint8_t output;
uint8_t circDiaVal;
uint8_t diaSlider;
uint8_t stepper;
uint8_t delayVal;
uint8_t delaySlider;
uint8_t action;
uint8_t drawGo;
uint8_t center;
//uint8_t spiral;
uint8_t randDir;
uint8_t continous;
int global_delay;
int global_radius;
bool global_continous;
int global_action;
  
void setup() 
{ 
  Serial.begin(38400);
  
  myservo[0].attach(2);  // attaches the servo on pin 2 to the servo object (Servo Output 1 of Servo Shield)
  myservo[1].attach(3);  // attaches the servo on pin 3 to the servo object (Servo Output 2 of Servo Shield)

  // center servos
  myservo[0].write(90);
  myservo[1].write(90);
  delay(1000); // put this in to slow down the boot up
 // updateInterval = 200;
  makeCircle = false;

  global_delay = 200;
  global_radius = 24;
  global_continous = false;
  global_action = 0;

  //***********************
    // put your setup code here, to run once:
  SimbleeForMobile.deviceName = "Newtonian";
  SimbleeForMobile.advertisementData = "Laser";
  SimbleeForMobile.domain = "PetSensor.Network";
  //SimbleeForMobile.advertisementInterval = 675;
  // Begin Simblee UI
  SimbleeForMobile.begin();
} 
 
 
void loop() 
{ 
  SimbleeForMobile.process();  

  
   if(makeCircle)
   {
   if((millis() - lastUpdate) > global_delay)  // time to update
    {
     lastUpdate = millis();
      pos += 1;
      drawCircle.next_move(pos, global_radius, myservo[0], myservo[1]); 
      if(pos > 360)
        {
          pos = 1;

          if(!global_continous)
            makeCircle = false;
        }
    }
   
  } 
}

/*
 * SimbleeForMobile UI callback requesting the user interface
 */
void ui()
{  

  //Create your own UI here!
  SimbleeForMobile.beginScreen(WHITE);

  center = SimbleeForMobile.drawButton(20, 150, 280, "Center");
  
  drawGo = SimbleeForMobile.drawButton(20, 200, 280, "Go!");

  // For some reason if you do this before the buttion it fails
  SimbleeForMobile.drawText(100, 110, "Cat Laser Toy");

  char *titles2[] = { "Circle", "ZigZag", "Spiral" };
  action = SimbleeForMobile.drawSegment(25, 250, 280, titles2, countof(titles2));  
  
  SimbleeForMobile.drawText(30, 300, "Random Direction:");
  randDir = SimbleeForMobile.drawSwitch(200, 300);

  SimbleeForMobile.drawText(30, 350, "Continous:");
  continous = SimbleeForMobile.drawSwitch(200, 350);
  
  SimbleeForMobile.drawText(20, 430, "Circle Diameter:");
  circDiaVal = SimbleeForMobile.drawTextField(230, 450, 60, 90);
  diaSlider = SimbleeForMobile.drawSlider(20, 450, 200, 10, 50);
  
  SimbleeForMobile.drawText(20, 480, "Delay in ms:");
  delayVal = SimbleeForMobile.drawTextField(230, 500, 60, 1);
  delaySlider = SimbleeForMobile.drawSlider(20, 500, 200, 50, 500);
  
  SimbleeForMobile.endScreen();
}

/*
 * SimbleeForMobile event callback method
 */
void ui_event(event_t &event)
{

   if (event.id == drawGo)
  {
    //{ "Circle", "ZigZag", "Spiral" };
     if (global_action == 0)
        makeCircle = true;
    else if (global_action == 1)
      Serial.print("ZigZag");
    else if (global_action == 2)
      Serial.print("Spiral");

  }

  if (event.id == center)
  {
    move_center();
  }

 if (event.id == diaSlider)
  {
      SimbleeForMobile.updateValue(circDiaVal, event.value);
      global_radius = (int)event.value;
  }
 if (event.id == circDiaVal)
  {
      SimbleeForMobile.updateValue(diaSlider, event.value);
      global_radius = (int)event.value;
  }
  
 if (event.id == delaySlider)
  {
     SimbleeForMobile.updateValue(delayVal, event.value);
     global_delay = event.value;
  }
  
   if (event.id == delayVal)
  {
     SimbleeForMobile.updateValue(delaySlider, event.value);
     global_delay = event.value;
  }
  
 if (event.id == continous)
  {
    if(event.value == 1) // switch 1 is on, 0 is off
    {
        global_continous = false;
    }
  else
    {
        global_continous = true;
    }
  }

  //{ "Circle", "ZigZag", "Spiral" };
  if (event.id == action)
  {
    if (event.value == 0)
      global_action = 0;
    else if (event.value == 1)
      global_action = 1;
    else if (event.value == 2)
      global_action = 2;
  } 

}

void update_ui(uint8_t val)
{
  // Initial Screen update - pull data from EPROMM
  SimbleeForMobile.updateValue(circDiaVal, 24);//Dia is Radius
  SimbleeForMobile.updateValue(diaSlider, 24);
  SimbleeForMobile.updateValue(delayVal, 200);
  SimbleeForMobile.updateValue(delaySlider, 200);
 // SimbleeForMobile.updateValue(spiral, 0);
  SimbleeForMobile.updateValue(randDir, 0);
  SimbleeForMobile.updateValue(continous, 0);
  SimbleeForMobile.updateValue(action, 0);      

}

void move_center()
{
   myservo[0].write(90);
   myservo[1].write(90);
}
