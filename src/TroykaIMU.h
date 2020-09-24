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
#define COMPASS_ADDRESS_V1 LIS3MDL_TWI_ADDRESS
#define COMPASS_ADDRESS_V2 LIS3MDL_TWI_ADDRESS_V2

// Barometer
#define BARO_ADDRESS_V1 LPS331AP_TWI_ADDRESS
#define BARO_ADDRESS_V2 LPS331AP_TWI_ADDRESS_V2

class Accelerometer : public LIS331DLH {
public:
    Accelerometer(uint8_t addr = ACCEL_ADDRESS_V1)
        : LIS331DLH(addr) { }
};

class Gyroscope : public L3G4200D {
public:
    Gyroscope(uint8_t addr = GYRO_ADDRESS_V1)
        : L3G4200D(addr) { }
};

class Compass : public LIS3MDL {
public:
    Compass(uint8_t addr = COMPASS_ADDRESS_V1)
        : LIS3MDL(addr) { }
};

class Barometer : public LPS331 {
public:
    Barometer(uint8_t addr = BARO_ADDRESS_V1)
        : LPS331(addr) { }
};
