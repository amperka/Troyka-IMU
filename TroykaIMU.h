#include <Wire.h>
#include "lis331dlh.h"
#include "l3g4200d.h"
#include "lis3mdl.h"
#include "LPS331.h"
#include "MadgwickAHRS.h"

// Accelerometer
#define ACCEL_ADDRESS_V1    LIS331DLH_TWI_ADDRESS
#define ACCEL_ADDRESS_V2    LIS331DLH_TWI_ADDRESS_V2

// Gyroscope
#define GYRO_ADDRESS_V1     L3G4200D_TWI_ADDRESS
#define GYRO_ADDRESS_V2     L3G4200D_TWI_ADDRESS_V2

// Compass
#define COMPASS_ADDRESS_V1  LIS3MDL_TWI_ADDRESS
#define COMPASS_ADDRESS_V2  LIS3MDL_TWI_ADDRESS_V2

// Barometer
#define BARO_ADDRESS_V1     LPS331AP_TWI_ADDRESS
#define BARO_ADDRESS_V2     LPS331AP_TWI_ADDRESS_V2

class Accelerometer : public LIS331DLH_TWI
{
  public:
    Accelerometer(uint8_t addr = ACCEL_ADDRESS_V1) :
	  LIS331DLH_TWI(addr) {}
};

class Gyroscope : public L3G4200D_TWI
{
  public:
    Gyroscope(uint8_t addr = GYRO_ADDRESS_V1) : 
	  L3G4200D_TWI(addr) {}
};

class Compass : public LIS3MDL_TWI
{
  public:
    Compass(uint8_t addr = COMPASS_ADDRESS_V1) :
      LIS3MDL_TWI(addr) {}
};

class Barometer : public LPS331
{
  public:
    Barometer(uint8_t addr = BARO_ADDRESS_V1) :
      LPS331(addr) {}
};
