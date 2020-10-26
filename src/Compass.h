#ifndef __COMPASS_H__
#define __COMPASS_H__

#include "BaseIMU.h"

constexpr auto LIS3MDL_CTRL_REG2_FS0 = 0x20;
constexpr auto LIS3MDL_CTRL_REG2_FS1 = 0x40;

enum class CompassRange {
    RANGE_4GAUSS = 1,
    RANGE_8GAUSS = 2,
    RANGE_12GAUSS = 3,
    RANGE_16GAUSS = 4
};

constexpr float SENS_4GAUSS = 6842;
constexpr float SENS_8GAUSS = 3421;
constexpr float SENS_12GAUSS = 2281;
constexpr float SENS_16GAUSS = 1711;

class LIS3MDL : public BaseIMU {
public:
    LIS3MDL(uint8_t slaveAddress);
    void begin(TwoWire& wire = Wire);
    void sleep(bool state);
    void setRange(CompassRange range);
    float readMagneticGaussX();
    float readMagneticGaussY();
    float readMagneticGaussZ();
    void readCalibrateMagneticGaussXYZ(float& mx, float& my, float& mz);
    void readMagneticGaussXYZ(float& mx, float& my, float& mz);
    void setCalibrateMatrix(const float calibrationMatrix[3][3],
                            const float bias[3]);
    float readAzimut();

private:
    void _calibrate(float& mx, float& my, float& mz);
    float _calibrationMatrix[3][3];
    float _calibrationBias[3];
    float _scalingFactor;
};

#endif // __COMPASS_H__
