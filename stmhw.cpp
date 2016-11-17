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

inline void AxisHw::waitForData() {
    while (WIRE_IMU.available() < 1)
        continue;
}

uint8_t AxisHw::readByte(uint8_t reg) {
    uint8_t value;
    WIRE_IMU.beginTransmission(_addr);
    WIRE_IMU.write(reg);
    WIRE_IMU.endTransmission();
    WIRE_IMU.requestFrom(_addr, 1u);
    waitForData();
    value = WIRE_IMU.read();
    return value;
}

void AxisHw::readXYZ(int16_t *x, int16_t *y, int16_t *z) {
    WIRE_IMU.beginTransmission(_addr);
    WIRE_IMU.write(OUT_X | (1 << 7));  // assert MSB to enable register address auto-increment
    WIRE_IMU.endTransmission();

    uint8_t burstSize = 6;
    WIRE_IMU.requestFrom(_addr, burstSize);
    uint8_t values[burstSize];
    for (uint8_t i = 0; i < burstSize; i++) {
        waitForData();
        values[i] = WIRE_IMU.read();
    }
    
    *x = *((int16_t*)&values[0]);
    *y = *((int16_t*)&values[2]);
    *z = *((int16_t*)&values[4]);
}

void AxisHw::writeCtrlReg1(){
    WIRE_IMU.beginTransmission(_addr);
    WIRE_IMU.write(CTRL_REG1);
    WIRE_IMU.write(_ctrlReg1);
    WIRE_IMU.endTransmission();
}

void AxisHw::writeCtrlReg2(){
    WIRE_IMU.beginTransmission(_addr);
    WIRE_IMU.write(CTRL_REG2);
    WIRE_IMU.write(_ctrlReg2);
    WIRE_IMU.endTransmission();
}

void AxisHw::writeCtrlReg3(){
    WIRE_IMU.beginTransmission(_addr);
    WIRE_IMU.write(CTRL_REG3);
    WIRE_IMU.write(_ctrlReg3);
    WIRE_IMU.endTransmission();
}

void AxisHw::writeCtrlReg4(){
    WIRE_IMU.beginTransmission(_addr);
    WIRE_IMU.write(CTRL_REG4);
    WIRE_IMU.write(_ctrlReg4);
    WIRE_IMU.endTransmission();
}

void AxisHw::writeCtrlReg5(){
    WIRE_IMU.beginTransmission(_addr);
    WIRE_IMU.write(CTRL_REG5);
    WIRE_IMU.write(_ctrlReg5);
    WIRE_IMU.endTransmission();
}
