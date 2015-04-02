#include "chartools.h"
#include "Wire.h"
#include "sensorbar.h"
#include <RedBot.h>  // This line "includes" the RedBot library into your sketch.
// Provides special objects, methods, and functions for the RedBot.

RedBotMotors motors; // Instantiate the motor control object. This only needs
// to be done once.

#define PACKET_LENGTH 10
#define START_SYMBOL '~'

char lastchar;
char packet[PACKET_LENGTH];
char lastPacket[PACKET_LENGTH];
char packetPending = 0;

char packet_ptr;

#define IDLE_STATE 0
#define READ_LINE 1
#define GO_FORWARD 2
#define GO_FORWARD_FAST 3
#define GO_LEFT 4
#define GO_RIGHT 5
#define GO_BACKWARDS 6

int8_t state;
SensorBar mySensorBar;

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  //Serial1.begin(9600);
}

void loop()
{
  if (Serial.available())
  {
    lastchar = Serial.read();
    //look for packet start (START_SYMBOL)
    if( lastchar == START_SYMBOL )
    {
      //Flag that the packet needs to be serviced
      packetPending = 1;
      
      //Fill packet with null, reset the pointer
      for( int i = 0; i < PACKET_LENGTH; i++ )
      {
        packet[i] = 0;
      }
      //write the start char
      packet[0] = START_SYMBOL;
      //reset the pointer
      packet_ptr = 1;
    }
    else
    if( ( packet_ptr < PACKET_LENGTH ) && (packet_ptr > 0) )//check for room in the packet, and that the start char has been seen
    {
      //put the char in the packet
      packet[packet_ptr] = lastchar;
      //advance the pointer
      packet_ptr++;
      //turn on LED
    }
    else
    {
      //Just overwrite to the last position
      packet[PACKET_LENGTH - 1] = lastchar;
    }
  }
  
  //if the packet is full and the last char is LF or CR, *do something here*
  if((packetPending == 1) && ((packet_ptr == PACKET_LENGTH) && ((packet[PACKET_LENGTH - 1] == 0x0A) || (packet[PACKET_LENGTH - 1] == 0x0D))) )
  {
    digitalWrite(13, digitalRead(13)^1);
    //check for new data
    packetPending = 0;
    if( packet[1] == '0' )
    {
      state = GO_LEFT;
    }
    else if( packet[2] == '0' )
    {
      state = GO_RIGHT;
    }
    else if( packet[3] == '0' )
    {
      state = GO_FORWARD;
    }
    else if( packet[4] == '0' )
    {
      state = GO_BACKWARDS;
    }
    else if( packet[7] == '0' )
    {
      state = GO_FORWARD_FAST;
    }
    else
    {
      state = IDLE_STATE;
    }

  }

  uint8_t nextState = state;
  switch (state) {
  case IDLE_STATE:
    motors.stop();       // Stops both motors
    break;
  case GO_FORWARD:
    motors.rightMotor(100);
    motors.leftMotor(-100);
    break;
  case GO_BACKWARDS:
    motors.rightMotor(-100);
    motors.leftMotor(100);
    break;
  case GO_FORWARD_FAST:
    motors.rightMotor(255);
    motors.leftMotor(-255);
    break;
  case GO_LEFT:
    motors.rightMotor(100);
    motors.leftMotor(-0);
    break;
  case GO_RIGHT:
    motors.rightMotor(0);
    motors.leftMotor(-100);
    break;
  default:
    motors.stop();       // Stops both motors
    break;
  }
  state = nextState;
  //delay(100);
}





