
/*
The API calls that can be made to the AV controller device
Smartthings calls this function when it receives a zigbee communication.

Troubleshooting:
Beware 2.4ghz WiFi majorly conflicts...

There needs to be a 1000ms pause between calls going out...
"BD_DVDOn" //ChromeCast
"VCROn" // Cord
"CBLOn"
"GAMEOn" //xBox
"TV_CDOn"
"stereoOn"
"stereoOff"
"projectorOff"
"projectorOn"
"volUP" Volume up 5
"volDOWN" Volume down 5
"mute"
*/

//IR codes for the Onkyo Stereo
//modes
unsigned long BD_DVD = 1261842894; //CABLE Plugged in
unsigned long VCR = 1270280207; //VCR
unsigned long CBL = 1270247567; //Cable TV
unsigned long GAME = 1270263887; //xBox
unsigned long TV_CD = 1270255727; //for the music player
//audio
unsigned long volUP = 1270235327;
unsigned long volDOWN = 1270267967;
unsigned long mute =  1270259807;
//power 
unsigned long stereoON= 1270227167; //stereo ON
unsigned long stereoOFF = 1261888029; //stereo OFF


void messageCallout(String message)
{
  // if debug is enabled print out the received message
  if (isDebugEnabled)
  {
    Serial.print("Received message: '");
    Serial.print(message);
    Serial.println("' ");
  }

  // based on message contents, calls proper function
  //Hash table possible perhaps to remove if statements?
    
  
  if (message.equals("BD_DVDOn")) sndCMD(BD_DVD); //ChromeCast 
  if (message.equals("VCROn")) sndCMD(VCR); // Cord
  if (message.equals("CBLOn")) sndCMD(CBL);
  if (message.equals("GAMEOn")) sndCMD(GAME,3); // Steam Computer
  if (message.equals("TV_CDOn")) sndCMD(TV_CD);
  if (message.equals("stereoOn")) sndCMD(stereoON,3);
  if (message.equals("stereoOff")) sndCMD(stereoOFF,3);
  if (message.equals("volUP")) sndCMD(volUP,5);
  if (message.equals("volDOWN")) sndCMD(volDOWN,5);
  if (message.equals("mute")) sndCMD(mute);  
 
  if (message.equals("projectorOff")) sndRS232("pow=off");    
  if (message.equals("projectorOn"))sndRS232("pow=on");   
}

/*
 * Old legacy codes not used anymore 
//PROJECTOR OLD IR codes not in use anymore
unsigned long projectorON= 1286815935; //projector on/off (dbl for off)
unsigned long projectorOFF= 1286829195; //projector on/off (dbl for off) 
*/

