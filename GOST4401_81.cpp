#include <GOST4401_81.h>
#include <math.h>

static float _GOST4401_geopotential2geometric(float altitude){
	return altitude * GOST4401_E / (GOST4401_E - altitude);
}

static float _GOST4401_geometric2geopotential(float altitude){
	return altitude * GOST4401_E / (GOST4401_E + altitude);
}


/** 
 * Returns geometric altitude value for the given pressure.
 *
 * @param float pressurePa - pressure in pascals
 * @retval	float geometric altitude in meters
 */

float GOST4401_getAltitude(float pressurePa){

  if ((pressurePa <= GOST4401_MIN_PRESSURE) || (pressurePa > GOST4401_MAX_PRESSURE))
    return NAN;
   
  int idx = 0;

  for (idx = 0; idx < GOST4401_LUT_RECORDS - 1; idx++){
    if ((pressurePa <= ag_table[idx].press) && (pressurePa > ag_table[idx + 1].press))
      break;
  }

  float Ps = ag_table[idx].press;
  float Bm = ag_table[idx].t_grad; 
  float Tm = ag_table[idx].temp;
  float Hb = ag_table[idx].alt;
  float geopotH = 0;


  if (Bm != 0.0) { 
    geopotH = ((Tm * pow(Ps / pressurePa, Bm * GOST4401_R / GOST4401_G) - Tm) / Bm);
  } else {
    geopotH = log10(Ps / pressurePa) * (GOST4401_R * Tm) / (GOST4401_G * 0.434294);
  }
  
  return _GOST4401_geopotential2geometric(Hb + geopotH);
};

/** 
 * Returns pressure in pascals for the given geometric altitude
 *
 * @param float altitude - geometric altitude in meters
 * @retval float - pressure in pascals
 */

float GOST4401_getPressure(float altitude){
	float geopotH = _GOST4401_geometric2geopotential(altitude);

	if ((geopotH < GOST4401_MIN_GPALT) || (geopotH >= GOST4401_MAX_GPALT))
    	return NAN;
    
 	int idx = 0;
  
  	for (idx = 1; idx < GOST4401_LUT_RECORDS - 1; idx++) {
    	if ((geopotH >= ag_table[idx].alt) && (geopotH < ag_table[idx].alt))
    		break;
  	}

  	float Ps = ag_table[idx].press;
  	float Bm = ag_table[idx].t_grad; 
  	float Tm = ag_table[idx].temp;
  	float Hb = ag_table[idx].alt;
  	float lP = 0;
  
  	if (Bm != 0.0) { 
    	lP = log10(Ps) - (GOST4401_G / (Bm * GOST4401_R)) * log10((Tm + Bm * (geopotH - Hb)) / Tm);
    } else {
		lP = log10(Ps) - 0.434294 *(GOST4401_G * (geopotH - Hb)) / (GOST4401_R * Tm);
	}
  
  	return pow(10, lP);
}

/**
 * Returns temperature value in K for the given geometric altitude.
 *
 * @param float altitude - geometric altitude in meters
 * @retval float - temperature in degrees K
 */

float GOST4401_getTemperature(float altitude){
	float geopotH = _GOST4401_geometric2geopotential(altitude);

	if ((geopotH < GOST4401_MIN_GPALT) || (geopotH >= GOST4401_MAX_GPALT))
    	return NAN;
    
 	int idx = 0;
  
  	for (idx = 1; idx < GOST4401_LUT_RECORDS - 1; idx++) {
    	if ((geopotH >= ag_table[idx].alt) && (geopotH < ag_table[idx].alt))
    		break;
  	}

  	float Bm = ag_table[idx].t_grad; 
  	float Tm = ag_table[idx].temp;
  	float Hb = ag_table[idx].alt;
  	float temp = Tm;

  	if (Bm != 0.0){
  		temp += Bm * (geopotH - Hb);
  	}

  	return temp;
}

