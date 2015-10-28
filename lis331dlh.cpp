
#include <Arduino.h>
#include <Wire.h>

#include "lis331dlh.h"


#define CTRL_REG1       0x20
#define CTRL_REG1_PM    (1 << 5)

#define CTRL_REG4       0x23

#define OUT_X           0x28
#define OUT_Y           0x2A
#define OUT_Z           0x2C

#define ADR_FS_2        0x00
#define ADR_FS_4        0x10
#define ADR_FS_8        0x30

#define SENS_FS_2       0.001
#define SENS_FS_4       0.002
#define SENS_FS_8       0.0039

LIS331DLH_TWI::LIS331DLH_TWI(uint8_t addr)
{
    _addr = addr;

    _ctrlReg1 = 0x7; // default according to datasheet
}

void LIS331DLH_TWI::begin()
{
    Wire.begin();
    setRange(RANGE_2);
    sleep(false);

    _freeFallAcceleration = 9.8;
}

void LIS331DLH_TWI::setRange(uint8_t range)
{
    switch (range) {
        case RANGE_2: {
            _ctrlReg4 = ADR_FS_2;
            _mult = SENS_FS_2;
            break;
        }
        case RANGE_4: {
            _ctrlReg4 = ADR_FS_4;
            _mult = SENS_FS_4;
            break;
        }
        case RANGE_8: {
            _ctrlReg4 = ADR_FS_8;
            _mult = SENS_FS_8;
            break;
        }
        default: {
        _mult = SENS_FS_8;    
        }
        break;
    }
    writeCtrlReg4();
}
void LIS331DLH_TWI::sleep(bool enable)
{
    if (enable)
        _ctrlReg1 &= ~CTRL_REG1_PM;
    else
        _ctrlReg1 |= CTRL_REG1_PM;

    writeCtrlReg1();
}


int16_t LIS331DLH_TWI::readX()
{
    return readAxis(OUT_X);
}

int16_t LIS331DLH_TWI::readY()
{
    return readAxis(OUT_Y);
}

int16_t LIS331DLH_TWI::readZ()
{
    return readAxis(OUT_Z);
}

float LIS331DLH_TWI::readX_G()
{
    return readX()*_mult*_freeFallAcceleration;
}

float LIS331DLH_TWI::readY_G()
{
    return readY()*_mult*_freeFallAcceleration;
}

float LIS331DLH_TWI::readZ_G()
{
    return readZ()*_mult*_freeFallAcceleration;
}

int16_t LIS331DLH_TWI::readAxis(uint8_t reg)
{
    Wire.beginTransmission(_addr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(_addr, 1);
    while (Wire.available() < 1)
        ;
    uint8_t lowByte = Wire.read();

    ++reg;

    Wire.beginTransmission(_addr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(_addr, 1);
    while (Wire.available() < 1)
        ;
    uint8_t highByte = Wire.read();

    return (((int16_t)highByte << 8) | lowByte) >> 4;
}

void LIS331DLH_TWI::writeCtrlReg1()
{
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG1);
    Wire.write(_ctrlReg1);
    Wire.endTransmission();
}

void LIS331DLH_TWI::writeCtrlReg4()
{
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG4);
    Wire.write(_ctrlReg4);
    Wire.endTransmission();
}