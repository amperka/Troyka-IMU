#ifndef __TROYKA_IMU_H__
#define __TROYKA_IMU_H__

#include "Accelerometer.h"
#include "Barometer.h"
#include "Compass.h"
#include "Gyroscope.h"
#include "MadgwickAHRS.h"

class Accelerometer : public LIS331DLH {
public:
    Accelerometer(uint8_t slaveAddress = 0x18)
        : LIS331DLH(slaveAddress) { }
};

class Gyroscope : public L3G4200D {
public:
    Gyroscope(uint8_t slaveAddress = 0x68)
        : L3G4200D(slaveAddress) { }
};

class Compass : public LIS3MDL {
public:
    Compass(uint8_t slaveAddress = 0x1C)
        : LIS3MDL(slaveAddress) { }
};

class Barometer : public LPS331 {
public:
    Barometer(uint8_t slaveAddress = 0x5C)
        : LPS331(slaveAddress) { }
};

#endif // __TROYKA_IMU_H__