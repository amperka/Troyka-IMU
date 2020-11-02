#include "Compass.h"

Compass::Compass(uint8_t slaveAddress)
    : BaseIMU(slaveAddress) { }

void Compass::begin(TwoWire& wire) {
    _wire = &wire;
    _wire->begin();
    _scalingFactor = 1;
    uint8_t data = 0;
    data &= ~(LIS3MDL_CTRL_REG3_MD0 | LIS3MDL_CTRL_REG3_MD1);
    _writeByte(BASE_IMU_CTRL_REG3, data);
    setRange(CompassRange::RANGE_4GAUSS);
}

void Compass::setRange(CompassRange range) {
    uint8_t data = _readByte(BASE_IMU_CTRL_REG2);
    data &= ~(LIS3MDL_CTRL_REG2_FS0 | LIS3MDL_CTRL_REG2_FS1);
    switch (range) {
    case CompassRange::RANGE_4GAUSS: {
        _scalingFactor = SENS_4GAUSS;
        break;
    }
    case CompassRange::RANGE_8GAUSS: {
        data |= LIS3MDL_CTRL_REG2_FS0;
        _scalingFactor = SENS_8GAUSS;
        break;
    }
    case CompassRange::RANGE_12GAUSS: {
        data |= LIS3MDL_CTRL_REG2_FS1;
        _scalingFactor = SENS_12GAUSS;
        break;
    }
    case CompassRange::RANGE_16GAUSS: {
        data |= LIS3MDL_CTRL_REG2_FS0 | LIS3MDL_CTRL_REG2_FS1;
        _scalingFactor = SENS_16GAUSS;
        break;
    }
    default: {
        _scalingFactor = SENS_4GAUSS;
    } break;
    }
    _writeByte(BASE_IMU_CTRL_REG2, data);
}

void Compass::sleep(bool state) {
    uint8_t data = _readByte(BASE_IMU_CTRL_REG3);
    if (state)
        data |= LIS3MDL_CTRL_REG3_MD0 | LIS3MDL_CTRL_REG3_MD1;
    else
        data &= ~(LIS3MDL_CTRL_REG3_MD0 | LIS3MDL_CTRL_REG3_MD1);

    _writeByte(BASE_IMU_CTRL_REG3, data);
}

float Compass::readMagneticGaussX() { return readX() / _scalingFactor; }

float Compass::readMagneticGaussY() { return readY() / _scalingFactor; }

float Compass::readMagneticGaussZ() { return readZ() / _scalingFactor; }

void Compass::readMagneticGaussXYZ(float& mx, float& my, float& mz) {
    int16_t x, y, z;
    readXYZ(x, y, z);
    mx = x / _scalingFactor;
    my = y / _scalingFactor;
    mz = z / _scalingFactor;
}

void Compass::readCalibrateMagneticGaussXYZ(float& mx, float& my, float& mz) {
    int16_t x, y, z;
    readXYZ(x, y, z);
    mx = x, my = y, mz = z;
    _calibrate(mx, my, mz);
    mx = x / _scalingFactor;
    my = y / _scalingFactor;
    mz = z / _scalingFactor;
}

void Compass::setCalibrateMatrix(const float calibrationMatrix[3][3],
                                 const float calibrationBias[3]) {
    memcpy(_calibrationBias, calibrationBias, 3 * sizeof(float));
    memcpy(_calibrationMatrix, calibrationMatrix, 3 * 3 * sizeof(float));
}

void Compass::_calibrate(float& x, float& y, float& z) {
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

float Compass::readAzimut() {
    int16_t x, y, z;
    readXYZ(x, y, z);
    float mx = x, my = y, mz = z;
    _calibrate(mx, my, mz);
    float heading = atan2(mx, my);
    if (heading < 0) {
        heading += TWO_PI;
    }
    float headingDegrees = heading * RAD_TO_DEG;
    return headingDegrees;
}
