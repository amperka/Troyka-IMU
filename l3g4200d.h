#ifndef L3G4200D_H
#define L3G4200D_H

#define L3G4200D_TWI_ADDRESS 0b01101000

#define RANGE_250DPS         0
#define RANGE_500DPS         1
#define RANGE_2000DPS        2


class L3G4200D_TWI
{
public:
    L3G4200D_TWI(uint8_t addr = L3G4200D_TWI_ADDRESS);
    void begin();
    void sleep(bool enable);
    void setRange(uint8_t range);
    uint8_t readByte(uint8_t reg);
    int16_t readX();
    int16_t readY();
    int16_t readZ();
    float readDegPerSecX();
    float readDegPerSecY();
    float readDegPerSecZ();
    float readRadPerSecX();
    float readRadPerSecY();
    float readRadPerSecZ();
    void readXYZ(int16_t *x, int16_t *y, int16_t *z);
    void readDegPerSecXYZ(float *gx, float *gy, float *gz);
    void readRadPerSecXYZ(float *gx, float *gy, float *gz);

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
