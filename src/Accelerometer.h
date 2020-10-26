#ifndef __ACCELEROMETER_H__
#define __ACCELEROMETER_H__

#include "BaseIMU.h"

constexpr auto LIS331DLH_CTRL_REG4_FS0 = 0x10;
constexpr auto LIS331DLH_CTRL_REG4_FS1 = 0x20;

constexpr auto GRAVITY_EARTH = 9.8;

enum class AccelerometerRange { RANGE_2G = 2, RANGE_4G = 4, RANGE_8G = 8 };

constexpr float SENS_2G = 1;
constexpr float SENS_4G = 2;
constexpr float SENS_8G = 3.9;

class LIS331DLH : public BaseIMU {
public:
    LIS331DLH(uint8_t slaveAddress);
    enum class ScaleRange;
    void begin(TwoWire& wire = Wire);
    void sleep(bool state);
    void setRange(AccelerometerRange range);
    float readAccelerationGX();
    float readAccelerationGY();
    float readAccelerationGZ();
    float readAccelerationAX();
    float readAccelerationAY();
    float readAccelerationAZ();
    void readAccelerationGXYZ(float& ax, float& ay, float& az);
    void readAccelerationAXYZ(float& ax, float& ay, float& az);

private:
    float _scalingFactor;
};

#endif // __ACCELEROMETER_H__
