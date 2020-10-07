#ifndef __BAROMETER_H__
#define __BAROMETER_H__

#include "BaseIMU.h"

#define LPS331_REF_P_XL 0x08
#define LPS331_REF_P_L 0x09
#define LPS331_REF_P_H 0x0A
#define LPS331_WHO_AM_I 0x0F
#define LPS331_RES_CONF 0x10
#define LPS331_CTRL_REG1 0x20
#define LPS331_CTRL_REG2 0x21
#define LPS331_CTRL_REG3 0x22
#define LPS331_INTERRUPT_CFG 0x23
#define LPS331_INT_SOURCE 0x24
#define LPS331_THS_P_L 0x25
#define LPS331_THS_P_H 0x26
#define LPS331_STATUS_REG 0x27
#define LPS331_PRESS_OUT_XL 0x28
#define LPS331_PRESS_OUT_L 0x29
#define LPS331_PRESS_OUT_H 0x2A
#define LPS331_TEMP_OUT_L 0x2B
#define LPS331_TEMP_OUT_H 0x2C
#define LPS331_AMP_CTRL 0x30
#define LPS331_DELTA_PRESS_XL 0x3C
#define LPS331_DELTA_PRESS_L 0x3D
#define LPS331_DELTA_PRESS_H 0x3E
#define LPS331_CELSIUS_TO_KELVIN_OFFSET 273.15

class LPS331 : public BaseIMU {
public:
    LPS331(uint8_t slaveAddress);
    void begin(TwoWire& wire = Wire);
    float readPressurePascals();
    float readPressureMillibars();
    float readPressureMillimetersHg();
    float readTemperatureC();
    float readTemperatureK();
    float readTemperatureF();
    float readAltitude();

private:
    uint32_t _readPressureRaw();
    int16_t _readTemperatureRaw();
};

#endif // __BAROMETER_H__
