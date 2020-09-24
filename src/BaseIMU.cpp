#include "BaseIMU.h"

#define CTRL_REG1       0x20
#define CTRL_REG2       0x21
#define CTRL_REG3       0x22
#define CTRL_REG4       0x23
#define CTRL_REG5       0x24

#define OUT_X           0x28
#define OUT_Y           0x2A
#define OUT_Z           0x2C

int16_t BaseIMU::readX() {
    return readAxis(OUT_X);
}

int16_t BaseIMU::readY() {
    return readAxis(OUT_Y);
}

int16_t BaseIMU::readZ() {
    return readAxis(OUT_Z);
}

int16_t BaseIMU::readAxis(uint8_t reg) {
    return ((int16_t)readByte(reg + 1) << 8) | readByte(reg);
}

void BaseIMU::waitForData() {
    while (_wire->available() < 1)
        continue;
}

uint8_t BaseIMU::readByte(uint8_t reg) {
    uint8_t value;
    _wire->beginTransmission(_addr);
    _wire->write(reg);
    _wire->endTransmission();
    _wire->requestFrom(_addr, 1u);
    waitForData();
    value = _wire->read();
    return value;
}

void BaseIMU::readXYZ(int16_t *x, int16_t *y, int16_t *z) {
    _wire->beginTransmission(_addr);
    _wire->write(OUT_X | (1 << 7));  // assert MSB to enable register address auto-increment
    _wire->endTransmission();

    uint8_t burstSize = 6;
    _wire->requestFrom(_addr, burstSize);
    uint8_t values[burstSize];
    for (uint8_t i = 0; i < burstSize; i++) {
        waitForData();
        values[i] = _wire->read();
    }
    
    *x = *((int16_t*)&values[0]);
    *y = *((int16_t*)&values[2]);
    *z = *((int16_t*)&values[4]);
}

void BaseIMU::writeCtrlReg1(){
    _wire->beginTransmission(_addr);
    _wire->write(CTRL_REG1);
    _wire->write(_ctrlReg1);
    _wire->endTransmission();
}

void BaseIMU::writeCtrlReg2(){
    _wire->beginTransmission(_addr);
    _wire->write(CTRL_REG2);
    _wire->write(_ctrlReg2);
    _wire->endTransmission();
}

void BaseIMU::writeCtrlReg3(){
    _wire->beginTransmission(_addr);
    _wire->write(CTRL_REG3);
    _wire->write(_ctrlReg3);
    _wire->endTransmission();
}

void BaseIMU::writeCtrlReg4(){
    _wire->beginTransmission(_addr);
    _wire->write(CTRL_REG4);
    _wire->write(_ctrlReg4);
    _wire->endTransmission();
}

void BaseIMU::writeCtrlReg5(){
    _wire->beginTransmission(_addr);
    _wire->write(CTRL_REG5);
    _wire->write(_ctrlReg5);
    _wire->endTransmission();
}
