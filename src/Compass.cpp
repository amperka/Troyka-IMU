#include "Compass.h"

LIS3MDL::LIS3MDL(uint8_t slaveAddress)
    : BaseIMU(slaveAddress) { }

void LIS3MDL::begin(TwoWire& wire) {
    _wire = &wire;
    _wire->begin();
    _writeByte(CTRL_REG3, _ctrlReg3);
    setRange(RANGE_4_GAUSS);
}

void LIS3MDL::setRange(uint8_t range) {
    switch (range) {
    case RANGE_4_GAUSS: {
        _ctrlReg2 = ADR_FS_4;
        _scale = SENS_FS_4;
        break;
    }
    case RANGE_8_GAUSS: {
        _ctrlReg2 = ADR_FS_8;
        _scale = SENS_FS_8;
        break;
    }
    case RANGE_12_GAUSS: {
        _ctrlReg2 = ADR_FS_12;
        _scale = SENS_FS_12;
        break;
    }
    case RANGE_16_GAUSS: {
        _ctrlReg2 = ADR_FS_16;
        _scale = SENS_FS_16;
        break;
    }
    default: {
        _scale = SENS_FS_4;
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

float LIS3MDL::readMagneticGaussX() { return readX() / _scale; }

float LIS3MDL::readMagneticGaussY() { return readY() / _scale; }

float LIS3MDL::readMagneticGaussZ() { return readZ() / _scale; }

void LIS3MDL::readMagneticGaussXYZ(float& mx, float& my, float& mz) {
    int16_t x, y, z;
    readXYZ(x, y, z);
    mx = x / _scale;
    my = y / _scale;
    mz = z / _scale;
}

void LIS3MDL::readCalibrateMagneticGaussXYZ(float& mx, float& my, float& mz) {
    int16_t x, y, z;
    readXYZ(x, y, z);
    _calibrate((float&)x, (float&)y, (float&)z);
    mx = x / _scale;
    my = y / _scale;
    mz = z / _scale;
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
            calibrationValues[i] += _calibrationMatrix[i][j] * nonCalibrationValues[j];
        }
    }

    x = calibrationValues[0];
    y = calibrationValues[1];
    z = calibrationValues[2];
}

float LIS3MDL::readAzimut() {
    float x = readX();
    float y = readY();
    float z = readZ();
    _calibrate(x, y, z);
    float heading = atan2(x, y);

    if (heading < 0)
        heading += TWO_PI;
    else if (heading > TWO_PI)
        heading -= TWO_PI;
    float headingDegrees = heading * RAD_TO_DEG;
    return headingDegrees;
}
