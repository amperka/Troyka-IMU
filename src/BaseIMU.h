#ifndef __BaseIMU_H__
#define __BaseIMU_H__

#include <Arduino.h>
#include <Wire.h>

constexpr auto CTRL_REG1 = 0x20;
constexpr auto CTRL_REG2 = 0x21;
constexpr auto CTRL_REG3 = 0x22;
constexpr auto CTRL_REG4 = 0x23;
constexpr auto CTRL_REG5 = 0x24;

constexpr auto OUT_X_L = 0x28;
constexpr auto OUT_X_H = 0x29;
constexpr auto OUT_Y_L = 0x2A;
constexpr auto OUT_Y_H = 0x2B;
constexpr auto OUT_Z_L = 0x2C;
constexpr auto OUT_Z_H = 0x2D;

class BaseIMU {
public:
    BaseIMU(uint8_t slaveAddress)
        : _slaveAddress(slaveAddress) { }
    void begin(TwoWire& wire = Wire);
    int16_t readX();
    int16_t readY();
    int16_t readZ();
    void readXYZ(int16_t& x, int16_t& y, int16_t& z);

protected:
    uint8_t _readByte(uint8_t regAddress);
    void _writeByte(uint8_t regAddress, uint8_t data);
    void _readBytes(uint8_t regAddress, uint8_t* data, uint8_t length);
    uint8_t _ctrlReg1;
    uint8_t _ctrlReg2;
    uint8_t _ctrlReg3;
    uint8_t _ctrlReg4;
    uint8_t _ctrlReg5;
    float _scale;
    TwoWire* _wire;

private:
    uint8_t _slaveAddress;
};

#endif // __BaseIMU_H__
