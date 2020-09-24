#ifndef __BaseIMU_H__
#define __BaseIMU_H__

#include <Arduino.h>
#include <Wire.h>

class BaseIMU {
public:
    BaseIMU(uint8_t addr)
        : _addr(addr) { }
    uint8_t readByte(uint8_t reg);
    int16_t readX();
    int16_t readY();
    int16_t readZ();
    void readXYZ(int16_t* x, int16_t* y, int16_t* z);

protected:
    void begin(TwoWire& wire = Wire);
    void writeCtrlReg1();
    void writeCtrlReg2();
    void writeCtrlReg3();
    void writeCtrlReg4();
    void writeCtrlReg5();
    uint8_t _ctrlReg1;
    uint8_t _ctrlReg2;
    uint8_t _ctrlReg3;
    uint8_t _ctrlReg4;
    uint8_t _ctrlReg5;
    int16_t readAxis(uint8_t reg);
    TwoWire* _wire;
    float _mult;

private:
    uint8_t _addr;
    void waitForData();
};

#endif // __BaseIMU_H__
