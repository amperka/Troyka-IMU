#ifndef __GYROSCOPE_H__
#define __GYROSCOPE_H__

#include "BaseIMU.h"

#define L3G4200D_ADDRESS 0b01101000
#define L3G4200D_ADDRESS_V2 0b01101001

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
    L3G4200D(uint8_t addr = L3G4200D_ADDRESS);
    void begin(TwoWire &wire = Wire);
    void sleep(bool enable);
    void setRange(uint8_t range);
    float readDegPerSecX();
    float readDegPerSecY();
    float readDegPerSecZ();
    float readRadPerSecX();
    float readRadPerSecY();
    float readRadPerSecZ();
    void readDegPerSecXYZ(float& gx, float& gy, float& gz);
    void readRadPerSecXYZ(float& gx, float& gy, float& gz);
};

#endif // __GYROSCOPE_H__
