#include <Barometer.h>
#include <GOST4401_81.h>

Barometer::Barometer(uint8_t slaveAddress)
    : BaseIMU(slaveAddress) { }

void Barometer::begin(TwoWire& wire) {
    _wire = &wire;
    _wire->begin();
    _ctrlReg1 |= (1 << 7);
    _ctrlReg1 |= (1 << 6);
    _writeByte(CTRL_REG1, _ctrlReg1);
}

float Barometer::readPressureMillibars() {
    return static_cast<float>(_readPressureRaw()) / 4096;
}

float Barometer::readPressurePascals() {
    return readPressureMillibars() * LPS331_MILLIBARS_TO_PASCALS;
}

float Barometer::readPressureMillimetersHg() {
    return readPressureMillibars() * LPS331_MILLIBARS_TO_MILLIMETERSHG;
}

// Temperature output data from datasheet
float Barometer::readTemperatureC() {
    return 42.5 + static_cast<float>(_readTemperatureRaw()) / 480;
}

// Convert Celsius scale to Kelvin
float Barometer::readTemperatureK() {
    return readTemperatureC() + LPS331_CELSIUS_TO_KELVIN;
}

// Convert Celsius scale to Fahrenheit
float Barometer::readTemperatureF() { return readTemperatureC() * 1.8 + 32; }

uint32_t Barometer::_readPressureRaw() {
    uint8_t data[3];
    _readBytes(0x80 | LPS331_PRESS_OUT_XL, data, 3);
    return (uint32_t)data[2] << 16 | (uint16_t)data[1] << 8 | data[0];
}

int16_t Barometer::_readTemperatureRaw() {
    return ((int16_t)_readByte(LPS331_TEMP_OUT_H) << 8)
           | _readByte(LPS331_TEMP_OUT_L);
}

float Barometer::readAltitude() {
    float pressurePascals = readPressurePascals();
    return GOST4401_getAltitude(pressurePascals);
}
