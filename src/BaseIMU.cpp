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

/*
void BaseIMU::readXYZ(int16_t *x, int16_t *y, int16_t *z) {
    _wire->beginTransmission(_addr);
    _wire->write(OUT_X | (1 << 7));  // assert MSB to enable register address auto-increment
    _wire->endTransmission();

    uint8_t burstSize = 6;
    _wire->requestFrom(_addr, burstSize);
    uint8_t values[burstSize];
    for (uint8_t i = 0; i < burstSize; i++) {
        values[i] = _wire->read();
    }
    
    *x = *((int16_t*)&values[0]);
    *y = *((int16_t*)&values[2]);
    *z = *((int16_t*)&values[4]);
}*/

void BaseIMU::readXYZ(int16_t &x, int16_t &y, int16_t &z) {
    uint8_t data[6];
    _readBytes(0x80 | OUT_X, data, 6);
    x = ((int16_t)data[1] << 8 ) | data[0];
    y = ((int16_t)data[3] << 8 ) | data[2];
    z = ((int16_t)data[5] << 8 ) | data[4];
}

uint8_t BaseIMU::_readByte(uint8_t reg) {
    uint8_t data;
    _wire->beginTransmission(_addr);
    _wire->write(reg);
    _wire->endTransmission();
    _wire->requestFrom(_addr, 1u);
    data = _wire->read();
    _wire->endTransmission();
    return data;
}

void BaseIMU::_writeByte(uint8_t reg, uint8_t data) {
    _wire->beginTransmission(_addr);
    _wire->write(reg);
    _wire->write(data);
    _wire->endTransmission();
}

void BaseIMU::_readBytes(uint8_t reg, uint8_t* data, uint8_t length) {
    _wire->beginTransmission(_addr);
    _wire->write(reg);
    _wire->endTransmission();
    _wire->requestFrom(_addr, length);
    for (size_t i = 0; i < length; i++) {
        *data++ = _wire->read();
    }
    _wire->endTransmission();
}
