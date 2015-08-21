
#ifndef LIS3MDL_H
#define LIS3MDL_H

#define LIS3MDL_TWI_ADDRESS 0b0011100

#define RANGE_4         0
#define RANGE_8         1
#define RANGE_12        2
#define RANGE_16        3


class LIS3MDL_TWI
{
    public:
        LIS3MDL_TWI(uint8_t addr = LIS3MDL_TWI_ADDRESS);

        void begin();

        int16_t readX();
        int16_t readY();
        int16_t readZ();

        void readXYZ_Calib();
        float read_Yaw();

        float readX_Gauss();
        float readY_Gauss();
        float readZ_Gauss();
        void setRange(uint8_t range);
        float x_cal = 0;
        float y_cal = 0;
        float z_cal = 0;

    private:
        uint8_t _addr;
        uint8_t _ctrlReg1;
        uint8_t _ctrlReg2;
        uint8_t _ctrlReg3;
        uint8_t _ctrlReg4;
        uint8_t _ctrlReg5;
        float _mult;

    protected:
        void writeCtrlReg1();
        void writeCtrlReg2();
        void writeCtrlReg3();
        void writeCtrlReg4();
        void writeCtrlReg5();
        int16_t readAxis(uint8_t reg);
};

#endif
