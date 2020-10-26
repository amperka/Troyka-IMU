#include "Compass.h"

LIS3MDL::LIS3MDL(uint8_t slaveAddress)
    : BaseIMU(slaveAddress) { }

void LIS3MDL::begin(TwoWire& wire) {
    _wire = &wire;
    _wire->begin();
    _writeByte(CTRL_REG3, _ctrlReg3);
    setRange(CompassRange::RANGE_16GAUSS);
}

void LIS3MDL::setRange(CompassRange range) {
    switch (range) {
    case CompassRange::RANGE_4GAUSS: {
        _ctrlReg2 = 0;
        _scalingFactor = SENS_4GAUSS;
        break;
    }
    case CompassRange::RANGE_8GAUSS: {
        _ctrlReg2 = LIS3MDL_CTRL_REG2_FS0;
        _scalingFactor = SENS_8GAUSS;
        break;
    }
    case CompassRange::RANGE_12GAUSS: {
        _ctrlReg2 = LIS3MDL_CTRL_REG2_FS1;
        _scalingFactor = SENS_12GAUSS;
        break;
    }
    case CompassRange::RANGE_16GAUSS: {
        _ctrlReg2 = LIS3MDL_CTRL_REG2_FS0 | LIS3MDL_CTRL_REG2_FS1;
        _scalingFactor = SENS_16GAUSS;
        break;
    }
    default: {
        _scalingFactor = SENS_4GAUSS;
    } break;
    }
    _writeByte(CTRL_REG2, _ctrlReg2);
}

void LIS3MDL::sleep(bool state) {
    if (state)
        _ctrlReg3 |= (3 << 0);
    else
        _ctrlReg3 &= ~(3 << 0);

    _writeByte(CTRL_REG3, _ctrlReg3);
}

float LIS3MDL::readMagneticGaussX() { return readX() / _scalingFactor; }

float LIS3MDL::readMagneticGaussY() { return readY() / _scalingFactor; }

float LIS3MDL::readMagneticGaussZ() { return readZ() / _scalingFactor; }

void LIS3MDL::readMagneticGaussXYZ(float& mx, float& my, float& mz) {
    int16_t x, y, z;
    readXYZ(x, y, z);
    mx = x / _scalingFactor;
    my = y / _scalingFactor;
    mz = z / _scalingFactor;
}

void LIS3MDL::readCalibrateMagneticGaussXYZ(float& mx, float& my, float& mz) {
    int16_t x, y, z;
    readXYZ(x, y, z);
    mx = x, my = y, mz = z;
    _calibrate(mx, my, mz);
    mx = x / _scalingFactor;
    my = y / _scalingFactor;
    mz = z / _scalingFactor;
}

void LIS3MDL::setCalibrateMatrix(const float calibrationMatrix[3][3],
                                 const float calibrationBias[3]) {
    memcpy(_calibrationBias, calibrationBias, 3 * sizeof(float));
    memcpy(_calibrationMatrix, calibrationMatrix, 3 * 3 * sizeof(float));
}

void LIS3MDL::_calibrate(float& x, float& y, float& z) {
    float calibrationValues[3] = { 0, 0, 0 };
    float nonCalibrationValues[3] = { 0, 0, 0 };
    nonCalibrationValues[0] = x - _calibrationBias[0];
    nonCalibrationValues[1] = y - _calibrationBias[1];
    nonCalibrationValues[2] = z - _calibrationBias[2];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            calibrationValues[i]
                += _calibrationMatrix[i][j] * nonCalibrationValues[j];
        }
    }

    x = calibrationValues[0];
    y = calibrationValues[1];
    z = calibrationValues[2];
}

float LIS3MDL::readAzimut() {
    int16_t x, y, z;
    readXYZ(x, y, z);
    float mx = x, my = y, mz = z;
    _calibrate(mx, my, mz);
    float heading = atan2(mx, my);

    if (heading < 0)
        heading += TWO_PI;
    else if (heading > TWO_PI)
        heading -= TWO_PI;
    float headingDegrees = heading * RAD_TO_DEG;
    return headingDegrees;
}
