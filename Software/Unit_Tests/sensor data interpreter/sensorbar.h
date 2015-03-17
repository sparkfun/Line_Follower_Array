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
    //move input to private eventually
    uint8_t input;
protected:
private:
};

#endif // SENSORBAR_H
