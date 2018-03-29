/**
 * Partial implementation of standard atmospheric model as described in 
 * GOST 4401-81 useful for processing of data from meteorological balloon 
 * sensors.
 *
 * Supported modelling of temperature and pressure over the altitude span from
 * 0 up to 51km.
 *  
 * by Oleg Kochetov <ok@noiselab.ru>
 */

#ifndef _ATMOSPHERE_GOST4401_H_
#define _ATMOSPHERE_GOST4401_H_

#include <stdint.h>


// Constants
#define  GOST4401_G		 9.80665
#define  GOST4401_R    287.05287
#define  GOST4401_E      6356766

#define GOST4401_MIN_PRESSURE	  6.69384
#define GOST4401_MAX_PRESSURE   101325.00

#define GOST4401_MIN_GPALT			0.00
#define GOST4401_MAX_GPALT		51000.00


// Export functions
float GOST4401_getAltitude(float pressurePa);
float GOST4401_getPressure(float altitude);
float GOST4401_getTemperature(float altitude);


// Structure for lookup table record
typedef struct __attribute__((packed)) _GOST4401_RECORD{
	float	  alt;		// Geopotentional altitude
	float    temp;	    // degrees K
	float  t_grad;		// degrees K per meter
	float	press;		// pascals
} GOST4401_RECORD;

// Lookup table with averaged empirical parameters for 
// lower layers of atmosphere in accordance with GOST 4401-81
#define GOST4401_LUT_RECORDS 	6
static const GOST4401_RECORD ag_table[] = {
  {	 	0,  288.15, -0.0065, 101325.00 },
  { 11000,  216.65,     0.0,  22632.04 },
  { 20000,  216.65,  0.0010,   5474.87 }, 
  { 32000,  228.65,  0.0028,  868.0146 },
  { 47000,  270.65,     0.0,  110.9056 },
  { 51000,  270.65, -0.0028,   6.69384 }
};

#endif