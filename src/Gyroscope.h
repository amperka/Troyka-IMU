#ifndef __GYROSCOPE_H__
#define __GYROSCOPE_H__

#include "BaseIMU.h"

constexpr auto L3G4200D_CTRL_REG4_FS0 = 0x10;
constexpr auto L3G4200D_CTRL_REG4_FS1 = 0x20;

enum class GyroscopeRange {
    RANGE_250DPS = 1,
    RANGE_500DPS = 2,
    RANGE_2000DPS = 3
};

constexpr float SENS_250DPS = 0.00875;
constexpr float SENS_500DPS = 0.0175;
constexpr float SENS_2000DPS = 0.07;

class L3G4200D : public BaseIMU {
public:
    L3G4200D(uint8_t slaveAddress);
    void begin(TwoWire& wire = Wire);
    void sleep(bool state);
    void setRange(GyroscopeRange range);
    float readRotationDegX();
    float readRotationDegY();
    float readRotationDegZ();
    float readRotationRadX();
    float readRotationRadY();
    float readRotationRadZ();
    void readRotationDegXYZ(float& gx, float& gy, float& gz);
    void readRotationRadXYZ(float& gx, float& gy, float& gz);

private:
    float _scalingFactor;
};

#endif // __GYROSCOPE_H__
