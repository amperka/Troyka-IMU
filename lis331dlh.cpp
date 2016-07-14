#include <Arduino.h>
#include <Wire.h>
#include "./lis331dlh.h"

#define CTRL_REG1       0x20
#define CTRL_REG2       0x21
#define CTRL_REG3       0x22
#define CTRL_REG4       0x23
#define CTRL_REG5       0x24

#define OUT_X           0x28
#define OUT_Y           0x2A
#define OUT_Z           0x2C

#define ADR_FS_2        0x00
#define ADR_FS_4        0x10
#define ADR_FS_8        0x30

#define G               9.8

LIS331DLH_TWI::LIS331DLH_TWI(uint8_t addr) {
    _addr = addr;
}

void LIS331DLH_TWI::begin() {
    // подключаемся к шине I²C
    Wire.begin();
    // включаем координаты x, y, z
    _ctrlReg1 |= (1 << 0);
    _ctrlReg1 |= (1 << 1);
    _ctrlReg1 |= (1 << 2);
    // включаем аксселерометр
    _ctrlReg1 |= (1 << 5);
    // устанавливаем максимальное измеряемое ускорение в G
    setRange(RANGE_2G);
    writeCtrlReg1();
}

void LIS331DLH_TWI::setRange(uint8_t range) {
    switch (range) {
        case RANGE_2G: {
            _ctrlReg4 = ADR_FS_2;
            _mult = RANGE_2G / 32767.0;
            break;
        }
        case RANGE_4G: {
            _ctrlReg4 = ADR_FS_4;
            _mult = RANGE_4G / 32767.0;
            break;
        }
        case RANGE_8G: {
            _ctrlReg4 = ADR_FS_8;
            _mult = RANGE_8G / 32767.0;
            break;
        }
        default: {
            _mult = RANGE_2G / 32767.0;
        }
        break;
    }
    writeCtrlReg4();
}

void LIS331DLH_TWI::sleep(bool enable) {
    if (enable)
        _ctrlReg1 &= ~(1 << 5);
    else
        _ctrlReg1 |= (1 << 5);

    writeCtrlReg1();
}

int16_t LIS331DLH_TWI::readX() {
    return readAxis(OUT_X);
}

int16_t LIS331DLH_TWI::readY() {
    return readAxis(OUT_Y);
}

int16_t LIS331DLH_TWI::readZ() {
    return readAxis(OUT_Z);
}

float LIS331DLH_TWI::readGX() {
    return readX()*_mult;
}

float LIS331DLH_TWI::readGY() {
    return readY()*_mult;
}

float LIS331DLH_TWI::readGZ() {
    return readZ()*_mult;
}

float LIS331DLH_TWI::readAX() {
    return readX()*_mult * G;
}

float LIS331DLH_TWI::readAY() {
    return readY() * _mult * G;
}

float LIS331DLH_TWI::readAZ() {
    return readZ() * _mult * G;
}

void LIS331DLH_TWI::readXYZ(int16_t *x, int16_t *y, int16_t *z) {
    Wire.beginTransmission(_addr);
    // assert MSB to enable register address auto-increment
    Wire.write(OUT_X | (1 << 7));
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

void LIS331DLH_TWI::readGXYZ(float *gx, float *gy, float *gz) {
    int16_t x, y, z;
    readXYZ(&x, &y, &z);
    *gx = static_cast<float>(x) * _mult;
    *gy = static_cast<float>(y) * _mult;
    *gz = static_cast<float>(z) * _mult;
}

void LIS331DLH_TWI::readAXYZ(float *ax, float *ay, float *az) {
    int16_t x, y, z;
    readXYZ(&x, &y, &z);
    *ax = static_cast<float>(x) * _mult * G;
    *ay = static_cast<float>(y) * _mult * G;
    *az = static_cast<float>(z) * _mult * G;
}

int16_t LIS331DLH_TWI::readAxis(uint8_t reg) {
    return (((int16_t)readByte(reg + 1) << 8) | readByte(reg));
}

uint8_t LIS331DLH_TWI::readByte(uint8_t reg) {
    uint8_t value = 0;
    Wire.beginTransmission(_addr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(_addr, (uint8_t)1);
    while (Wire.available() < 1) {
    }
    value = Wire.read();
    Wire.endTransmission();
    return value;
}

void LIS331DLH_TWI::writeCtrlReg1() {
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG1);
    Wire.write(_ctrlReg1);
    Wire.endTransmission();
}

void LIS331DLH_TWI::writeCtrlReg2() {
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG2);
    Wire.write(_ctrlReg2);
    Wire.endTransmission();
}

void LIS331DLH_TWI::writeCtrlReg3() {
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG3);
    Wire.write(_ctrlReg3);
    Wire.endTransmission();
}

void LIS331DLH_TWI::writeCtrlReg4() {
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG4);
    Wire.write(_ctrlReg4);
    Wire.endTransmission();
}

void LIS331DLH_TWI::writeCtrlReg5() {
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG5);
    Wire.write(_ctrlReg5);
    Wire.endTransmission();
}
