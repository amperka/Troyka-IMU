#ifndef L3G4200D_H
#define L3G4200D_H

#include "stmhw.h"

#define L3G4200D_TWI_ADDRESS     0b01101000
#define L3G4200D_TWI_ADDRESS_V2  0b01101001

#define RANGE_250DPS             0
#define RANGE_500DPS             1
#define RANGE_2000DPS            2

class L3G4200D_TWI : public AxisHw
{
public:
    L3G4200D_TWI(uint8_t addr = L3G4200D_TWI_ADDRESS);
    void begin();
    void sleep(bool enable);
    void setRange(uint8_t range);
    float readDegPerSecX();
    float readDegPerSecY();
    float readDegPerSecZ();
    float readRadPerSecX();
    float readRadPerSecY();
    float readRadPerSecZ();
    void readDegPerSecXYZ(float *gx, float *gy, float *gz);
    void readRadPerSecXYZ(float *gx, float *gy, float *gz);
};

#endif
