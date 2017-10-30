//*****************************************************************************
//
//THIS pairs with the Smart THINGS to turn on and off the stereo
//and the projector. The rs232 isn't working though with projector
//
///   Pin Layout for the Smartthigns Shield
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
///           --| 5V         9 |--IR LED, ensure the IRremomte library file boarddefs.h is set to timer 1 NOT 2
///           --| GND        8 |--
///           --| GND          |
///           --| Vin        7 |--
///             |            6 |--
///           --| A0         5 |--
///           --| A1    ( )  4 |--
///           --| A2         3 |--X THING_RX
///           --| A3  ____   2 |--X THING_TX
///           --| A4 |    |  1 |-- This is the RS232 send, unplug to update software (shares the port w/ Arduino)
///           --| A5 |    |  0 |--
///             |____|    |____|
///                  |____|
///
//*****************************************************************************
#include <SoftwareSerial.h>   //Needed for Smartthings, CANT use it for RS232, it conflicts
#include <SmartThings.h> //Smartthings library for communicating with Shield

//*****************************************************************************
// Global Variables & Definitions     | | | | | | | | | | | | | | | | | | | | |
//                                    V V V V V V V V V V V V V V V V V V V V V
//*****************************************************************************
#define PIN_LED         13 //Channel of the LED light?
#define PIN_THING_RX    3  //Channel the Smartthings hub uses to talk to the main arduino
#define PIN_THING_TX    2

bool isDebugEnabled = false;    // enable or disable debug in this example
int stateLED;           // state to track last set value of LED

SmartThingsCallout_t messageCallout;    //Smartthings calls this with incoming messages
SmartThings smartthing(PIN_THING_RX, PIN_THING_TX, messageCallout);  // constructor

//*****************************************************************************
// Function Prototyps | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
//                    V V V V V V V V V V V V V V V V V V V V V V V V V V V V V
//*****************************************************************************

void sndRS232(char triggerValue[]); //To send messages on the RS232
void sndCMD(unsigned long codeValue, int repeat = 1); //To send IR messages
void softwareSerialsetup(); //For the RS232 serial port

//*****************************************************************************
// Setup            | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
//                  V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V
//*****************************************************************************
  
void setup()
{
  // setup default state of global variables
  stateLED = 0;                 // matches state of hardware pin set below
  
  // setup hardware pins 
  pinMode(PIN_LED, OUTPUT);     // define PIN_LED as an output
  digitalWrite(PIN_LED, LOW);   // set value to LOW (off) to match stateLED=0
  smartthing.shieldSetLED(0, 0, 0);

  Serial.begin(115200);         // Ensure projector on baud rate of 115200

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (isDebugEnabled)
  { // setup debug serial port
    Serial.println("setup..");  // print out 'setup..' on start
  }
  Serial.println("baud test..");
}

//*****************************************************************************
// Main Loop        | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
//                  V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V
//*****************************************************************************

void loop()
{
  // run smartthing logic
  smartthing.run();  //On incomming message it triggers Message_callout
}





