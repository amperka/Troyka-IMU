#include <LPS331.h>
#include <Wire.h>
#include <GOST4401_81.h>

// Constructors //////////////////////////////////////////////////////

LPS331::LPS331(uint8_t addr)
{
  address = addr;
}

// Public Methods ////////////////////////////////////////////////////

// sets or detects slave address; returns bool indicating success
void LPS331::begin()
{
  WIRE_IMU.begin();
  writeReg(LPS331_CTRL_REG1, 0b11100000);
  delay(100);
}

// writes register
void LPS331::writeReg(byte reg, byte value)
{
  WIRE_IMU.beginTransmission(address);
  WIRE_IMU.write(reg);
  WIRE_IMU.write(value);
  WIRE_IMU.endTransmission();
}

// reads register
byte LPS331::readReg(byte reg)
{
  byte value;

  WIRE_IMU.beginTransmission(address);
  WIRE_IMU.write(reg);
  WIRE_IMU.endTransmission(false); // restart
  WIRE_IMU.requestFrom(address, (byte)1);
  value = WIRE_IMU.read();
  WIRE_IMU.endTransmission();

  return value;
}

// read pressure in pascals
float LPS331::readPressurePascals(void)
{
  return (float)readPressureRaw() / 40.96;
}

// reads pressure in millibars (mbar)/hectopascals (hPa)
float LPS331::readPressureMillibars(void)
{
  return (float)readPressureRaw() / 4096;
}

// reads pressure in inches of mercury (inHg)
float LPS331::readPressureInchesHg(void)
{
  return (float)readPressureRaw() / 138706.5;
}

// reads pressure in millimeters of mercury (mmHg)
float LPS331::readPressureMillimetersHg(void)
{
  // 1 mbar * 0,75006168270417 = 1 mmHg
  return (float)(readPressureRaw()) * 0.75006375541921 / 4096.0;
}

// reads pressure and returns raw 24-bit sensor output
int32_t LPS331::readPressureRaw(void)
{
  WIRE_IMU.beginTransmission(address);
  // assert MSB to enable register address auto-increment
  WIRE_IMU.write(LPS331_PRESS_OUT_XL | (1 << 7));
  WIRE_IMU.endTransmission();
  WIRE_IMU.requestFrom(address, (byte)3);

  while (WIRE_IMU.available() < 3);

  uint8_t pxl = WIRE_IMU.read();
  uint8_t pl = WIRE_IMU.read();
  uint8_t ph = WIRE_IMU.read();

  // combine bytes
  return (int32_t)(int8_t)ph << 16 | (uint16_t)pl << 8 | pxl;
}

// reads temperature in degrees K
float LPS331::readTemperatureK(){
  return readTemperatureC() + LPS331_CELSIUS_TO_KELVIN_OFFSET;
}

// reads temperature in degrees C
float LPS331::readTemperatureC(void)
{
  return 42.5 + (float)readTemperatureRaw() / 480;
}

// reads temperature in degrees F
float LPS331::readTemperatureF(void)
{
  return 108.5 + (float)readTemperatureRaw() / 480 * 1.8;
}

// reads temperature and returns raw 16-bit sensor output
int16_t LPS331::readTemperatureRaw(void)
{
  WIRE_IMU.beginTransmission(address);
  // assert MSB to enable register address auto-increment
  WIRE_IMU.write(LPS331_TEMP_OUT_L | (1 << 7));
  WIRE_IMU.endTransmission();
  WIRE_IMU.requestFrom(address, (byte)2);

  while (WIRE_IMU.available() < 2);

  uint8_t tl = WIRE_IMU.read();
  uint8_t th = WIRE_IMU.read();

  // combine bytes
  return (int16_t)(th << 8 | tl);
}

// Calculates altitude in meters above MSL using GOST4401-81 
// atmosphere model from the given pressure in pascals
// The model implemented for height up to 51km
// 
float LPS331::GOST4401_altitude(float pressure_pascals){
  return GOST4401_getAltitude(pressure_pascals);
}

// converts pressure in mbar to altitude in meters, using 1976 US
// Standard Atmosphere model (note that this formula only applies to a
// height of 11 km, or about 36000 ft)
//  If altimeter setting (QNH, barometric pressure adjusted to sea
//  level) is given, this function returns an indicated altitude
//  compensated for actual regional pressure; otherwise, it returns
//  the pressure altitude above the standard pressure level of 1013.25
//  mbar or 29.9213 inHg
float LPS331::pressureToAltitudeMeters(float pressure_mbar, float altimeter_setting_mbar)
{
  return (1 - pow(pressure_mbar / altimeter_setting_mbar, 0.190263)) * 44330.8;
}

// converts pressure in inHg to altitude in feet; see notes above
float LPS331::pressureToAltitudeFeet(float pressure_inHg, float altimeter_setting_inHg)
{
  return (1 - pow(pressure_inHg / altimeter_setting_inHg, 0.190263)) * 145442;
}

// Private Methods ///////////////////////////////////////////////////

bool LPS331::autoDetectAddress(void)
{
  // try each possible address and stop if reading WHO_AM_I returns the expected response
  address = LPS331AP_ADDRESS_SA0_LOW;
  if (testWhoAmI()) return true;
  address = LPS331AP_ADDRESS_SA0_HIGH;
  if (testWhoAmI()) return true;

  return false;
}

bool LPS331::testWhoAmI(void)
{
  return (readReg(LPS331_WHO_AM_I) == 0xBB);
}
