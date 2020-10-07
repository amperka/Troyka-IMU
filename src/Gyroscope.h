#ifndef __GYROSCOPE_H__
#define __GYROSCOPE_H__

#include "BaseIMU.h"

#define RANGE_250DPS 0
#define RANGE_500DPS 1
#define RANGE_2000DPS 2

#define ADR_FS_250 0x00
#define ADR_FS_500 0x10
#define ADR_FS_2000 0x20

#define SENS_FS_250 0.00875
#define SENS_FS_500 0.0175
#define SENS_FS_2000 0.07

class L3G4200D : public BaseIMU {
public:
    L3G4200D(uint8_t slaveAddress);
    void begin(TwoWire &wire = Wire);
    void sleep(bool state);
    void setRange(uint8_t range);
    float readRotationDegX();
    float readRotationDegY();
    float readRotationDegZ();
    float readRotationRadX();
    float readRotationRadY();
    float readRotationRadZ();
    void readRotationDegXYZ(float& gx, float& gy, float& gz);
    void readRotationRadXYZ(float& gx, float& gy, float& gz);
};

#endif // __GYROSCOPE_H__
