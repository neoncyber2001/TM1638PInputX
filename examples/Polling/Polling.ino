#include <Arduino.h>
#include <TM1638plus.h>
#include <TM1638PInputX.h>
#define  STROBE_TM 9 // strobe = GPIO connected to strobe line of module
#define  CLOCK_TM 8  // clock = GPIO connected to clock line of module
#define  DIO_TM 7 // data = GPIO connected to data line of module
bool high_freq = false; // default false, If using a high freq CPU > ~100 MHZ set to true. 
TM1638plus tm(STROBE_TM, CLOCK_TM , DIO_TM, high_freq);
TMInputX inputX(&tm);



void setup() {
  // put your setup code here, to run once:
  tm.displayBegin(); 
}

void loop() {
  if(inputX.readInputs()){
    if(inputX.getButtonJustPressed(0)){
      tm.displayText("BTN0PRSD");
    }
  }
}

