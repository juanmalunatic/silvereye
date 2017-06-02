// v 2016-09-21

/*

jReadLength:
Implements ReadLength, a private method of the Adafruit_BNO055 library,
in order to read the registers on the BNO055 sensor directly.

createFrame:
Reads the sensor data and formats a frame following the specific needs
of this application. Frame format can be found in Datasheets/Trama.docx

isBNO055Connected: (DON'T USE)
Doesn't work currently because of https://github.com/arduino/Arduino/issues/1476
Checks via i2c if there's a device at the default BNO055 address.

*/


// Guard

#ifndef __CREATE_FRAME__
#define __CREATE_FRAME__

// Dependencies

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//#include "utils.h"

// Functions

bool jReadLen( Adafruit_BNO055::adafruit_bno055_reg_t reg , byte * buffer, uint8_t len);

void createFrame( byte sensor_id, byte * imu_frame );

bool isBNO055Connected();

// End guard
#endif