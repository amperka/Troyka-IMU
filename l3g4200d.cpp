
#include <Arduino.h>
#include <Wire.h>

#include "l3g4200d.h"


#define CTRL_REG1       0x20
#define CTRL_REG1_PD    (1 << 3)

#define CTRL_REG4       0x23

#define OUT_X           0x29
#define OUT_Y           0x2B
#define OUT_Z           0x2D

#define ADR_FS_250     0x00
#define ADR_FS_500     0x10
#define ADR_FS_2000    0x20

#define SENS_FS_250        0.00875
#define SENS_FS_500        0.0175
#define SENS_FS_2000       0.07

L3G4200D_TWI::L3G4200D_TWI(uint8_t addr)
{
    _addr = addr;

    _ctrlReg1 = 0x3; // default according to datasheet
}

void L3G4200D_TWI::setRange(uint8_t range)
{
    switch (range) {
        case RANGE_250: {
            _ctrlReg4 = ADR_FS_250;
            _mult = SENS_FS_250;
            break;
        }
        case RANGE_500: {
            _ctrlReg4 = ADR_FS_500;
            _mult = SENS_FS_500;
            break;
        }
        case RANGE_2000: {
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

void L3G4200D_TWI::begin()
{
    Wire.begin();
    _mult = SENS_FS_250;
    sleep(false);
}


void L3G4200D_TWI::sleep(bool enable)
{
    if (enable)
        _ctrlReg1 &= ~CTRL_REG1_PD;
    else
        _ctrlReg1 |= CTRL_REG1_PD;

    writeCtrlReg1();
}

int16_t L3G4200D_TWI::readX()
{

    return readAxis(OUT_X);
}

int16_t L3G4200D_TWI::readY()
{
    return readAxis(OUT_Y);
}

int16_t L3G4200D_TWI::readZ()
{
    return readAxis(OUT_Z);
}

float L3G4200D_TWI::readX_DegPerSec()
{
    return readX()*_mult;
}

float L3G4200D_TWI::readY_DegPerSec()
{
    return readY()*_mult;
}

float L3G4200D_TWI::readZ_DegPerSec()
{
    return readZ()*_mult;
}

int16_t L3G4200D_TWI::readAxis(uint8_t reg)
{
    return (int16_t)readByte(reg) << 8 | readByte(reg - 1);
}

uint8_t L3G4200D_TWI::readByte(uint8_t reg)
{
    Wire.beginTransmission(_addr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(_addr, 1u);
    while (!Wire.available())
        ;
    return Wire.read();
}

void L3G4200D_TWI::writeCtrlReg1()
{
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG1);
    Wire.write(_ctrlReg1);
    Wire.endTransmission();
}

void L3G4200D_TWI::writeCtrlReg4()
{
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG4);
    Wire.write(_ctrlReg4);
    Wire.endTransmission();
}