#ifndef __COMPASS_H__
#define __COMPASS_H__

#include "BaseIMU.h"

#define LIS3MDL_ADDRESS 0b0011100
#define LIS3MDL_ADDRESS_V2 0b0011110

#define RANGE_4_GAUSS 0
#define RANGE_8_GAUSS 1
#define RANGE_12_GAUSS 2
#define RANGE_16_GAUSS 3

#define ADR_FS_4 0x00
#define ADR_FS_8 0x20
#define ADR_FS_12 0x40
#define ADR_FS_16 0x60

#define SENS_FS_4 6842
#define SENS_FS_8 3421
#define SENS_FS_12 2281
#define SENS_FS_16 1711

class LIS3MDL : public BaseIMU {
public:
    LIS3MDL(uint8_t slaveAddress = LIS3MDL_ADDRESS);
    void begin(TwoWire& wire = Wire);
    void sleep(bool state);
    void setRange(uint8_t range);
    float readMagneticGaussX();
    float readMagneticGaussY();
    float readMagneticGaussZ();
    void readMagneticGaussXYZ(float& x, float& y, float& z);
    void readCalibrateMagneticGaussXYZ(float& x, float& y, float& z);
    void setCalibrateMatrix(const float calibrationMatrix[3][3],
                            const float bias[3]);
    float readAzimut();


private:
    void _calibrate(float& x, float& y, float& z);
    float _calibrationMatrix[3][3];
    float _calibrationBias[3];
};

#endif // __COMPASS_H__
