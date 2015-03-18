#include "sensorbar.h"
#include <Wire.h>

SensorBar::SensorBar()
{
  //ctor
}

uint8_t SensorBar::getRaw( void )
{
  scan();
  return lastBarRawValue;
}

int8_t SensorBar::getPosition( void )
{
  //Assign values to each bit, -127 to 127, sum, and divide
  int16_t accumulator = 0;
  uint8_t bitsCounted = 0;
  int16_t i;

  //get input from the I2C machine
  scan();

  //count bits
  for( i = 0; i < 8; i++ )
  {
    if( ((lastBarRawValue >> i) & 0x01) == 1 )
    {
      bitsCounted++;
    }
  }

  //Find the vector value of each positive bit and sum
  for( i = 7; i > 3; i-- )
  {
    if( ((lastBarRawValue >> i) & 0x01) == 1 )
    {
      accumulator += ((32 * (i - 3)) - 1);
    }
  }
  for( i = 0; i < 4; i++ )
  {
    if( ((lastBarRawValue >> i) & 0x01) == 1 )
    {
      accumulator += ((-32 * (4 - i)) + 1);
    }
  }

  if( bitsCounted > 0 )
  {
    lastBarRawValue = accumulator / bitsCounted;
  }
  else
  {
    lastBarRawValue = 0;
  }

  return lastBarRawValue;
}

uint8_t SensorBar::getDensity( void )
{
  uint8_t bitsCounted = 0;
  uint8_t i;

  //get input from the I2C machine
  scan();

  //count bits
  for( i = 0; i < 8; i++ )
  {
    if( ((lastBarRawValue >> i) & 0x01) == 1 )
    {
      bitsCounted++;
    }
  }
  return bitsCounted;
}

void SensorBar::scan( void )
{
  //Operate the I2C machine
  Wire.requestFrom(0x25, 2);    // request 2 bytes from slave device at 0x25

  int i = 0;
  char inputBuffer[3];

  while(Wire.available())    // slave may send less than requested
  {
    if(i < 3)
    {
      inputBuffer[i] = Wire.read(); // receive a byte as character
    }
    i++;
  }
  lastBarRawValue = inputBuffer[0];
}



CircularStack::CircularStack()
{
  cStackLastPtr = 0;
  cStackElementsUsed = 0;  
}

int16_t CircularStack::getElement( uint8_t elementNum ) //zero is the push location.  Max is CSTACK_MAX_LENGTH - 1
{
  //Translate elementNum into terms of cStackLastPtr.
  int16_t virtualElementNum;
  virtualElementNum = cStackLastPtr - elementNum;
  if( virtualElementNum < 0 )
  {
    virtualElementNum += CSTACK_MAX_LENGTH;
  }
  
  //Output the value
  return cStackData[virtualElementNum];
}

void CircularStack::pushElement( int16_t elementVal )
{
  //inc. the pointer
  cStackLastPtr++;

  //deal with roll
  if( cStackLastPtr >= CSTACK_MAX_LENGTH )
  {
    cStackLastPtr = 0;
  }

  //write data
  cStackData[cStackLastPtr] = elementVal;

  //increase length up to CSTACK_MAX_LENGTH
  if( cStackElementsUsed < CSTACK_MAX_LENGTH )
  {
    cStackElementsUsed++;
  }
}

int16_t CircularStack::averageLast( uint8_t numElements )
{
  //Add up all the elements
  int32_t accumulator = 0;
  int8_t i;
  for( i = 0; i < numElements; i++ )
  {
    accumulator += getElement( i );
  }
  //Divide by number of elements
  accumulator /= numElements;
  return accumulator;
}

uint8_t CircularStack::recordLength( void )
{
  return cStackElementsUsed;
}

