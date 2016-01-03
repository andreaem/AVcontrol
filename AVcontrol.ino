//*****************************************************************************
//
//THIS pairs with the Smart THINGS to turn on and off the stereo
//and the projector. The rs232 isn't working though with projector
//

///
///
///
///
///
///
///
/// @file
/// @brief
///   Arduino SmartThings Shield LED Example 
/// @note
///              ______________
///             |              |
///             |         SW[] |
///             |[]RST         |
///             |         AREF |--
///             |          GND |--
///             |           13 |--X LED
///             |           12 |--
///             |           11 |--
///           --| 3.3V      10 |--
///           --| 5V         9 |--IR LED
///           --| GND        8 |--
///           --| GND          |
///           --| Vin        7 |--
///             |            6 |--
///           --| A0         5 |--
///           --| A1    ( )  4 |--
///           --| A2         3 |--X THING_RX
///           --| A3  ____   2 |--X THING_TX
///           --| A4 |    |  1 |--
///           --| A5 |    |  0 |--
///             |____|    |____|
///                  |____|
///
//*****************************************************************************
#include <SoftwareSerial.h>   //TODO need to set due to some weird wire language linker, should we absorb this whole library into smartthings
#include <SmartThings.h>


#include <IRremote.h>
IRsend irsend;

//*****************************************************************************
// Pin Definitions    | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
//                    V V V V V V V V V V V V V V V V V V V V V V V V V V V V V
//*****************************************************************************
#define PIN_LED         13
#define PIN_THING_RX    3
#define PIN_THING_TX    2

//*****************************************************************************
// Global Variables   | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
//                    V V V V V V V V V V V V V V V V V V V V V V V V V V V V V
//*****************************************************************************
SmartThingsCallout_t messageCallout;    // call out function forward decalaration
SmartThings smartthing(PIN_THING_RX, PIN_THING_TX, messageCallout);  // constructor

bool isDebugEnabled;    // enable or disable debug in this example
int stateLED;           // state to track last set value of LED

//*****************************************************************************
// Local Functions  | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
//                  V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V
//*****************************************************************************
void sndCMD(unsigned long codeValue, int repeat = 1)
{
  //stateLED = 1;                 // save state as 1 (on)
  //digitalWrite(PIN_LED, HIGH);  // turn LED on
  //smartthing.shieldSetLED(0, 0, 1);
  smartthing.send("on");        // send message to cloud
  
  for (int t = 0; t < repeat; t ++){
    if (t > 0) delay (205);
    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(codeValue, 32);
      delay(40);
    }
  Serial.print("Sent NEC ");
  Serial.println(codeValue, HEX);    
  }
}

//*****************************************************************************


//*****************************************************************************
// API Functions    | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
//                  V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V
//*****************************************************************************
void setup()
{
  // setup default state of global variables
  isDebugEnabled = true;
  stateLED = 0;                 // matches state of hardware pin set below
  
  // setup hardware pins 
  pinMode(PIN_LED, OUTPUT);     // define PIN_LED as an output
  digitalWrite(PIN_LED, LOW);   // set value to LOW (off) to match stateLED=0

  if (isDebugEnabled)
  { // setup debug serial port
    Serial.begin(9600);         // setup serial with a baud rate of 9600
    Serial.println("setup..");  // print out 'setup..' on start
  }
}

//*****************************************************************************

void loop()
{
  // run smartthing logic
  smartthing.run();
    
}

//*****************************************************************************
void messageCallout(String message)
{
  // if debug is enabled print out the received message
  if (isDebugEnabled)
  {
    Serial.print("Received message: '");
    Serial.print(message);
    Serial.println("' ");
  }

///delay (205); for repete commands
///
///STEREO
///BD/DVD 4B3631CE     1261842894   (cable plugged in)
///VCR 4BB6F00F
///CBL 4BB6708F
///GAME 4BB6B04F       1270263887   (XBOX)
///TV/CD 4BB6906F      1270255727

///VOL UP 4BB640BF     1270235327
///VOL DOWN 4BB6C03F   1270267967
///MUTE 4BB6A05F
///
///PROJECTOR:
///On/OFF C40BF     803007

  //STEREO
  //modes
  unsigned long BD_DVD = 1261842894; //CABLE Plugged in
  unsigned long GAME = 1270263887;
  unsigned long TV_CD = 1270255727; //for the music player
  //audio
  unsigned long volUP = 1270235327;
  unsigned long volDOWN = 1270267967;
  unsigned long mute =  1270259807;
  //power 
  unsigned long stereoON= 1270227167; //stereo ON
  unsigned long stereoOFF = 1261888029; //stereo OFF

  //PROJECTOR
  unsigned long projectorTOGGLE= 803007; //projector on/off (dbl for off)
  


  // based on message contents, calls proper function
  // sndCMD([command to do],[number of repeats to issue]);
  if (message.equals("systemOn"))
  {
    sndCMD(stereoON);    
    sndCMD(projectorTOGGLE);
    sndCMD(GAME);
  }
  else if (message.equals("systemOff"))
  {
    sndCMD(stereoOFF);
    sndCMD(projectorTOGGLE,3);
  }
  else if (message.equals("stereoON"))
  {
    sndCMD(stereoON);
    sndCMD(TV_CD);
  }
  else if (message.equals("stereoOFF"))
  {
    sndCMD(stereoOFF);
  }
  else if (message.equals("volUP")) sndCMD(volUP,5);
  else if (message.equals("volDOWN")) sndCMD(volDOWN,5);
  else if (message.equals("mute")) sndCMD(mute);
  
}

