#ifndef __ACCELEROMETER_H__
#define __ACCELEROMETER_H__

#include "BaseIMU.h"

// I²C-address device
constexpr uint8_t LIS331DLH_SLAVE_ADDRESS = 0x18;
constexpr uint8_t LIS331DLH_SLAVE_ADDRESS_ALT = 0x19;

// Registers addrress
constexpr uint8_t LIS331DLH_CTRL_REG4_FS0 = 0x10;
constexpr uint8_t LIS331DLH_CTRL_REG4_FS1 = 0x20;

// Registers value bits
constexpr uint8_t LIS331DLH_CTRL_REG1_X_EN = 0x01;
constexpr uint8_t LIS331DLH_CTRL_REG1_Y_EN = 0x02;
constexpr uint8_t LIS331DLH_CTRL_REG1_Z_EN = 0x04;
constexpr uint8_t LIS331DLH_CTRL_REG1_PM0 = 0x20;
constexpr uint8_t LIS331DLH_CTRL_REG1_PM1 = 0x40;
constexpr uint8_t LIS331DLH_CTRL_REG1_PM2 = 0x80;

// Constans
constexpr float GRAVITY_EARTH = 9.8;
constexpr float SENS_2G = 1;
constexpr float SENS_4G = 2;
constexpr float SENS_8G = 3.9;

enum class AccelerometerRange { RANGE_2G = 1, RANGE_4G = 2, RANGE_8G = 3 };

class Accelerometer : public BaseIMU {
public:
    Accelerometer(uint8_t slaveAddress = LIS331DLH_SLAVE_ADDRESS);
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
