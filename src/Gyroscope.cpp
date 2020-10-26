#include "Gyroscope.h"

L3G4200D::L3G4200D(uint8_t slaveAddress)
    : BaseIMU(slaveAddress) { }

void L3G4200D::begin(TwoWire& wire) {
    _wire = &wire;
    _wire->begin();
    _ctrlReg1 |= (1 << 0) | (1 << 2) | (1 << 3) | (1 << 4);
    _writeByte(CTRL_REG1, _ctrlReg1);
    setRange(GyroscopeRange::RANGE_2000DPS);
}

void L3G4200D::setRange(GyroscopeRange range) {
    switch (range) {
    case GyroscopeRange::RANGE_250DPS: {
        _ctrlReg4 = 0;
        _scalingFactor = SENS_250DPS;
        break;
    }
    case GyroscopeRange::RANGE_500DPS: {
        _ctrlReg4 = L3G4200D_CTRL_REG4_FS0;
        _scalingFactor = SENS_500DPS;
        break;
    }
    case GyroscopeRange::RANGE_2000DPS: {
        _ctrlReg4 = L3G4200D_CTRL_REG4_FS0 | L3G4200D_CTRL_REG4_FS1;
        _scalingFactor = SENS_2000DPS;
        break;
    }
    default: {
        _scalingFactor = SENS_250DPS;
    } break;
    }
    _writeByte(CTRL_REG4, _ctrlReg4);
}

void L3G4200D::sleep(bool state) {
    if (state) {
        _ctrlReg1 &= ~(1 << 3);
    } else {
        _ctrlReg1 |= (1 << 3);
    }
    _writeByte(CTRL_REG1, _ctrlReg1);
}

float L3G4200D::readRotationDegX() { return readX() * _scalingFactor; }

float L3G4200D::readRotationDegY() { return readY() * _scalingFactor; }

float L3G4200D::readRotationDegZ() { return readZ() * _scalingFactor; }

float L3G4200D::readRotationRadX() { return readRotationDegX() * DEG_TO_RAD; }

float L3G4200D::readRotationRadY() { return readRotationDegY() * DEG_TO_RAD; }

float L3G4200D::readRotationRadZ() { return readRotationDegZ() * DEG_TO_RAD; }

void L3G4200D::readRotationDegXYZ(float& gx, float& gy, float& gz) {
    int16_t x, y, z;
    readXYZ(x, y, z);
    gx = x * _scale;
    gy = y * _scale;
    gz = z * _scale;
}

void L3G4200D::readRotationRadXYZ(float& gx, float& gy, float& gz) {
    readRotationDegXYZ(gx, gy, gz);
    gx *= DEG_TO_RAD;
    gy *= DEG_TO_RAD;
    gz *= DEG_TO_RAD;
}
