#ifndef LIS331DLH_H
#define LIS331DLH_H

#define LIS331DLH_TWI_ADDRESS 0b0011000

#define RANGE_2G        2
#define RANGE_4G        4
#define RANGE_8G        8

class LIS331DLH_TWI
{
public:
    LIS331DLH_TWI(uint8_t addr = LIS331DLH_TWI_ADDRESS);
    void begin();
    void sleep(bool enable);
    void setRange(uint8_t range);
    uint8_t readByte(uint8_t reg);
    int16_t readX();
    int16_t readY();
    int16_t readZ();
    float readGX();
    float readGY();
    float readGZ();
    float readAX();
    float readAY();
    float readAZ();
    void readXYZ(int16_t *x, int16_t *y, int16_t *z);
    void readGXYZ(float *ax, float *ay, float *az);
    void readAXYZ(float *gx, float *gy, float *gz);

private:
    uint8_t _addr;
    float _mult;
    uint8_t _ctrlReg1;
    uint8_t _ctrlReg2;
    uint8_t _ctrlReg3;
    uint8_t _ctrlReg4;
    uint8_t _ctrlReg5;
    void writeCtrlReg1();
    void writeCtrlReg2();
    void writeCtrlReg3();
    void writeCtrlReg4();
    void writeCtrlReg5();
    int16_t readAxis(uint8_t reg);
};

#endif
