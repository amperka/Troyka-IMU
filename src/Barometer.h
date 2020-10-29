#ifndef __BAROMETER_H__
#define __BAROMETER_H__

#include "BaseIMU.h"

// I²C-address devices LPS25HB and LPS331
constexpr uint8_t LPS_SLAVE_ADDRESS = 0x5C;
constexpr uint8_t LPS_SLAVE_ADDRESS_ALT = 0x5D;

// Registers address LPS25HB and LPS331
constexpr uint8_t LPS_CTRL_REG1_ODR0 = 0x10;
constexpr uint8_t LPS_CTRL_REG1_ODR1 = 0x20;
constexpr uint8_t LPS_CTRL_REG1_ODR2 = 0x40;
constexpr uint8_t LPS_CTRL_REG1_PD = 0x80;

constexpr uint8_t LPS_PRESS_OUT_XL = 0x28;
constexpr uint8_t LPS_PRESS_OUT_L = 0x29;
constexpr uint8_t LPS_PRESS_OUT_H = 0x2A;
constexpr uint8_t LPS_TEMP_OUT_L = 0x2B;
constexpr uint8_t LPS_TEMP_OUT_H = 0x2C;

// Registers value byte
constexpr uint8_t LPS331_WHO_AM_I = 0xBB;
constexpr uint8_t LPS25HB_WHO_AM_I = 0xBD;

// Conversion factors units of measurement
constexpr float CELSIUS_TO_KELVIN = 273.15;
constexpr float MILLIBARS_TO_PASCALS = 100;
constexpr float MILLIBARS_TO_MILLIMETERSHG = 0.75;

class Barometer : public BaseIMU {
public:
    Barometer(uint8_t slaveAddress = LPS_SLAVE_ADDRESS);
    void begin(TwoWire& wire = Wire);
    float readPressurePascals();
    float readPressureMillibars();
    float readPressureMillimetersHg();
    float readTemperatureC();
    float readTemperatureK();
    float readTemperatureF();
    float readAltitude();
    // DEPRECATED fuctions
    // Use readAccelerationGX instead
    
private:
    uint32_t _readPressureRaw();
    int16_t _readTemperatureRaw();
    uint8_t _deviceID;
};

#endif // __BAROMETER_H__
