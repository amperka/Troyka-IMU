#ifndef __ACCELEROMETER_H__
#define __ACCELEROMETER_H__

#include "BaseIMU.h"

#define LIS331DLH_ADDRESS 0b0011000
#define LIS331DLH_ADDRESS_V2 0b0011001

#define RANGE_2G 2
#define RANGE_4G 4
#define RANGE_8G 8

#define ADR_FS_2 0x00
#define ADR_FS_4 0x10
#define ADR_FS_8 0x30

#define G 9.8

class LIS331DLH : public BaseIMU {
public:
    LIS331DLH(uint8_t slaveAddress = LIS331DLH_ADDRESS);
    void begin(TwoWire &wire = Wire);
    void sleep(bool state);
    void setRange(uint8_t range);
    float readAccelerationGX();
    float readAccelerationGY();
    float readAccelerationGZ();
    float readAccelerationAX();
    float readAccelerationAY();
    float readAccelerationAZ();
    void readAccelerationGXYZ(float& ax, float& ay, float& az);
    void readAccelerationAXYZ(float& ax, float& ay, float& az);
};

#endif // __ACCELEROMETER_H__
