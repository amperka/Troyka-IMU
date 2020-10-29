#include "BaseIMU.h"

uint8_t BaseIMU::readDeviceID(){
    return _readByte(BASE_IMU_WHO_AM_I);
}

int16_t BaseIMU::readX() {
    return (static_cast<uint16_t>(_readByte(BASE_IMU_OUT_X_H)) << 8) | _readByte(BASE_IMU_OUT_X_L);
}

int16_t BaseIMU::readY() {
    return (static_cast<uint16_t>(_readByte(BASE_IMU_OUT_Y_H)) << 8) | _readByte(BASE_IMU_OUT_Y_L);
}

int16_t BaseIMU::readZ() {
    return (static_cast<uint16_t>(_readByte(BASE_IMU_OUT_Z_H)) << 8) | _readByte(BASE_IMU_OUT_Z_L);
}

void BaseIMU::readXYZ(int16_t& x, int16_t& y, int16_t& z) {
    uint8_t data[6];
    _readBytes(0x80 | BASE_IMU_OUT_X_L, data, 6);
    x = (static_cast<uint16_t>(data[1]) << 8) | data[0];
    y = (static_cast<uint16_t>(data[3]) << 8) | data[2];
    z = (static_cast<uint16_t>(data[5]) << 8) | data[4];
}

uint8_t BaseIMU::_readByte(uint8_t regAddress) {
    uint8_t data;
    _wire->beginTransmission(_slaveAddress);
    _wire->write(regAddress);
    _wire->endTransmission();
    _wire->requestFrom(_slaveAddress, 1u);
    data = _wire->read();
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
}
