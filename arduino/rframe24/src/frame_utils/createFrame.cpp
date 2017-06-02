/*
	Reads the BNO055 sensor and formats the frame.
*/

// v 2016-09-21

// added a function to check the BNO055 avaliability, which doesn't work :)
// removed all serial.print instances
// added a (commented) debug code to print bytes (and compare them with the original lib).
// changed frame to v2.0 (add online indicator and change battery levels)

// Dependencies
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include "createFrame.h"

void createFrame( byte sensor_id, byte * imu_frame )  // same as byte * imu_frame[27] 
{
	// Frame structure is created in the main loop and passed as a pointer.
		
	// [frame] Create the frame's structure: 28 bytes
	// byte imu_frame[28];
	
	//*****************************************************************
	// [frame_id ] Byte 0: Sensor ID and battery status	
	//*****************************************************************
	
	imu_frame[0] = B00000000;  // We start with a blank register
	
	// The valid sensorId range is 1 - 15
	// If this is not the case, the ID field will be B1111XXXX
	// and collisions with legitimate nodes may occur
	
	if( (sensor_id < 1) || (sensor_id > 15) )
	{	
		imu_frame[0] = imu_frame[0] | (B11110000);	
	}
	else
	{
		imu_frame[0] = imu_frame[0] | (sensor_id << 4);
	}     
	
	// Signal that, as we're sending a frame, we are online
	//                                   |
	//                                   v 
	imu_frame[0] = imu_frame[0] | ( B00001000 );
	
	//*****************************************************************
	// [frame_bat] Battery info
	//*****************************************************************

	// TO-DO: Reading takes about 450us -.- unacceptable!
	
	// .~\Arduino15\packages\adafruit\hardware\samd\1.0.13
	// .~\Arduino15\packages\arduino\tools\CMSIS\4.0.0-atmel\Device\ATMEL\samd21\include\component
	// https://msdn.microsoft.com/en-us/library/64973255.aspx para adc.h
	// http://forum.arduino.cc/index.php?topic=396831.0;nowap
	// https://forum.arduino.cc/index.php?topic=341345.0
	
	// Timing debug
	/*unsigned long bat_start;
	unsigned long bat_stop;
	
	bat_start = micros();*/

    int adcbat = analogRead(A7);
	
	// Curve fitting for 4.2 -> 100% and 3 -> 0% : m=83.33 b=-250
	// In practice we have 3 bits and we use the direct ADC readings 
	// (Voltage=ADC*3.3*2/1024): 
	/*		  
	 Batt % |  0*  14  29  43  57  71  86 100
	Voltage	|   3                         4.2
	    ADC | 465 492 519 546 573 600 627 654
	Mapping | 000 001 010 011 100 101 110 111
	*/
	
	
	if( adcbat <= 465 )
	{
		// Do nothing as it was reset previously
	} 
	else if ( (adcbat > 465) && (adcbat < 492 ) )
	{ 
		imu_frame[0] = imu_frame[0] | (B00000001);
	} 
	else if ( (adcbat > 492) && (adcbat < 519 ) )
	{
		imu_frame[0] = imu_frame[0] | (B00000010);
	}
	else if ( (adcbat > 519) && (adcbat < 546 ) )
	{	
		imu_frame[0] = imu_frame[0] | (B00000011);
	}
	else if ( (adcbat > 546) && (adcbat < 573 ) )
	{	
		imu_frame[0] = imu_frame[0] | (B00000100);
	}
	else if ( (adcbat > 573) && (adcbat < 600 ) )
	{	
		imu_frame[0] = imu_frame[0] | (B00000101);
	}
	else if ( (adcbat > 600) && (adcbat < 627 ) )
	{
		imu_frame[0] = imu_frame[0] | (B00000110);
	}
	else if ( adcbat > 627 )
	{
		imu_frame[0] = imu_frame[0] | (B00000111);	
	};
	
	// Print timing for debug
	
	/*bat_stop = micros() - bat_start;	
    Serial.print("VBat: " ); Serial.println(adcbat);
	Serial.print("Frame[0]: "); Serial.println(imu_frame[0], BIN);
	Serial.print("us: "); Serial.println( bat_stop );*/
	
	//*****************************************************************
	// [frame_cal] Byte 1: Callibration 
	//*****************************************************************
	
	// This process is explained in the sensor's data formatting
	
	imu_frame[1] = B00000000; // Calibration register
	
	uint8_t buffer_cal[1];
	memset (buffer_cal, 0, 1); // http://www.cplusplus.com/reference/cstring/memset/
	
	jReadLen( Adafruit_BNO055::BNO055_CALIB_STAT_ADDR , buffer_cal, 1 ); 
	imu_frame[1] = (byte)buffer_cal[0]; 
	
	// Print acquired calibration for debugging
	/*Serial.println("");
	Serial.print("Frame[1]: ");
	print_binary( (int)imu_frame[1], 8); // in utils.h to have trailing zeros
	Serial.println("");*/

	//*****************************************************************
	// [frame_raw] Raw sensor data
	//*****************************************************************
	
	/*
	This method simply reads adjacent bytes from the sensor's registers,
	according to its datasheet. It is faster than the default method be-
	cause it doesn't involve scaling the acquired data (this task must
	be realized by the client).	It is also more suited for transmission
	because scaling involves casting raw values to a double type (taking
	more bytes).

	Worst time: 7ms. Average time: 4.6ms.
	
	TO-DO: We can try to further improve performance changing the clock
	stretch limit (L62 Adafruit_BNO055.cpp)
	*/

	// Starting from ACC_DATA_X_LSB, we read 18 bytes
	// Buffer to read 18 bytes over the serial connection
	
	uint8_t buffer[18];
	memset (buffer, 0, 18); // http://www.cplusplus.com/reference/cstring/memset/
	
	/*
	This is a "public" implementation of Adafruit_BNO055's readLen
	method.	It is implemented as a separate file in order to pre-
	serve the original library unmodified (as this allows updating,
	extending, etc).
	*/	
	
	jReadLen( Adafruit_BNO055::BNO055_ACCEL_DATA_X_LSB_ADDR , buffer, 18 );   

	
	// Frame formatting.
	// The following code is verbose in case docs go missing :^)

	// Acelerómetro
	imu_frame[2] = (byte)buffer[0];  // Acc_X_lsb
	imu_frame[3] = (byte)buffer[1];  // Acc_X_msb
	imu_frame[4] = (byte)buffer[2];  // Acc_Y_lsb
	imu_frame[5] = (byte)buffer[3];  // ...
	imu_frame[6] = (byte)buffer[4];  // Acc_Z_...
	imu_frame[7] = (byte)buffer[5];  // ...

	// Magnetómetro
	imu_frame[8]  = (byte)buffer[6];  // Mag_X_lsb
	imu_frame[9]  = (byte)buffer[7];   
	imu_frame[10] = (byte)buffer[8];  // Mag_Y
	imu_frame[11] = (byte)buffer[9];
	imu_frame[12] = (byte)buffer[10]; // Mag_Z
	imu_frame[13] = (byte)buffer[11];
	
	/*// DEBUG START
	
	Serial.print("CreateFrame output bytes"); //output
	//Serial.print("CreateFrame input bytes"); //input
	Serial.println("");
	
	for( int i = 8 ; i <= 13 ; i++ ) //output
	//for(int i = 6 ; i <= 11; i++) input
	{
		Serial.print("Byte ");
		Serial.print(i,DEC);
		Serial.print(": ");
		Serial.print( imu_frame[i] , HEX ); //output
		//Serial.print( (byte)buffer[i] , HEX); //input
		Serial.println("");
	}
	
	Serial.println("");
	
	// DEBUG END*/
	
	//gyr
	imu_frame[14] = (byte)buffer[12]; // Gyr_X_lsb
	imu_frame[15] = (byte)buffer[13];
	imu_frame[16] = (byte)buffer[14]; // Gyr_Y
	imu_frame[17] = (byte)buffer[15];
	imu_frame[18] = (byte)buffer[16]; // Gyr_Z
	imu_frame[19] = (byte)buffer[17];
	
	//*****************************************************************
	// [frame_fsn] Raw sensor fusion data (Quaternions)
	//*****************************************************************

	//	Quaternion data starts at a different location (QUA_Data_w_LSB) and spans 8 bytes.

	//byte quat[8];
	uint8_t buffer2[8];
	memset (buffer2, 0, 8); 

	jReadLen( Adafruit_BNO055::BNO055_QUATERNION_DATA_W_LSB_ADDR , buffer2, 8);  

	// Cuaternios (Quats)

	imu_frame[20] = (byte)buffer2[0]; // Quat_W_lsb
	imu_frame[21] = (byte)buffer2[1];
	imu_frame[22] = (byte)buffer2[2]; // Quat_X
	imu_frame[23] = (byte)buffer2[3];
	imu_frame[24] = (byte)buffer2[4]; // Quat_Y
	imu_frame[25] = (byte)buffer2[5];
	imu_frame[26] = (byte)buffer2[6]; // Quat_Z
	imu_frame[27] = (byte)buffer2[7]; 

	/* Timing functions must go in the main thread 
	// Try to obtain as stable a framerate as possible :)
	unsigned long timesofar;
	timesofar = micros() - looptime;
	delayMicroseconds( BNO055_SAMPLERATE_DELAY_MS*1000 - timesofar - 15 ); // desired framerate. 15 microsecs ajuste heurístico
	*/
}


/**************************************************************************/
/*!
    @brief  Read the sensor via I2C at a fixed address. 
	        Almost identical to Adafruit_BNO055::readLen.
*/
/**************************************************************************/
bool jReadLen( Adafruit_BNO055::adafruit_bno055_reg_t reg , byte * buffer, uint8_t len)
{

	// Fixed address as we are targeting one board model. Edit this if other MCU is in use.

	//uint8_t _address = Adafruit_BNO055::BNO055_ADDRESS_A; //(0x28)
	uint8_t _address = 0x28;

	Wire.beginTransmission(_address);
	#if ARDUINO >= 100
		Wire.write((uint8_t)reg);
	#else
		Wire.send(reg);
	#endif
	
	Wire.endTransmission();
	Wire.requestFrom(_address, (byte)len);

	for (uint8_t i = 0; i < len; i++)
	{
		#if ARDUINO >= 100
		  buffer[i] = Wire.read();
		#else
		  buffer[i] = Wire.receive();
		#endif
	}

	/* ToDo: Check for errors! */
	return true;
}

bool isBNO055Connected()
{
	/*
	This function doesn't work currently due to an Arduino bug.
	*/
	
	// Based on http://playground.arduino.cc/Main/I2cScanner
		
	uint8_t _address = 0x28;
	Wire.beginTransmission(_address);
	
	byte error;
	error = Wire.endTransmission(false); 
	
	// arduino will always hang up here if there are no i2c devices
	// proposed solution involves using other library http://www.gammon.com.au/i2c
	
	// 	https://www.arduino.cc/en/Reference/WireEndTransmission
	if( error == 4 )
	{
		return false;		
	}
	else
	{
		return true;
	}
	
}