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
    LIS331DLH(uint8_t addr = LIS331DLH_ADDRESS);
    void begin(TwoWire &wire = Wire);
    void sleep(bool enable);
    void setRange(uint8_t range);
    float readGX();
    float readGY();
    float readGZ();
    float readAX();
    float readAY();
    float readAZ();
    void readGXYZ(float& ax, float& ay, float& az);
    void readAXYZ(float& gx, float& gy, float& gz);
};

#endif // __ACCELEROMETER_H__
