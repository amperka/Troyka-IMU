#include <Barometer.h>
#include <GOST4401_81.h>

LPS331::LPS331(uint8_t slaveAddress)
    : BaseIMU(slaveAddress) { }

void LPS331::begin(TwoWire& wire) {
    _wire = &wire;
    _wire->begin();
    _ctrlReg1 |= (1 << 7);
    _ctrlReg1 |= (1 << 6);
    _writeByte(CTRL_REG1, _ctrlReg1);
}

float LPS331::readPressureMillibars() {
    return static_cast<float>(_readPressureRaw()) / 4096;
}

float LPS331::readPressurePascals() {
    return readPressureMillibars() * LPS331_MILLIBARS_TO_PASCALS;
}

float LPS331::readPressureMillimetersHg() {
    return readPressureMillibars() * LPS331_MILLIBARS_TO_MILLIMETERSHG;
}

// Temperature output data from datasheet
float LPS331::readTemperatureC() {
    return 42.5 + static_cast<float>(_readTemperatureRaw()) / 480;
}

// Convert Celsius scale to Kelvin
float LPS331::readTemperatureK() {
    return readTemperatureC() + LPS331_CELSIUS_TO_KELVIN;
}

// Convert Celsius scale to Fahrenheit
float LPS331::readTemperatureF() { return readTemperatureC() * 1.8 + 32; }

uint32_t LPS331::_readPressureRaw() {
    uint8_t data[3];
    _readBytes(0x80 | LPS331_PRESS_OUT_XL, data, 3);
    return (uint32_t)data[2] << 16 | (uint16_t)data[1] << 8 | data[0];
}

int16_t LPS331::_readTemperatureRaw() {
    return ((int16_t)_readByte(LPS331_TEMP_OUT_H) << 8)
           | _readByte(LPS331_TEMP_OUT_L);
}

float LPS331::readAltitude() {
    float pressurePascals = readPressurePascals();
    return GOST4401_getAltitude(pressurePascals);
}
