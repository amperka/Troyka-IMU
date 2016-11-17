#ifndef HW_H
#define HW_H

#if defined(__AVR__) || defined(__SAMD21G18A__)
#define WIRE_IMU Wire

#elif defined(__SAM3X8E__) || defined(__SAM3A8C__) || defined(__SAM3A4C__)
#define WIRE_IMU Wire1
#endif

#include <stdint.h>
#include <Arduino.h>
class AxisHw
{
private:
    uint8_t _addr;

    static inline void waitForData();

public:
    AxisHw (uint8_t addr) : _addr (addr) {}

    uint8_t readByte(uint8_t reg);
    int16_t readX();
    int16_t readY();
    int16_t readZ();
    void readXYZ(int16_t *x, int16_t *y, int16_t *z);

protected:
    uint8_t _ctrlReg1;
    uint8_t _ctrlReg2;
    uint8_t _ctrlReg3;
    uint8_t _ctrlReg4;
    uint8_t _ctrlReg5;

    float _mult;

    void writeCtrlReg1();
    void writeCtrlReg2();
    void writeCtrlReg3();
    void writeCtrlReg4();
    void writeCtrlReg5();

    int16_t readAxis(uint8_t reg);
};
#endif //HW_H
