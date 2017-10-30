/*  Send IR Command
 *  sndCMD([command to do],[number of repeats to issue]);
 *  The repeat is useful for things like volume down 5
*/ 

#include <IRremote.h>  //Module to receive IR signals?  Not needed except to find a new IR code for a new receiver
IRsend irsend;  //This module needs the default IR send port to be changed from 3 in a fresh install of the library, see boarddefs.h

void sndCMD(unsigned long codeValue, int repeat = 1)
{
  stateLED = 1;                 // save state as 1 (on)
  digitalWrite(PIN_LED, HIGH);  // turn LED on
  smartthing.shieldSetLED(0, 0, 1);

  smartthing.send("on");        // send message to cloud

  for (int t = 0; t < repeat; t ++){
    if (t > 0) delay (205);
    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(codeValue, 32);
      delay(40);
    }
  } 
   
  // if debug is enabled print out the sent code
  if (isDebugEnabled)
  {
    Serial.print("Sent NEC ");
    Serial.println(codeValue, HEX);    
  }
  digitalWrite(PIN_LED, LOW);  // turn LED on
  smartthing.shieldSetLED(0, 0, 0);  
}
