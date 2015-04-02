#RedBot_Line_Follower_Bar  
##Example Sketch Descriptions
* AveragingFollower  
 _Does a sort of over-sampling on the sensor readings, doesn't work too well_

* AveragingReadBarOnly  
 _Like the_ AveragingFollower _but doesn't drive, outputs serial_

* LessBasicFollower  
 _Like the_ MostBasicFollower _with an additional "corner detected" action_

* MostBasicFollower  
 _Simply tries to steer towards center. **After playing with the sensor, run this sketch on an actual robot course**_

* NintendoControlled  
 _run the redBot by XBee!  Need to form a packet on the airwaves..._

* ReadBarOnly  
 _Dump the various method calls to the serial term. **This is a good place to start**_

##Method Descriptions

####SensorBar::SensorBar()  
This is the constructor.  It takes no arguements and does nothing.

####uint8_t SensorBar::getRaw( void )  
The method getRaw() takes no arguements and returns a picture of what the bar sees in bits.

![Leftmost2](https://github.com/marshalltaylorSFE/staged_photos/raw/master/left2.png)  
If the bar sees a line (dark) under the left most two sensors, getRaw() would return 0xC0, or 1100000b

####int8_t SensorBar::getPosition( void )  
Use this method to get an average direction of where the line is, as a number from -127 to 127.  

![Leftmost2](https://github.com/marshalltaylorSFE/staged_photos/raw/master/left2.png)  
With the left most two detectors example, this method returns decimal 111.

![Leftmost2](https://github.com/marshalltaylorSFE/staged_photos/raw/master/left4.png)  
If the left 4 are covered, it returns 79.


A way to conceptualize this method is that it returns a 1 dimetional vector that points to the center of the density of the detected line.

####uint8_t SensorBar::getDensity( void )  
This method returns the number of sensors that detect dark, 0 through 8.

####void SensorBar::scan( void )  
**This method must be periodically called!**  It operates the I2C machine and updates the internal class members so that the other functions work

