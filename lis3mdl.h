#ifndef LIS3MDL_H
#define LIS3MDL_H

#define LIS3MDL_TWI_ADDRESS 0b0011100

#define RANGE_4_GAUSS   0
#define RANGE_8_GAUSS   1
#define RANGE_12_GAUSS  2
#define RANGE_16_GAUSS  3

class LIS3MDL_TWI
{
public:
    LIS3MDL_TWI(uint8_t addr = LIS3MDL_TWI_ADDRESS);

    void begin();
    void setRange(uint8_t range);
    void calibrateMatrix(const double calibrationMatrix[3][3], const double bias[3]);
    void calibrate();
    uint8_t readByte(uint8_t reg);
    int16_t readX();
    int16_t readY();
    int16_t readZ();
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
    uint8_t _addr;
    float _mult;
    float _xCalibrate;
    float _yCalibrate;
    float _zCalibrate;
    uint8_t _ctrlReg1;
    uint8_t _ctrlReg2;
    uint8_t _ctrlReg3;
    uint8_t _ctrlReg4;
    uint8_t _ctrlReg5;
    double _calibrationMatrix[3][3];
    double _bias[3];
    void writeCtrlReg1();
    void writeCtrlReg2();
    void writeCtrlReg3();
    void writeCtrlReg4();
    void writeCtrlReg5();
    int16_t readAxis(uint8_t reg);
};

#endif
