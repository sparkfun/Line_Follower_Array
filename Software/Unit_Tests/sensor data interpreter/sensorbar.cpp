#include "sensorbar.h"

SensorBar::SensorBar()
{
    //ctor
}

uint8_t SensorBar::getRaw( void )
{
    return input;
}

int8_t SensorBar::getPosition( void )
{
    //Assign values to each bit, -127 to 127, sum, and divide
    int16_t accumulator = 0;
    uint8_t bitsCounted = 0;
    int16_t i;

    //get input from the I2C machine
    uint8_t tempInput = input;

    //count bits
    for( i = 0; i < 8; i++ )
    {
        if( ((tempInput >> i) & 0x01) == 1 )
        {
            bitsCounted++;
        }
    }

    //Find the vector value of each positive bit and sum
    for( i = 7; i > 3; i-- )
    {
        if( ((tempInput >> i) & 0x01) == 1 )
        {
            accumulator += ((32 * (i - 3)) - 1);
        }
    }
    for( i = 0; i < 4; i++ )
    {
        if( ((tempInput >> i) & 0x01) == 1 )
        {
            accumulator += ((-32 * (4 - i)) + 1);
        }
    }

    if( bitsCounted > 0 )
    {
        tempInput = accumulator / bitsCounted;
    }
    else
    {
        tempInput = 0;
    }

    return tempInput;
}

uint8_t SensorBar::getDensity( void )
{
    uint8_t bitsCounted = 0;
    uint8_t i;

    //get input from the I2C machine
    uint8_t tempInput = input;

    //count bits
    for( i = 0; i < 8; i++ )
    {
        if( ((tempInput >> i) & 0x01) == 1 )
        {
            bitsCounted++;
        }
    }
    return bitsCounted;
}
