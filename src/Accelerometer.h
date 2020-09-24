#ifndef __ACCELEROMETER_H__
#define __ACCELEROMETER_H__

#include "IMU.h"

#define LIS331DLH_ADDRESS     0b0011000
#define LIS331DLH_ADDRESS_V2  0b0011001

#define RANGE_2G        2
#define RANGE_4G        4
#define RANGE_8G        8

class LIS331DLH : public IMU
{
public:
    LIS331DLH(uint8_t addr = LIS331DLH_ADDRESS);
    void begin();
    void sleep(bool enable);
    void setRange(uint8_t range);
    float readGX();
    float readGY();
    float readGZ();
    float readAX();
    float readAY();
    float readAZ();
    void readGXYZ(float *ax, float *ay, float *az);
    void readAXYZ(float *gx, float *gy, float *gz);
};

#endif // __ACCELEROMETER_H__
