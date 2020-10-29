#include <Barometer.h>
#include <GOST4401_81.h>

Barometer::Barometer(uint8_t slaveAddress)
    : BaseIMU(slaveAddress) { }

void Barometer::begin(TwoWire& wire) {
    _wire = &wire;
    _wire->begin();
    _deviceID = readDeviceID();
    uint8_t data = 0;
    if (_deviceID == LPS331_WHO_AM_I) {
        data |= LPS_CTRL_REG1_ODR0 | LPS_CTRL_REG1_ODR1 | LPS_CTRL_REG1_ODR2;
    } else if (_deviceID == LPS25HB_WHO_AM_I) {
        data |= LPS_CTRL_REG1_ODR2;
    }
    data |= LPS_CTRL_REG1_PD;
    _writeByte(BASE_IMU_CTRL_REG1, data);
}

float Barometer::readPressureMillibars() {
    return static_cast<float>(_readPressureRaw()) / 4096;
}

float Barometer::readPressurePascals() {
    return readPressureMillibars() * MILLIBARS_TO_PASCALS;
}

float Barometer::readPressureMillimetersHg() {
    return readPressureMillibars() * MILLIBARS_TO_MILLIMETERSHG;
}

// Temperature output data from datasheet
float Barometer::readTemperatureC() {
    return 42.5 + static_cast<float>(_readTemperatureRaw()) / 480;
}

// Convert Celsius scale to Kelvin
float Barometer::readTemperatureK() {
    return readTemperatureC() + CELSIUS_TO_KELVIN;
}

// Convert Celsius scale to Fahrenheit
float Barometer::readTemperatureF() { return readTemperatureC() * 1.8 + 32; }

uint32_t Barometer::_readPressureRaw() {
    uint8_t data[3];
    _readBytes(0x80 | LPS_PRESS_OUT_XL, data, 3);
    return static_cast<uint32_t>(data[2]) << 16 | static_cast<uint16_t>(data[1]) << 8 | data[0];
}

int16_t Barometer::_readTemperatureRaw() {
    return (static_cast<uint16_t>(_readByte(LPS_TEMP_OUT_H)) << 8)
           | _readByte(LPS_TEMP_OUT_L);
}

float Barometer::readAltitude() {
    float pressurePascals = readPressurePascals();
    return GOST4401_getAltitude(pressurePascals);
}
