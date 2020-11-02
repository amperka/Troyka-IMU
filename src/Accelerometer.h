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

// Gravity of Earth
constexpr float GRAVITY_EARTH = 9.8;

// Sensor sensitivity depending on selectable full scales
// Use the datasheet for details
constexpr float SENS_2G = 1 * 4 / pow(2, 16);
constexpr float SENS_4G = 2 * 4 / pow(2, 16);
constexpr float SENS_8G = 3.9 * 4 / pow(2, 16);

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
    // DEPRECATED fuctions
    // Use readAccelerationGX instead
    float readGX() { return readAccelerationGX(); }
    // Use readAccelerationGY instead
    float readGY() { return readAccelerationGY(); }
    // Use readAccelerationGZ instead
    float readGZ() { return readAccelerationGZ(); }
    // Use readAccelerationAX instead
    float readAX() { return readAccelerationAX(); }
    // Use readAccelerationAY instead
    float readAY() { return readAccelerationAY(); }
    // Use readAccelerationAZ instead
    float readAZ() { return readAccelerationAZ(); }
    // Use readAccelerationGXYZ instead
    void readGXYZ(float* ax, float* ay, float* az) {
        readAccelerationGXYZ(*ax, *ay, *az);
    }
    // Use readAccelerationAXYZ instead
    void readAXYZ(float* ax, float* ay, float* az) {
        readAccelerationAXYZ(*ax, *ay, *az);
    }

private:
    float _scalingFactor;
};

#endif // __ACCELEROMETER_H__
