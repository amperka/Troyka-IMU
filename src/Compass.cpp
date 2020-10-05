#include "Compass.h"

LIS3MDL::LIS3MDL(uint8_t addr)
    : BaseIMU(addr) { }

void LIS3MDL::begin(TwoWire& wire) {
    _wire = &wire;
    _wire->begin();
    // устанавливаем чувствительность
    setRange(RANGE_4_GAUSS);
    _writeByte(CTRL_REG3, _ctrlReg3);
}

void LIS3MDL::setRange(uint8_t range) {
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
    } break;
    }
    _writeByte(CTRL_REG2, _ctrlReg2);
}

void LIS3MDL::sleep(bool enable) {
    if (enable)
        _ctrlReg3 |= (3 << 0);
    else
        _ctrlReg3 &= ~(3 << 0);

    _writeByte(CTRL_REG3, _ctrlReg3);
}

float LIS3MDL::readGaussX() { return readX() / _mult; }

float LIS3MDL::readGaussY() { return readY() / _mult; }

float LIS3MDL::readGaussZ() { return readZ() / _mult; }

float LIS3MDL::readCalibrateX() {
    calibrate();
    return _xCalibrate;
}

float LIS3MDL::readCalibrateY() {
    calibrate();
    return _yCalibrate;
}

float LIS3MDL::readCalibrateZ() {
    calibrate();
    return _zCalibrate;
}

float LIS3MDL::readCalibrateGaussX() { return readCalibrateX() / _mult; }

float LIS3MDL::readCalibrateGaussY() { return readCalibrateY() / _mult; }

float LIS3MDL::readCalibrateGaussZ() { return readCalibrateZ() / _mult; }

void LIS3MDL::calibrate() {
    float result[3] = { 0, 0, 0 };
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

void LIS3MDL::calibrateMatrix(const double calibrationMatrix[3][3],
                              const double bias[3]) {
    memcpy(_bias, bias, 3 * sizeof(double));
    memcpy(_calibrationMatrix, calibrationMatrix, 3 * 3 * sizeof(double));
}

void LIS3MDL::readCalibrateGaussXYZ(float& x, float& y, float& z) {
    calibrate();
    x = _xCalibrate / _mult;
    y = _yCalibrate / _mult;
    z = _zCalibrate / _mult;
}

float LIS3MDL::readAzimut() {
    calibrate();
    float heading = atan2(_yCalibrate, _xCalibrate);

    if (heading < 0)
        heading += TWO_PI;
    else if (heading > TWO_PI)
        heading -= TWO_PI;
    float headingDegrees = heading * RAD_TO_DEG;
    return headingDegrees;
}
