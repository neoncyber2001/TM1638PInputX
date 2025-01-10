#include <Arduino.h>
#include <TM1638plus.h>
#include <TM1638PInputX.h>
#define  STROBE_TM 9 // strobe = GPIO connected to strobe line of module
#define  CLOCK_TM 8  // clock = GPIO connected to clock line of module
#define  DIO_TM 7 // data = GPIO connected to data line of module
bool high_freq = false; // default false, If using a high freq CPU > ~100 MHZ set to true. 
TM1638plus tm(STROBE_TM, CLOCK_TM , DIO_TM, high_freq);
TMInputX inputX(&tm);


//typedef void (*BtnPressedCB)(uint8_t);
//typedef void (*BtnReleasedCB)(uint8_t);

void onChanged(uint8_t pressed, uint8_t released){
  uint16_t changesgtates = (pressed<<8) | released;
  tm.setLEDs(changesgtates);
};

void onPressed(uint8_t pressed){
  String st = String(pressed, 10)+" P";
  char charArray[st.length() + 1]; 
  st.toCharArray(charArray,st.length()+1);
  tm.displayText(charArray);
};

void onRelease(uint8_t release){
  String st = String(release, 10)+" R";
  char charArray[st.length() + 1]; 
  st.toCharArray(charArray,st.length()+1);
  tm.displayText(charArray);
};

void setup() {
  // put your setup code here, to run once:
  tm.displayBegin();
  inputX.setChangeCB(onChanged);
  inputX.setPressedCB(onPressed,0);
  inputX.setPressedCB(onPressed,1);
  inputX.setPressedCB(onPressed,2);
  inputX.setPressedCB(onPressed,3);
  inputX.setPressedCB(onPressed,4);
  inputX.setPressedCB(onPressed,5);
  inputX.setPressedCB(onPressed,6);
  inputX.setPressedCB(onPressed,7);   
  inputX.setReleasedCB(onRelease,0);
  inputX.setReleasedCB(onRelease,1);
  inputX.setReleasedCB(onRelease,2);
  inputX.setReleasedCB(onRelease,3);
  inputX.setReleasedCB(onRelease,4);
  inputX.setReleasedCB(onRelease,5);
  inputX.setReleasedCB(onRelease,6);
  inputX.setReleasedCB(onRelease,7);
  tm.displayText("TM1638");
  delay(1000);
  tm.displayText("InputX");
  delay(1000);
  tm.displayText("EVENTS");
  delay(1000);
  uint8_t ledB = 0x01;
  uint32_t tt=millis()+1000;
  while (millis()<tt) {
      if(ledB==0x80)
      ledB=0x01;
    else{
      ledB=ledB<<1;
    }
    tm.setLEDs(ledB);
    delay(10);
  }
  tm.reset();
}

uint8_t led = 1;
uint32_t tmr = 0;
void loop() {
  tm.setLEDs(led);
  inputX.readInputs();
  if(millis()>tmr){  
    tmr=millis()+250;
  }
}




