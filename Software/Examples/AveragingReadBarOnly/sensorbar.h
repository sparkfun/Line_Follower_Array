#ifndef SENSORBAR_H
#define SENSORBAR_H
#include "stdint.h"

class SensorBar
{
public:
    SensorBar();
    uint8_t getRaw( void );
    int8_t getPosition( void );
    uint8_t getDensity( void );
    void scan( void );
    //move input to private eventually
    uint8_t input;
protected:
private:
    uint8_t lastBarRawValue;
};


//Class CircularStack is int16_t
//Does not care about over-running real data ( if request is outside length's bounds )
//The underlying machine writes [48], [49], [0], [1] ... 
#define CSTACK_MAX_LENGTH 500

class CircularStack
{
public:
    CircularStack();
    int16_t getElement( uint8_t ); //zero is the push location
    void pushElement( int16_t );
    int16_t averageLast( uint8_t );
    uint8_t recordLength( void );
private:
    int16_t cStackData[CSTACK_MAX_LENGTH];
    int16_t cStackLastPtr;
    uint8_t cStackElementsUsed;
};

#endif // SENSORBAR_H
