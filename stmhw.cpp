#include "stmhw.h"
#include <Wire.h>

#define CTRL_REG1       0x20
#define CTRL_REG2       0x21
#define CTRL_REG3       0x22
#define CTRL_REG4       0x23
#define CTRL_REG5       0x24

#define OUT_X           0x28
#define OUT_Y           0x2A
#define OUT_Z           0x2C

int16_t AxisHw::readX() {
    return readAxis(OUT_X);
}

int16_t AxisHw::readY() {
    return readAxis(OUT_Y);
}

int16_t AxisHw::readZ() {
    return readAxis(OUT_Z);
}

int16_t AxisHw::readAxis(uint8_t reg) {
    return ((int16_t)readByte(reg + 1) << 8) | readByte(reg);
}

uint8_t AxisHw::readByte(uint8_t reg) {
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

void AxisHw::readXYZ(int16_t *x, int16_t *y, int16_t *z) {
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

void AxisHw::writeCtrlReg1(){
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG1);
    Wire.write(_ctrlReg1);
    Wire.endTransmission();
}

void AxisHw::writeCtrlReg2(){
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG2);
    Wire.write(_ctrlReg2);
    Wire.endTransmission();
}

void AxisHw::writeCtrlReg3(){
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG3);
    Wire.write(_ctrlReg3);
    Wire.endTransmission();
}

void AxisHw::writeCtrlReg4(){
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG4);
    Wire.write(_ctrlReg4);
    Wire.endTransmission();
}

void AxisHw::writeCtrlReg5(){
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG5);
    Wire.write(_ctrlReg5);
    Wire.endTransmission();
}
