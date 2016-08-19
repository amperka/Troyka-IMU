#include <Arduino.h>
#include <Wire.h>
#include "l3g4200d.h"

#define CTRL_REG1       0x20
#define CTRL_REG2       0x21
#define CTRL_REG3       0x22
#define CTRL_REG4       0x23
#define CTRL_REG5       0x24

#define OUT_X           0x28
#define OUT_Y           0x2A
#define OUT_Z           0x2C

#define ADR_FS_250      0x00
#define ADR_FS_500      0x10
#define ADR_FS_2000     0x20

#define SENS_FS_250     0.00875
#define SENS_FS_500     0.0175
#define SENS_FS_2000    0.07

L3G4200D_TWI::L3G4200D_TWI(uint8_t addr) {
    _addr = addr;
}

void L3G4200D_TWI::setRange(uint8_t range) {
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
        }
        break;
    }
    writeCtrlReg4();
}

void L3G4200D_TWI::begin() {
    // подключаемся к шине I²C
    Wire.begin();
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


void L3G4200D_TWI::sleep(bool enable) {
    if (enable)
        _ctrlReg1 &= ~(1 << 3);
    else
        _ctrlReg1 |= (1 << 3);

    writeCtrlReg1();
}

int16_t L3G4200D_TWI::readX() {
    return readAxis(OUT_X);
}

int16_t L3G4200D_TWI::readY() {
    return readAxis(OUT_Y);
}

int16_t L3G4200D_TWI::readZ() {
    return readAxis(OUT_Z);
}

float L3G4200D_TWI::readDegPerSecX() {
    return readX() * _mult;
}

float L3G4200D_TWI::readDegPerSecY() {
    return readY() * _mult;
}

float L3G4200D_TWI::readDegPerSecZ() {
    return readZ() * _mult;
}

float L3G4200D_TWI::readRadPerSecX() {
    return readX() * _mult * DEG_TO_RAD;
}

float L3G4200D_TWI::readRadPerSecY() {
    return readY() * _mult * DEG_TO_RAD;
}

float L3G4200D_TWI::readRadPerSecZ() {
    return readZ() * _mult * DEG_TO_RAD;
}

void L3G4200D_TWI::readXYZ(int16_t *x, int16_t *y, int16_t *z) {
    Wire.beginTransmission(_addr);
    Wire.write(OUT_X | (1 << 7));  // assert MSB to enable register address auto-increment
    Wire.endTransmission();
    Wire.requestFrom(_addr, (uint8_t)6);
    uint8_t values[6];
    for (uint8_t i = 0; i < 6; i++) {
        values[i] = Wire.read();
    }
    Wire.endTransmission();
    
    *x = (((int16_t)values[1] << 8) | values[0]);
    *y = (((int16_t)values[3] << 8) | values[2]);
    *z = (((int16_t)values[5] << 8) | values[4]);
}

void L3G4200D_TWI::readDegPerSecXYZ(float *gx, float *gy, float *gz) {
    int16_t x, y, z;
    readXYZ(&x, &y, &z);
    *gx = (float)x * _mult;
    *gy = (float)y * _mult;
    *gz = (float)z * _mult;
}

void L3G4200D_TWI::readRadPerSecXYZ(float *gx, float *gy, float *gz) {
    int16_t x, y, z;
    readXYZ(&x, &y, &z);
    *gx = (float)x * _mult * DEG_TO_RAD;
    *gy = (float)y * _mult * DEG_TO_RAD;
    *gz = (float)z * _mult * DEG_TO_RAD;
}

int16_t L3G4200D_TWI::readAxis(uint8_t reg) {
    return (((int16_t)readByte(reg + 1) << 8) | readByte(reg));
}

uint8_t L3G4200D_TWI::readByte(uint8_t reg) {
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

void L3G4200D_TWI::writeCtrlReg1() {
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG1);
    Wire.write(_ctrlReg1);
    Wire.endTransmission();
}

void L3G4200D_TWI::writeCtrlReg2() {
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG2);
    Wire.write(_ctrlReg2);
    Wire.endTransmission();
}

void L3G4200D_TWI::writeCtrlReg3() {
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG3);
    Wire.write(_ctrlReg3);
    Wire.endTransmission();
}

void L3G4200D_TWI::writeCtrlReg4() {
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG4);
    Wire.write(_ctrlReg4);
    Wire.endTransmission();
}

void L3G4200D_TWI::writeCtrlReg5() {
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG5);
    Wire.write(_ctrlReg5);
    Wire.endTransmission();
}
