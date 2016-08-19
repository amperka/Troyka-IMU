#include <Arduino.h>
#include <Wire.h>
#include "lis3mdl.h"

#define CTRL_REG1       0x20
#define CTRL_REG2       0x21
#define CTRL_REG3       0x22
#define CTRL_REG4       0x23
#define CTRL_REG5       0x24

#define OUT_X           0x28
#define OUT_Y           0x2A
#define OUT_Z           0x2C

#define ADR_FS_4        0x00
#define ADR_FS_8        0x20
#define ADR_FS_12       0x40
#define ADR_FS_16       0x60

#define SENS_FS_4       6842
#define SENS_FS_8       3421
#define SENS_FS_12      2281
#define SENS_FS_16      1711

LIS3MDL_TWI::LIS3MDL_TWI(uint8_t addr) {
    _addr = addr;
}

void LIS3MDL_TWI::begin() {
    Wire.begin();
    // устанавливаем чувствительность
    setRange(RANGE_4_GAUSS);
    writeCtrlReg3();
}

void LIS3MDL_TWI::setRange(uint8_t range) {
    switch (range) {
        case RANGE_4_GAUSS: {
            _ctrlReg2 = ADR_FS_4;
            _mult = SENS_FS_4;
            break;
        }
        case RANGE_8_GAUSS: {
            _ctrlReg2 = ADR_FS_8;
            _mult = SENS_FS_8;
            break;
        }
        case RANGE_12_GAUSS: {
            _ctrlReg2 = ADR_FS_12;
            _mult = SENS_FS_12;
            break;
        }
        case RANGE_16_GAUSS: {
            _ctrlReg2 = ADR_FS_16;
            _mult = SENS_FS_16;
            break;
        }
        default: {
        _mult = SENS_FS_4;    
        }
        break;
    }
    writeCtrlReg2();
}

int16_t LIS3MDL_TWI::readX() {
    return readAxis(OUT_X);
}

int16_t LIS3MDL_TWI::readY() {
    return readAxis(OUT_Y);
}

int16_t LIS3MDL_TWI::readZ() {
    return readAxis(OUT_Z);
}

float LIS3MDL_TWI::readGaussX() {
    return readX() / _mult;
}

float LIS3MDL_TWI::readGaussY() {
    return readY() / _mult;
}

float LIS3MDL_TWI::readGaussZ() {
    return readZ() / _mult;
}

float LIS3MDL_TWI::readCalibrateX() {
    calibrate();
    return _xCalibrate;
}

float LIS3MDL_TWI::readCalibrateY() {
    calibrate();
    return _yCalibrate;
}

float LIS3MDL_TWI::readCalibrateZ() {
    calibrate();
    return _zCalibrate;
}

float LIS3MDL_TWI::readCalibrateGaussX() {
    return readCalibrateX()/_mult;
}

float LIS3MDL_TWI::readCalibrateGaussY() {
    return readCalibrateY()/_mult;
}

float LIS3MDL_TWI::readCalibrateGaussZ() {
    return readCalibrateZ()/_mult;
}

void LIS3MDL_TWI::calibrate() {
    float result[3] = {0, 0, 0};
    float uncalibratedValues[3];
    uncalibratedValues[0] = readX() - _bias[0];
    uncalibratedValues[1] = readY() - _bias[1];
    uncalibratedValues[2] = readZ() - _bias[2];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
        result[i] += _calibrationMatrix[i][j] * uncalibratedValues[j];
        }
    }

    _xCalibrate = result[0];
    _yCalibrate = result[1];
    _zCalibrate = result[2];
}

void LIS3MDL_TWI::calibrateMatrix(const double calibrationMatrix[3][3], const double bias[3]) {
    for(int i = 0; i < 3; i++)
        _bias[i] = bias[i];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
        _calibrationMatrix[i][j] = calibrationMatrix[i][j];
    }  
}

void LIS3MDL_TWI::readCalibrateGaussXYZ(float *x, float *y, float *z) {
    calibrate();
    *x = _xCalibrate;
    *y = _yCalibrate;
    *z = _zCalibrate;
}

float LIS3MDL_TWI::readAzimut() {
    calibrate();
    float heading = atan2(_yCalibrate, _xCalibrate);

    if(heading < 0)
        heading += TWO_PI;
    else if(heading > TWO_PI)
        heading -= TWO_PI;

    float headingDegrees = heading * RAD_TO_DEG;

    return headingDegrees;
}

int16_t LIS3MDL_TWI::readAxis(uint8_t reg) {
    return (((int16_t)readByte(reg + 1) << 8) | readByte(reg)) ;
}

uint8_t LIS3MDL_TWI::readByte(uint8_t reg) {
    uint8_t value = 0;
    Wire.beginTransmission(_addr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(_addr, (uint8_t)1);
    while (Wire.available() < 1)
        ;
    value = Wire.read();
    Wire.endTransmission();
    return value;
}

void LIS3MDL_TWI::writeCtrlReg1() {
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG1);
    Wire.write(_ctrlReg1);
    Wire.endTransmission();
}

void LIS3MDL_TWI::writeCtrlReg2() {
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG2);
    Wire.write(_ctrlReg2);
    Wire.endTransmission();
}

void LIS3MDL_TWI::writeCtrlReg3() {
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG3);
    Wire.write(_ctrlReg3);
    Wire.endTransmission();
}

void LIS3MDL_TWI::writeCtrlReg4() {
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG4);
    Wire.write(_ctrlReg4);
    Wire.endTransmission();
}

void LIS3MDL_TWI::writeCtrlReg5() {
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG5);
    Wire.write(_ctrlReg5);
    Wire.endTransmission();
}
