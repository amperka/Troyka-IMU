#ifndef MADGWICK_AHRS_H_
#define MADGWICK_AHRS_H_

#include <math.h>

#define SAMPLE_FREQ	1000.0f		// sample frequency in Hz
#define BETA_DEF	0.5f		// 2 * proportional gain

class Madgwick {

public:
    Madgwick();
    void readQuaternions(float *q0, float *q1, float *q2, float *q3);
    void reset();
    void setKoeff(float sampleFreq, float beta);
    void update(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
    void update(float gx, float gy, float gz, float ax, float ay, float az);
    float getPitchRad();
    float getRollRad();
    float getYawRad();
    float getPitchDeg();
    float getRollDeg();
    float getYawDeg();

private:
    float invSqrt(float x);
    volatile float _beta = BETA_DEF;				// algorithm gain
    volatile float _sampleFreq = SAMPLE_FREQ;
    volatile float _q0 = 1.0f;
    volatile float _q1 = 0.0f;
    volatile float _q2 = 0.0f;
    volatile float _q3 = 0.0f;
};
#endif
