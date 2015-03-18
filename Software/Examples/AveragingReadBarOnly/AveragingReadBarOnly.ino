#include "chartools.h"
#include "Wire.h"
#include "sensorbar.h"

SensorBar mySensorBar;
CircularStack positionHistory;
uint16_t msTick = 0;

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(38400);  // start serial for output
}

void loop()
{
  //Wait 1 ms
  delay(5);

  //Increment the tick
  msTick++;

  //Do ms related activities
  int temp = mySensorBar.getDensity();
  if( (temp < 4)&&(temp > 0) )
  {
    positionHistory.pushElement( mySensorBar.getPosition());
  }

  //If the tick is too high, decrement it and do long scale activities
  if( msTick > 20 )
  {
    msTick -= 20;

    //print me a meter!
    int16_t i;
    int16_t avePos = positionHistory.averageLast( 100 );
    Serial.print("Scale = 5/char :");
    for( i = 130; i >= -130; i = i - 5 )
    {
      if( i < 0 )
      {
        //if avePos within 5 of i
        if((avePos > (i - 3)) && (avePos <= (i + 2)))
        {
          Serial.print("*");
        }
        else
        {
          Serial.print("-");
        }
      }
      else if( i == 0 )
      {
        //if avePos within 5 of i
        if((avePos > (i - 3)) && (avePos <= (i + 2)))
        {
          Serial.print("*");
        }
        else
        {
          Serial.print("+");
        }
      }
      else if( i > 0 )
      {
        //if avePos within 5 of i
        if((avePos > (i - 3)) && (avePos <= (i + 2)))
        {
          Serial.print("*");
        }
        else
        {
          Serial.print("-");
        }
      }
    }
    Serial.print(" avePos = ");
    Serial.println(avePos);
  }
}






