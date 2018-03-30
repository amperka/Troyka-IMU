#ifndef LIS3MDL_H
#define LIS3MDL_H

#include "stmhw.h"

#define LIS3MDL_TWI_ADDRESS     0b0011100
#define LIS3MDL_TWI_ADDRESS_V2  0b0011110

#define RANGE_4_GAUSS           0
#define RANGE_8_GAUSS           1
#define RANGE_12_GAUSS          2
#define RANGE_16_GAUSS          3

class LIS3MDL_TWI : public AxisHw
{
public:
    LIS3MDL_TWI(uint8_t addr = LIS3MDL_TWI_ADDRESS);
    void begin();
    void sleep(bool enable);
    void setRange(uint8_t range);
    void calibrateMatrix(const double calibrationMatrix[3][3], const double bias[3]);
    void calibrate();
    float readGaussX();
    float readGaussY();
    float readGaussZ();
    float readCalibrateX();
    float readCalibrateY();
    float readCalibrateZ();
    float readCalibrateGaussX();
    float readCalibrateGaussY();
    float readCalibrateGaussZ();
    float readAzimut();
    void readCalibrateGaussXYZ(float *x, float *y, float *z);

private:
    float _xCalibrate;
    float _yCalibrate;
    float _zCalibrate;
    double _calibrationMatrix[3][3];
    double _bias[3];
};

#endif
