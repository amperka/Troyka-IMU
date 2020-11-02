#ifndef __MADGWICK_AHRS_H__
#define __MADGWICK_AHRS_H__

#include <math.h>

// Gyroscope measurement error in rads/s (start at 40 deg/s)
constexpr float GYRO_MEAS_ERROR = M_PI * (40.0f / 180.0f);
// Gyroscope measurement drift in rad/s/s (start at 0.0 deg/s/s)
constexpr float GYRO_MEAS_DRIFT = M_PI * (0.0f / 180.0f);
// Compute beta
constexpr float BETA_DEFAULT = sqrt(3.0f / 4.0f) * GYRO_MEAS_ERROR;
// Compute zeta
constexpr float ZETA_DEFAULT = sqrt(3.0f / 4.0f) * GYRO_MEAS_DRIFT;

class Madgwick {
public:
    Madgwick();
    void begin();
    void reset();
    void setSettings(float beta = BETA_DEFAULT, float zeta = ZETA_DEFAULT);
    void setFrequency(float frequency);
    void readQuaternion(float& q0, float& q1, float& q2, float& q3);
    void update(float gx, float gy, float gz, float ax, float ay, float az,
                float mx, float my, float mz);
    void update(float gx, float gy, float gz, float ax, float ay, float az);
    float getPitchRad();
    float getRollRad();
    float getYawRad();
    float getPitchDeg();
    float getRollDeg();
    float getYawDeg();
    // DEPRECATED fuctions
    // Use readQuaternion instead
    void readQuaternions(float *q0, float *q1, float *q2, float *q3);
    // Use setSettings and setFrequency instead
    void setKoeff(float frequency, float beta);
private:
    float _beta;
    float _zeta;
    float _frequency;
    float _q0, _q1, _q2, _q3;
};

#endif // __MADGWICK_AHRS_H__
