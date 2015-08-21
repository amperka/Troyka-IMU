
#include <Arduino.h>
#include <Wire.h>

#include "lis3mdl.h"


#define CTRL_REG1       0x20
#define CTRL_REG2       0x21
#define CTRL_REG3       0x22
#define CTRL_REG4       0x23
#define CTRL_REG5       0x24

#define OUT_X           0x28
#define OUT_Y           0x2A
#define OUT_Z           0x2C

#define ADR_FS_4        0x00
#define ADR_FS_8        0x20
#define ADR_FS_12       0x40
#define ADR_FS_16       0x60

#define SENS_FS_4       6842
#define SENS_FS_8       3421
#define SENS_FS_12      2281
#define SENS_FS_16      1711

LIS3MDL_TWI::LIS3MDL_TWI(uint8_t addr)
{
    _addr = addr;

    _ctrlReg1 = 0x0;
}

void LIS3MDL_TWI::begin()
{
    Wire.begin();

    Wire.beginTransmission(_addr);
    Wire.write(0x22);
    Wire.write(0);
    Wire.endTransmission();

    setRange(RANGE_4);
}

void LIS3MDL_TWI::setRange(uint8_t range)
{
    switch (range) {
        case RANGE_4: {
            _ctrlReg2 = ADR_FS_4;
            _mult = SENS_FS_4;
            break;
        }
        case RANGE_8: {
            _ctrlReg2 = ADR_FS_8;
            _mult = SENS_FS_8;
            break;
        }
        case RANGE_12: {
            _ctrlReg2 = ADR_FS_12;
            _mult = SENS_FS_12;
            break;
        }
        case RANGE_16: {
            _ctrlReg2 = ADR_FS_16;
            _mult = SENS_FS_16;
            break;
        }
        default: {
        _mult = SENS_FS_4;    
        }
        break;
    }
    writeCtrlReg2();
}

int16_t LIS3MDL_TWI::readX()
{
    return readAxis(OUT_X);
}

int16_t LIS3MDL_TWI::readY()
{
    return readAxis(OUT_Y);
}

int16_t LIS3MDL_TWI::readZ()
{
    return readAxis(OUT_Z);
}

float LIS3MDL_TWI::readX_Gauss()
{
    return readX()/_mult;
}

float LIS3MDL_TWI::readY_Gauss()
{
    return readY()/_mult;
}

float LIS3MDL_TWI::readZ_Gauss()
{
    return readZ()/_mult;
}

void LIS3MDL_TWI::readXYZ_Calib()
{
    double calibration_matrix[3][3] = 
    {
        {2.446, 0.074, 0.006},
        {0.07, 2.317, -0.006},
        {-0.027, -0.12, 2.458}  
    };

    double bias[3] = 
    {
        -1221.593,
        -2042.451,
        6497.221
    };

    float result[3] = {0, 0, 0};
    float uncalibrated_values[3];
    uncalibrated_values[0] = readX() - bias[0];
    uncalibrated_values[1] = readY() - bias[1];
    uncalibrated_values[2] = readZ() - bias[2];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
        result[i] += calibration_matrix[i][j] * uncalibrated_values[j];
        }
    }

    x_cal = result[0];
    y_cal = result[1];
    z_cal = result[2];
}

float LIS3MDL_TWI::read_Yaw()
{
    readXYZ_Calib();
    float heading = atan2(y_cal, x_cal);

    if(heading < 0)
    heading += 2*PI;

    if(heading > 2*PI)
    heading -= 2*PI;

    float headingDegrees = heading * 180/M_PI;

    return headingDegrees;
}
int16_t LIS3MDL_TWI::readAxis(uint8_t reg)
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

    return ((int16_t)highByte << 8) | lowByte;

}

void LIS3MDL_TWI::writeCtrlReg1()
{
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG1);
    Wire.write(_ctrlReg1);
    Wire.endTransmission();
}

void LIS3MDL_TWI::writeCtrlReg2()
{
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG2);
    Wire.write(_ctrlReg2);
    Wire.endTransmission();
}

void LIS3MDL_TWI::writeCtrlReg3()
{
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG3);
    Wire.write(_ctrlReg3);
    Wire.endTransmission();
}

void LIS3MDL_TWI::writeCtrlReg4()
{
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG3);
    Wire.write(_ctrlReg3);
    Wire.endTransmission();
}

void LIS3MDL_TWI::writeCtrlReg5()
{
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG5);
    Wire.write(_ctrlReg5);
    Wire.endTransmission();
}