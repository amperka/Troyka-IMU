#include "BaseIMU.h"

int16_t BaseIMU::readX() {
    return ((int16_t)_readByte(OUT_X + 1) << 8) | _readByte(OUT_X);
}

int16_t BaseIMU::readY() {
    return ((int16_t)_readByte(OUT_Y + 1) << 8) | _readByte(OUT_Y);
}

int16_t BaseIMU::readZ() {
    return ((int16_t)_readByte(OUT_Z + 1) << 8) | _readByte(OUT_Z);
}

void BaseIMU::readXYZ(int16_t &x, int16_t &y, int16_t &z) {
    uint8_t data[6];
    _readBytes(0x80 | OUT_X, data, 6);
    x = ((int16_t)data[1] << 8 ) | data[0];
    y = ((int16_t)data[3] << 8 ) | data[2];
    z = ((int16_t)data[5] << 8 ) | data[4];
}

uint8_t BaseIMU::_readByte(uint8_t regAddress) {
    uint8_t data;
    _wire->beginTransmission(_slaveAddress);
    _wire->write(regAddress);
    _wire->endTransmission();
    _wire->requestFrom(_slaveAddress, 1u);
    data = _wire->read();
    _wire->endTransmission();
    return data;
}

void BaseIMU::_writeByte(uint8_t regAddress, uint8_t data) {
    _wire->beginTransmission(_slaveAddress);
    _wire->write(regAddress);
    _wire->write(data);
    _wire->endTransmission();
}

void BaseIMU::_readBytes(uint8_t regAddress, uint8_t* data, uint8_t length) {
    _wire->beginTransmission(_slaveAddress);
    _wire->write(regAddress);
    _wire->endTransmission();
    _wire->requestFrom(_slaveAddress, length);
    for (size_t i = 0; i < length; i++) {
        *data++ = _wire->read();
    }
    _wire->endTransmission();
}
