#include <Barometer.h>
#include <GOST4401_81.h>

LPS331::LPS331(uint8_t slaveAddress)
    : BaseIMU(slaveAddress) { }

void LPS331::begin(TwoWire& wire) {
    _wire = &wire;
    _wire->begin();
    _ctrlReg1 |= (1 << 7);
    _ctrlReg1 |= (1 << 6);
    _ctrlReg1 |= (1 << 5);
    _writeByte(CTRL_REG1, _ctrlReg1);
}

float LPS331::readPressurePascals() {
    return (float)_readPressureRaw() / 40.96;
}

float LPS331::readPressureMillibars() {
   return (float)_readPressureRaw() / 4096;
}

float LPS331::readPressureMillimetersHg() {
    return (float)(_readPressureRaw()) * 0.75006375541921 / 4096.0;
}

float LPS331::readTemperatureC() {
    return 42.5 + (float)_readTemperatureRaw() / 480;
}

float LPS331::readTemperatureK() {
    return readTemperatureC() + LPS331_CELSIUS_TO_KELVIN_OFFSET;
}

float LPS331::readTemperatureF() {
    return 108.5 + (float)_readTemperatureRaw() / 480 * 1.8;
}

uint32_t LPS331::_readPressureRaw() {
    uint8_t data[3];
    _readBytes(0x80 | LPS331_PRESS_OUT_XL, data, 3);
    return (uint32_t)data[2] << 16 | (uint16_t)data[1] << 8 | data[0];
}

int16_t LPS331::_readTemperatureRaw() {
    uint8_t data[2];
    _readBytes(0x80 | LPS331_TEMP_OUT_L, data, 2);
    return (int16_t)data[1] << 8 | data[0];
}

float LPS331::readAltitude() {
    float pressurePascals = readPressurePascals();
    return GOST4401_getAltitude(pressurePascals);
}
