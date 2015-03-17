#include <cstdlib>
#include "stdio.h"
#include "stdint.h"
#include "sensorbar.h"
using namespace std;

void printOutputs(uint8_t input);

SensorBar mySensorBar;

int main()
{
    int16_t i;

    uint8_t input = 0x03;

    printf ("SensorBar Unit Test\n\n");



    //First test.  Apply two bits scrolling across the input
    // 00000011
    // 00000110
    // ...

    printf ("\n\nFirst test, rolling 1's\n");

    for( i = 0; i < 7; i++)
    {
        printOutputs(input);

        //push dots
        input = input << 1;
    }


    //Second test.  Apply two bits zero scrolling across the input
    // 11111100
    // 11111001
    // ...
    printf ("\n\nSecond test, rolling zeros\n");
    input = 0xFC;
    for( i = 0; i < 7; i++)
    {
        printOutputs(input);

        //push dots
        input = (input << 1) + 1;
    }

    //Extremes, 0xFF and 0x00
    printf ("\n\nTest the limits\n");
    input = 0xFF;
    printOutputs(input);

    input = 0x00;
    printOutputs(input);

    input = 0xF0;
    printOutputs(input);

    input = 0x0F;
    printOutputs(input);

    //Now do 20 random numbers
    //Increment rand some number of times
    for( int i = 0; i < 62; i++)
    {
        rand();
    }

    printf ("\n\n20 random numbers\n");

    for( i = 0; i < 20; i++)
    {
        input = rand() % 256;

        printOutputs(input);
    }
}

void printOutputs(uint8_t input)
{
    int16_t i;
    mySensorBar.input = input;

    printf ("\n");

    //get binary
    printf ("Bin value of input: ");
    for( i = 7; i >= 0; i-- )
    {
        printf ("%01d", ((input >> i) & 0x01));
    }
    printf ("b\n");

    //get raw
    printf ("Hex value of bar: 0x%02X\n", mySensorBar.getRaw());

    //get vectors
    printf ("Position (out of 256): %d\n", mySensorBar.getPosition());
    printf ("Density, bits detected (of 8): %d\n", mySensorBar.getDensity());

}
