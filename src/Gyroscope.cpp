#include "Gyroscope.h"

L3G4200D::L3G4200D(uint8_t slaveAddress)
    : BaseIMU(slaveAddress) { }

void L3G4200D::setRange(uint8_t range) {
    switch (range) {
    case RANGE_250DPS: {
        _ctrlReg4 |= ADR_FS_250;
        _scale = SENS_FS_250;
        break;
    }
    case RANGE_500DPS: {
        _ctrlReg4 |= ADR_FS_500;
        _scale = SENS_FS_500;
        break;
    }
    case RANGE_2000DPS: {
        _ctrlReg4 |= ADR_FS_2000;
        _scale = SENS_FS_2000;
        break;
    }
    default: {
        _scale = SENS_FS_250;
    } break;
    }
    _writeByte(CTRL_REG4, _ctrlReg4);
}

void L3G4200D::begin(TwoWire& wire) {
    _wire = &wire;
    _wire->begin();
    _ctrlReg1 |= (1 << 0) | (1 << 2) | (1 << 3) | (1 << 4);
    _writeByte(CTRL_REG1, _ctrlReg1);
    setRange(RANGE_250DPS);
}

void L3G4200D::sleep(bool state) {
    if (state) {
        _ctrlReg1 &= ~(1 << 3);
    } else {
        _ctrlReg1 |= (1 << 3);
    }
    _writeByte(CTRL_REG1, _ctrlReg1);
}

float L3G4200D::readRotationDegX() { return readX() * _scale; }

float L3G4200D::readRotationDegY() { return readY() * _scale; }

float L3G4200D::readRotationDegZ() { return readZ() * _scale; }

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
