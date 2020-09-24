#include "Gyroscope.h"

#define ADR_FS_250 0x00
#define ADR_FS_500 0x10
#define ADR_FS_2000 0x20

#define SENS_FS_250 0.00875
#define SENS_FS_500 0.0175
#define SENS_FS_2000 0.07

L3G4200D::L3G4200D(uint8_t addr)
    : IMU(addr) { }

void L3G4200D::setRange(uint8_t range) {
    switch (range) {
    case RANGE_250DPS: {
        _ctrlReg4 = ADR_FS_250;
        _mult = SENS_FS_250;
        break;
    }
    case RANGE_500DPS: {
        _ctrlReg4 = ADR_FS_500;
        _mult = SENS_FS_500;
        break;
    }
    case RANGE_2000DPS: {
        _ctrlReg4 = ADR_FS_2000;
        _mult = SENS_FS_2000;
        break;
    }
    default: {
        _mult = SENS_FS_250;
    } break;
    }
    writeCtrlReg4();
}

void L3G4200D::begin() {
    // подключаемся к шине I²C
    WIRE_IMU.begin();
    // включаем координаты x, y, z
    _ctrlReg1 |= (1 << 0);
    _ctrlReg1 |= (1 << 1);
    _ctrlReg1 |= (1 << 2);
    // включаем гироскоп
    _ctrlReg1 |= (1 << 3);
    // устанавливаем чувствительность
    setRange(RANGE_250DPS);
    writeCtrlReg1();
}

void L3G4200D::sleep(bool enable) {
    if (enable)
        _ctrlReg1 &= ~(1 << 3);
    else
        _ctrlReg1 |= (1 << 3);

    writeCtrlReg1();
}

float L3G4200D::readDegPerSecX() { return readX() * _mult; }

float L3G4200D::readDegPerSecY() { return readY() * _mult; }

float L3G4200D::readDegPerSecZ() { return readZ() * _mult; }

float L3G4200D::readRadPerSecX() { return readDegPerSecX() * DEG_TO_RAD; }

float L3G4200D::readRadPerSecY() { return readDegPerSecY() * DEG_TO_RAD; }

float L3G4200D::readRadPerSecZ() { return readDegPerSecZ() * DEG_TO_RAD; }

void L3G4200D::readDegPerSecXYZ(float* gx, float* gy, float* gz) {
    int16_t x, y, z;
    readXYZ(&x, &y, &z);
    *gx = x * _mult;
    *gy = y * _mult;
    *gz = z * _mult;
}

void L3G4200D::readRadPerSecXYZ(float* gx, float* gy, float* gz) {
    readDegPerSecXYZ(gx, gy, gz);
    (*gx) *= DEG_TO_RAD;
    (*gy) *= DEG_TO_RAD;
    (*gz) *= DEG_TO_RAD;
}
