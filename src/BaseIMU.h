#ifndef __BaseIMU_H__
#define __BaseIMU_H__

#include <Arduino.h>
#include <Wire.h>

#define CTRL_REG1       0x20
#define CTRL_REG2       0x21
#define CTRL_REG3       0x22
#define CTRL_REG4       0x23
#define CTRL_REG5       0x24

#define OUT_X           0x28
#define OUT_Y           0x2A
#define OUT_Z           0x2C

class BaseIMU {
public:
    BaseIMU(uint8_t addr)
        : _addr(addr) { }
    int16_t readX();
    int16_t readY();
    int16_t readZ();
    void readXYZ(int16_t& x, int16_t& y, int16_t& z);

protected:
    TwoWire* _wire;
    void begin(TwoWire& wire = Wire);
    uint8_t _readByte(uint8_t reg);
    void _readBytes(uint8_t reg, uint8_t* data, uint8_t length);
    void _writeByte(uint8_t reg, uint8_t data);
    uint8_t _ctrlReg1;
    uint8_t _ctrlReg2;
    uint8_t _ctrlReg3;
    uint8_t _ctrlReg4;
    uint8_t _ctrlReg5;
    float _mult;

private:
    uint8_t _addr;
};

#endif // __BaseIMU_H__
