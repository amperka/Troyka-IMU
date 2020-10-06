#include "Accelerometer.h"

LIS331DLH::LIS331DLH(uint8_t slaveAddress)
    : BaseIMU(slaveAddress) { }

void LIS331DLH::begin(TwoWire& wire) {
    _wire = &wire;
    _wire->begin();
    _ctrlReg1 |= (1 << 0);
    _ctrlReg1 |= (1 << 1);
    _ctrlReg1 |= (1 << 2);
    _ctrlReg1 |= (1 << 5);
    _writeByte(CTRL_REG1, _ctrlReg1);
    setRange(RANGE_2G);
}

void LIS331DLH::setRange(uint8_t range) {
    switch (range) {
    case RANGE_2G: {
        _ctrlReg4 = ADR_FS_2;
        _scale = RANGE_2G / 32767.0;
        break;
    }
    case RANGE_4G: {
        _ctrlReg4 = ADR_FS_4;
        _scale = RANGE_4G / 32767.0;
        break;
    }
    case RANGE_8G: {
        _ctrlReg4 = ADR_FS_8;
        _scale = RANGE_8G / 32767.0;
        break;
    }
    default: {
        _scale = RANGE_2G / 32767.0;
    } break;
    }
    _writeByte(CTRL_REG4, _ctrlReg4);
}

void LIS331DLH::sleep(bool state) {
    if (state)
        _ctrlReg1 &= ~(1 << 5);
    else
        _ctrlReg1 |= (1 << 5);

    _writeByte(CTRL_REG1, _ctrlReg1);
}

float LIS331DLH::readAccelerationGX() { return readX() * _scale; }

float LIS331DLH::readAccelerationGY() { return readY() * _scale; }

float LIS331DLH::readAccelerationGZ() { return readZ() * _scale; }

float LIS331DLH::readAccelerationAX() { return readAccelerationGX() * G; }

float LIS331DLH::readAccelerationAY() { return readAccelerationGY() * G; }

float LIS331DLH::readAccelerationAZ() { return readAccelerationGZ() * G; }

void LIS331DLH::readAccelerationGXYZ(float& ax, float& ay, float& az) {
    int16_t x, y, z;
    readXYZ(x, y, z);
    ax = x * _scale;
    ay = y * _scale;
    az = z * _scale;
}

void LIS331DLH::readAccelerationAXYZ(float& ax, float& ay, float& az) {
    readAccelerationGXYZ(ax, ay, az);
    ax *= G;
    ay *= G;
    az *= G;
}
