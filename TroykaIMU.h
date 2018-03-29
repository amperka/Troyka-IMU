#include <Wire.h>
#include "lis331dlh.h"
#include "l3g4200d.h"
#include "lis3mdl.h"
#include "LPS331.h"
#include "MadgwickAHRS.h"

#define ACCEL_ADDRESS_V1    0b0011000
#define ACCEL_ADDRESS_V2    0b0011001

#define GYRO_ADDRESS_V1     0b01101000
#define GYRO_ADDRESS_V2     0b01101001

#define COMPASS_ADDRESS_V1  0b0011100
#define COMPASS_ADDRESS_V2  0b0011110

#define BARO_ADDRESS_V1     0b1011100
#define BARO_ADDRESS_V2     0b1011101


class Accelerometer : public LIS331DLH_TWI
{
	public:
		Accelerometer(uint8_t addr = LIS331DLH_TWI_ADDRESS) :
			LIS331DLH_TWI(addr) {}
};

class Gyroscope : public L3G4200D_TWI
{
	public:
		Gyroscope(uint8_t addr = L3G4200D_TWI_ADDRESS) : 
			L3G4200D_TWI(addr) {}
};

class Compass : public LIS3MDL_TWI
{
	public:
		Compass(uint8_t addr = LIS3MDL_TWI_ADDRESS) :
			LIS3MDL_TWI(addr) {}
};

class Barometer : public LPS331
{
	public:
		Barometer(uint8_t addr = LPS331AP_TWI_ADDRESS) :
			LPS331(addr) {}
};
