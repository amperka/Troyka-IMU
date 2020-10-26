#ifndef __BAROMETER_H__
#define __BAROMETER_H__

#include "BaseIMU.h"

constexpr auto LPS331_PRESS_OUT_XL = 0x28;
constexpr auto LPS331_PRESS_OUT_L = 0x29;
constexpr auto LPS331_PRESS_OUT_H = 0x2A;
constexpr auto LPS331_TEMP_OUT_L = 0x2B;
constexpr auto LPS331_TEMP_OUT_H = 0x2C;

constexpr auto LPS331_CELSIUS_TO_KELVIN = 273.15;
constexpr auto LPS331_MILLIBARS_TO_PASCALS = 100;
constexpr auto LPS331_MILLIBARS_TO_MILLIMETERSHG = 0.75;

class Barometer : public BaseIMU {
public:
    Barometer(uint8_t slaveAddress = 0x5C);
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
