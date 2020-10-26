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
    setRange(AccelerometerRange::RANGE_2G);
}

void LIS331DLH::setRange(AccelerometerRange range) {
    switch (range) {
    case AccelerometerRange::RANGE_2G: {
        _ctrlReg4 = 0;
        _scalingFactor = SENS_2G * 4 / pow(2, 16);
        break;
    }
    case AccelerometerRange::RANGE_4G: {
        _ctrlReg4 = LIS331DLH_CTRL_REG4_FS0;
        _scalingFactor = SENS_4G * 4 / pow(2, 16);
        break;
    }
    case AccelerometerRange::RANGE_8G: {
        _ctrlReg4 = LIS331DLH_CTRL_REG4_FS0 | LIS331DLH_CTRL_REG4_FS1;
        _scalingFactor = SENS_8G * 4 / pow(2, 16);
        break;
    }
    default: {
        _scalingFactor = SENS_2G * 4 / pow(2, 16);
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

float LIS331DLH::readAccelerationGX() { return readX() * _scalingFactor; }

float LIS331DLH::readAccelerationGY() { return readY() * _scalingFactor; }

float LIS331DLH::readAccelerationGZ() { return readZ() * _scalingFactor; }

float LIS331DLH::readAccelerationAX() {
    return readAccelerationGX() * GRAVITY_EARTH;
}

float LIS331DLH::readAccelerationAY() {
    return readAccelerationGY() * GRAVITY_EARTH;
}

float LIS331DLH::readAccelerationAZ() {
    return readAccelerationGZ() * GRAVITY_EARTH;
}

void LIS331DLH::readAccelerationGXYZ(float& ax, float& ay, float& az) {
    int16_t x, y, z;
    readXYZ(x, y, z);
    ax = x * _scalingFactor;
    ay = y * _scalingFactor;
    az = z * _scalingFactor;
}

void LIS331DLH::readAccelerationAXYZ(float& ax, float& ay, float& az) {
    readAccelerationGXYZ(ax, ay, az);
    ax *= GRAVITY_EARTH;
    ay *= GRAVITY_EARTH;
    az *= GRAVITY_EARTH;
}
