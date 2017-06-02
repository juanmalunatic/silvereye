// v 2016-09-14 21:43

// added size argument to check is incoming data is ok
// frame 2.0

#ifndef IMUDATA_H
#define IMUDATA_H

/*
 *  Dependencies
 */

#include <stdint.h>

/*
 *
 * Data structures
 *
 */

// Structure to store the callibration data

struct CallibData
{
	unsigned char system;
	unsigned char gyr;
	unsigned char mag;
	unsigned char acc;
};

struct Acc
{
	double x;
	double y;
	double z;
};

struct Mag
{
	double x;
	double y;
	double z;
};

struct Gyr
{
	double x;
	double y;
	double z;
};

struct Quat
{
	double w;
	double x;
	double y;
	double z;

};

// Needs the previously declared structs

struct ImuData
{
	// Basic info

	unsigned char id;
	bool online;
	unsigned char battery;

	// Callibration status

	CallibData callibration;

	// Sensor data

	Acc  accelerometer;
	Mag  magnetometer;
	Gyr  gyroscope;
	Quat quaternion;

};

/*
 * Functions
 *
 */

bool decodeFrame(const char* inputData, const int inputSize, ImuData* outputData);


#endif // IMUDATA_H
