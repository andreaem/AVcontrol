# AVcontrol
An AV controller for IR devices

This is a controller for my Smartthings home entertainment System.  I have an Onkyo mixer and a Ben-Q 1070W projector connected to an Arduino Uno by an IR led (soldered onto a lead plugged into the arduino) and RS232 using a jy-r2t-v12 RS232 to TTL adapter.

Pin connections
(9) - IR led, the IR library by default uses pin 3, and that conflicts with the Smartthings library which uses pin 2/3 for the communication with the board.
(1) - TX on an RS232 connection.  You cant use SoftwareSerial again because it conflicts with the Smartthings library, so just unplug the RS232 when you install new software

Setting up an environemnt:

Install Smartthings and IRremote library
Change the default IRremote pin to 9
delete the default Arduino IR robot library that comes with it, conflicts with IRremote


Notes:

Sometimes you need to hard power off the projector to get the RS2323 to referesh.
There is also reader software to get the IR codes from a remote, it uses pin 9 but it's out of date and may not work.
