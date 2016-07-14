#include <Wire.h>
#include "lis331dlh.h"
#include "l3g4200d.h"
#include "lis3mdl.h"
#include "LPS331.h"
#include "MadgwickAHRS.h"

class Accelerometer : public LIS331DLH_TWI
{

};

class Gyroscope : public L3G4200D_TWI
{
	
};

class Compass : public LIS3MDL_TWI
{
	
};

class Barometer : public LPS331
{
	
};