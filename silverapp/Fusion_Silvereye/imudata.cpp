// v 2016-10-31 21:43

// changed how the bool is generated (added != 0 for onlinestatus)
// added bool return to provide signature checking
// added size argument to check if incoming data is ok
// fixed scaling issues in all platforms
// fixed scaling issues (needed extra int16_t casting)
// fixed wrong callib order
// frame 2.0

#include <stdint.h>
#include "imudata.h"

// #include <Arduino.h> // Uncomment to have access to HEX (in Arduino) when debugging frame

bool decodeFrame(const char* inputData, const int inputSize, ImuData* outputData)
{

	/*-----------------------------------------------------------------
	* Signature checking
	*
	* Bytes with index [28] and [29] contain a signature (0xFF 0x0A)
	*
	* If the signature doesn't match, return false in order to avoid
	*  reading data from an unintended system.
	*-----------------------------------------------------------------*/

	if( inputSize == 30 )
	{
		// If the inputSize is 30 we must have a valid signature to proceeed
		//  (decoder is either PC or memcopier Arduino)

		if(  ( ((uint8_t)inputData[28]) != 255 ) &&	( ((uint8_t)inputData[29]) != 10 ) )
		{
			return false;
		}
	}

	else if( inputSize != 28 )

	{
		// If the decoder is an Arduino that doesn't add signature (ex a sensor Arduino),
		//   it will ask to decode 28 bytes.
		// We let 28 bytes continue, any other size is likely an error.

		return false;
	}

	/*

	Considerations to decode the frame:


	Signed and unsigned conversion:


	"If you cast from a smaller signed integral type to a larger signed
	integral type, copies of the original most significant bit (1 in
	the case of a negative number) will be prepended as necessary to
	preserve the integer's value."
									-Mike DeSimone

	http://stackoverflow.com/questions/4218465/when-does-casting-change-a-values-bits-in-c

	For unsigned:

	uint8_t  8  -> 0000 1000.  If cast to uint16_t -> 0000 0000 0000 1000
	uint8_t 255 -> 1111 1111.  If cast to uint16_t -> 0000 0000 1111 1111

	"... when converting to an unsigned integer, only the value of the input matters, not its type."

	Storing a negative value as an uint stores its two's complement representation

	uint8_t -8 -> 1111 1000. If cast to uint16_t -> 1111 1111 1111 1000
					   (248)

	For signed:

	int8_t  8 -> 0000 1000.  If cast to uint16_t -> 0000 0000 0000 1000
	int8_t -8 -> 1111 1000.  If cast to uint16_t... 1111 1111 1111 1000

	-------------------------------------------------------------------
	[W] WARNING !!
	-------------------------------------------------------------------
	Casting (uint16_t) to a const char seems equivalent to:

	(uint16_t)
			  (int8_t)
					   data
	... implying that theres an implicit const char -> SIGNED cast
	when dealing with members of the const char* inputData array.

	As the choice of reading as a signed  seems to be platform dependent,
	cast uint8_t to every acquired array member when signs are a concern
	before promoting their size (joining bytes with OR for example).

	*/

	// x-> is syntactic sugar for (*x).

	// ABCD EFGH

	// Sensor ID
	outputData->id      = (unsigned char) ( (inputData[0]>>4) & 15 ); // 0000ABCD

	// Sensor status
	outputData->online  = (bool) ( ( (inputData[0] & 8) >> 3 ) != 0 ) ;   // 0000000E (!=0 to make it a bool)

	// Battery
	outputData->battery = (unsigned char) ( inputData[0] & 7 );       // 00000FGH

	// TO-DO: decode from levels to voltage

//	switch( gato.battery )
//	{
//		case 5:
//			// do stuff
//		break;
//	}

	// Callibration values
	// Endianness doesn't matter here only a byte is being read.

	outputData->callibration.system = (unsigned char) ( (inputData[1] >> 6) & 3 );
	outputData->callibration.gyr    = (unsigned char) ( (inputData[1] >> 4) & 3 );
	outputData->callibration.acc    = (unsigned char) ( (inputData[1] >> 2) & 3 );
	outputData->callibration.mag    = (unsigned char) ( inputData[1] & 3 );

	//qDebug() << gato.callibration.system << gato.callibration.acc << gato.callibration.mag << gato.callibration.gyr;

	// [1] Temp variables to do the joining and int16_t cast:

	int16_t w,x,y,z;
	w = x = y = z = 0;

	/*

	// When inputData[X] is cast as int16_t directly
	// an implicit conversion occurs. See [W].

	// MSB: Preserve the original sign with a signed type because the
	//      physical variables (and thus our results) are signed.
	//
	// This appends ones to the left if the actual size > 16 and when shifing

	// LSB: CAST AS UNSIGNED so there's no autofill with 1s to the left
	//      when expanding (as this would interfere with the OR operation).
	//
	// Could use a mask, both solutions should be independent of the underlying size!
	// Here uint8_t is implicitly promoted to int16_t do the bitwise op,
	// but it's value isn't changed.

	// Endianness doesn't matter, all bitwise operations and shifts in C/C++
	// are in "logical order" (MSB ... LSB)

	*/

	// Accelerometer

	const double acc_lsb = 100.0;

	x = ( ((int16_t)inputData[3]) << 8 ) | ( (uint8_t)inputData[2] );
	y = ( ((int16_t)inputData[5]) << 8 ) | ( (uint8_t)inputData[4] );
	z = ( ((int16_t)inputData[7]) << 8 ) | ( (uint8_t)inputData[6] );

	outputData->accelerometer.x = ( (double)x )/acc_lsb;
	outputData->accelerometer.y = ( (double)y )/acc_lsb;
	outputData->accelerometer.z = ( (double)z )/acc_lsb;

	// Magnetometer

	const double mag_lsb = 16.0;

	x = ( ((int16_t)inputData[9] ) << 8 ) | ( (uint8_t)inputData[8]  );
	y = ( ((int16_t)inputData[11]) << 8 ) | ( (uint8_t)inputData[10] );
	z = ( ((int16_t)inputData[13]) << 8 ) | ( (uint8_t)inputData[12] );

	outputData->magnetometer.x = ( (double)x )/mag_lsb;
	outputData->magnetometer.y = ( (double)y )/mag_lsb;
	outputData->magnetometer.z = ( (double)z )/mag_lsb;

	// Gyroscope

	const double gyr_lsb = 900.0;

	x = ( ((int16_t)inputData[15]) << 8 ) | ( (uint8_t)inputData[14] );
	y = ( ((int16_t)inputData[17]) << 8 ) | ( (uint8_t)inputData[16] );
	z = ( ((int16_t)inputData[19]) << 8 ) | ( (uint8_t)inputData[18] );

	outputData->gyroscope.x = ( (double)x )/gyr_lsb;
	outputData->gyroscope.y = ( (double)y )/gyr_lsb;
	outputData->gyroscope.z = ( (double)z )/gyr_lsb;

	// Quaternions

	const double quat_scale = (1.0 / (1<<14));

	// Same idea as above

	w = ( ((int16_t)inputData[21]) << 8 ) | ( (uint8_t)inputData[20] );
	x = ( ((int16_t)inputData[23]) << 8 ) | ( (uint8_t)inputData[22] );
	y = ( ((int16_t)inputData[25]) << 8 ) | ( (uint8_t)inputData[24] );
	z = ( ((int16_t)inputData[27]) << 8 ) | ( (uint8_t)inputData[26] );

	// Implicit (double) promotion of w x y z because quat_scale is double

	outputData->quaternion.w = w * quat_scale;
	outputData->quaternion.x = x * quat_scale;
	outputData->quaternion.y = y * quat_scale;
	outputData->quaternion.z = z * quat_scale;

	// Print bytes in order to track errors.

	// bytes sample in monospace:
	// idcaax  ay  az  mx  my  mz  gx  gy  gz  qw  qx  qy  qz
	// 1f30e6ff2d00d60300fdcaffd2fefeff00000000fb3f6b01db00fcff

	/*// Debug START

	Serial.print("DecodeFrame input bytes");
	Serial.println("");

	for( int i = 8 ; i <= 13 ; i++ ) //output
	//for(int i = 6 ; i <= 11; i++) input
	{
		Serial.print("Byte ");
		Serial.print(i,DEC);
		Serial.print(": ");
		Serial.print( inputData[i] , HEX ); //output
		Serial.println("");
	}

	Serial.println("");

	// Debug END*/

	return true;

}
