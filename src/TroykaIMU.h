#include "Accelerometer.h"
#include "Barometer.h"
#include "Compass.h"
#include "Gyroscope.h"
#include "MadgwickAHRS.h"

// Accelerometer
#define ACCEL_ADDRESS_V1 LIS331DLH_ADDRESS
#define ACCEL_ADDRESS_V2 LIS331DLH_ADDRESS_V2

// Gyroscope
#define GYRO_ADDRESS_V1 L3G4200D_ADDRESS
#define GYRO_ADDRESS_V2 L3G4200D_ADDRESS_V2

// Compass
#define COMPASS_ADDRESS_V1 LIS3MDL_ADDRESS
#define COMPASS_ADDRESS_V2 LIS3MDL_ADDRESS_V2

// Barometer
#define BARO_ADDRESS_V1 LPS331AP_ADDRESS
#define BARO_ADDRESS_V2 LPS331AP_ADDRESS_V2

class Accelerometer : public LIS331DLH {
public:
    Accelerometer(uint8_t slaveAddress = ACCEL_ADDRESS_V1)
        : LIS331DLH(slaveAddress) { }
};

class Gyroscope : public L3G4200D {
public:
    Gyroscope(uint8_t slaveAddress = GYRO_ADDRESS_V1)
        : L3G4200D(slaveAddress) { }
};

class Compass : public LIS3MDL {
public:
    Compass(uint8_t slaveAddress = COMPASS_ADDRESS_V1)
        : LIS3MDL(slaveAddress) { }
};

class Barometer : public LPS331 {
public:
    Barometer(uint8_t slaveAddress = BARO_ADDRESS_V1)
        : LPS331(slaveAddress) { }
};
