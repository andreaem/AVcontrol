
/*
 * This controlls the  jy-r2t-v12 serial to RS232 adapotor attached to the Arduino
 * 
 * If it's not working, try powering off the projector, unplugging it, and then powering back on
*/

void sndRS232(char triggerValue[]) //, int repeat = 1)
{
  Serial.print("\r*"); //Very picky about the \r*COMMAND#\r they must be \r and in that exact format...
  Serial.print(triggerValue);
  Serial.println("#\r");
}
