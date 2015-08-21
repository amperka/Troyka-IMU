
#ifndef L3G4200D_H
#define L3G4200D_H

#define L3G4200D_TWI_ADDRESS 0b01101000

#define RANGE_250         0
#define RANGE_500         1
#define RANGE_2000        2


class L3G4200D_TWI
{
    public:
        L3G4200D_TWI(uint8_t addr = L3G4200D_TWI_ADDRESS);

        void begin();
        void sleep(bool enable);

        int16_t readX();
        int16_t readY();
        int16_t readZ();
        float readX_DegPerSec();
        float readY_DegPerSec();
        float readZ_DegPerSec();
        void setRange(uint8_t range);

    private:
        uint8_t _addr;
        uint8_t _ctrlReg1;
        uint8_t _ctrlReg4;
        float _mult;

    protected:
        void writeCtrlReg1();
        void writeCtrlReg4();
        int16_t readAxis(uint8_t reg);
        uint8_t readByte(uint8_t reg);
};

#endif
