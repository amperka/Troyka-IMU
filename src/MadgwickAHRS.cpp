#include "MadgwickAHRS.h"
#include <math.h>
#include <Arduino.h>

Madgwick::Madgwick() {

}

void Madgwick::setKoeff(float sampleFreq, float beta) {
    _beta = beta;
    _sampleFreq = sampleFreq;
}
void Madgwick::reset() {
    _q0 = 1.0;
    _q1 = 0;
    _q2 = 0;
    _q3 = 0;
}

void Madgwick::readQuaternions(float *q0, float *q1, float *q2, float *q3) {
    *q0 = _q0;
    *q1 = _q1;
    *q2 = _q2;
    *q3 = _q3;
}

//---------------------------------------------------------------------------------------------------
// AHRS algorithm update

void Madgwick::update(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz) {
    float recipNorm;
    float s0, s1, s2, s3;
    float qDot1, qDot2, qDot3, qDot4;
    float hx, hy;
    float _2q0mx, _2q0my, _2q0mz, _2q1mx, _2bx, _2bz, _4bx, _4bz, _2q0, _2q1, _2q2, _2q3, _2q0q2, _2q2q3, q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;

    // Use IMU algorithm if magnetometer measurement invalid (avoids NaN in magnetometer normalisation)
    if((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f)) {
        update(gx, gy, gz, ax, ay, az);
        return;
    }

    // Rate of change of quaternion from gyroscope
    qDot1 = 0.5f * (-_q1 * gx - _q2 * gy - _q3 * gz);
    qDot2 = 0.5f * (_q0 * gx + _q2 * gz - _q3 * gy);
    qDot3 = 0.5f * (_q0 * gy - _q1 * gz + _q3 * gx);
    qDot4 = 0.5f * (_q0 * gz + _q1 * gy - _q2 * gx);

    // Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
    if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

        // Normalise accelerometer measurement
        recipNorm = invSqrt(ax * ax + ay * ay + az * az);
        ax *= recipNorm;
        ay *= recipNorm;
        az *= recipNorm;   

        // Normalise magnetometer measurement
        recipNorm = invSqrt(mx * mx + my * my + mz * mz);
        mx *= recipNorm;
        my *= recipNorm;
        mz *= recipNorm;

        // Auxiliary variables to avoid repeated arithmetic
        _2q0mx = 2.0f * _q0 * mx;
        _2q0my = 2.0f * _q0 * my;
        _2q0mz = 2.0f * _q0 * mz;
        _2q1mx = 2.0f * _q1 * mx;
        _2q0 = 2.0f * _q0;
        _2q1 = 2.0f * _q1;
        _2q2 = 2.0f * _q2;
        _2q3 = 2.0f * _q3;
        _2q0q2 = 2.0f * _q0 * _q2;
        _2q2q3 = 2.0f * _q2 * _q3;
        q0q0 = _q0 * _q0;
        q0q1 = _q0 * _q1;
        q0q2 = _q0 * _q2;
        q0q3 = _q0 * _q3;
        q1q1 = _q1 * _q1;
        q1q2 = _q1 * _q2;
        q1q3 = _q1 * _q3;
        q2q2 = _q2 * _q2;
        q2q3 = _q2 * _q3;
        q3q3 = _q3 * _q3;

        // Reference direction of Earth's magnetic field
        hx = mx * q0q0 - _2q0my * _q3 + _2q0mz * _q2 + mx * q1q1 + _2q1 * my * _q2 + _2q1 * mz * _q3 - mx * q2q2 - mx * q3q3;
        hy = _2q0mx * _q3 + my * q0q0 - _2q0mz * _q1 + _2q1mx * _q2 - my * q1q1 + my * q2q2 + _2q2 * mz * _q3 - my * q3q3;
        _2bx = sqrt(hx * hx + hy * hy);
        _2bz = -_2q0mx * _q2 + _2q0my * _q1 + mz * q0q0 + _2q1mx * _q3 - mz * q1q1 + _2q2 * my * _q3 - mz * q2q2 + mz * q3q3;
        _4bx = 2.0f * _2bx;
        _4bz = 2.0f * _2bz;

        // Gradient decent algorithm corrective step
        s0 = -_2q2 * (2.0f * q1q3 - _2q0q2 - ax) + _2q1 * (2.0f * q0q1 + _2q2q3 - ay) - _2bz * _q2 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (-_2bx * _q3 + _2bz * _q1) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + _2bx * _q2 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
        s1 = _2q3 * (2.0f * q1q3 - _2q0q2 - ax) + _2q0 * (2.0f * q0q1 + _2q2q3 - ay) - 4.0f * _q1 * (1 - 2.0f * q1q1 - 2.0f * q2q2 - az) + _2bz * _q3 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (_2bx * _q2 + _2bz * _q0) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + (_2bx * _q3 - _4bz * _q1) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
        s2 = -_2q0 * (2.0f * q1q3 - _2q0q2 - ax) + _2q3 * (2.0f * q0q1 + _2q2q3 - ay) - 4.0f * _q2 * (1 - 2.0f * q1q1 - 2.0f * q2q2 - az) + (-_4bx * _q2 - _2bz * _q0) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (_2bx * _q1 + _2bz * _q3) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + (_2bx * _q0 - _4bz * _q2) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
        s3 = _2q1 * (2.0f * q1q3 - _2q0q2 - ax) + _2q2 * (2.0f * q0q1 + _2q2q3 - ay) + (-_4bx * _q3 + _2bz * _q1) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (-_2bx * _q0 + _2bz * _q2) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + _2bx * _q1 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
        recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
        s0 *= recipNorm;
        s1 *= recipNorm;
        s2 *= recipNorm;
        s3 *= recipNorm;

        // Apply feedback step
        qDot1 -= _beta * s0;
        qDot2 -= _beta * s1;
        qDot3 -= _beta * s2;
        qDot4 -= _beta * s3;
    }

    // Integrate rate of change of quaternion to yield quaternion
    _q0 += qDot1 * (1.0f / _sampleFreq);
    _q1 += qDot2 * (1.0f / _sampleFreq);
    _q2 += qDot3 * (1.0f / _sampleFreq);
    _q3 += qDot4 * (1.0f / _sampleFreq);

    // Normalise quaternion
    recipNorm = invSqrt(_q0 * _q0 + _q1 * _q1 + _q2 * _q2 + _q3 * _q3);
    _q0 *= recipNorm;
    _q1 *= recipNorm;
    _q2 *= recipNorm;
    _q3 *= recipNorm;
}

//---------------------------------------------------------------------------------------------------
// IMU algorithm update

void Madgwick::update(float gx, float gy, float gz, float ax, float ay, float az) {
    float recipNorm;
    float s0, s1, s2, s3;
    float qDot1, qDot2, qDot3, qDot4;
    float _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;

    // Rate of change of quaternion from gyroscope
    qDot1 = 0.5f * (-_q1 * gx - _q2 * gy - _q3 * gz);
    qDot2 = 0.5f * (_q0 * gx + _q2 * gz - _q3 * gy);
    qDot3 = 0.5f * (_q0 * gy - _q1 * gz + _q3 * gx);
    qDot4 = 0.5f * (_q0 * gz + _q1 * gy - _q2 * gx);

    // Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
    if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

        // Normalise accelerometer measurement
        recipNorm = invSqrt(ax * ax + ay * ay + az * az);
        ax *= recipNorm;
        ay *= recipNorm;
        az *= recipNorm;

        // Auxiliary variables to avoid repeated arithmetic
        _2q0 = 2.0f * _q0;
        _2q1 = 2.0f * _q1;
        _2q2 = 2.0f * _q2;
        _2q3 = 2.0f * _q3;
        _4q0 = 4.0f * _q0;
        _4q1 = 4.0f * _q1;
        _4q2 = 4.0f * _q2;
        _8q1 = 8.0f * _q1;
        _8q2 = 8.0f * _q2;
        q0q0 = _q0 * _q0;
        q1q1 = _q1 * _q1;
        q2q2 = _q2 * _q2;
        q3q3 = _q3 * _q3;


        // Gradient decent algorithm corrective step
        s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
        s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * _q1 - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
        s2 = 4.0f * q0q0 * _q2 + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
        s3 = 4.0f * q1q1 * _q3 - _2q1 * ax + 4.0f * q2q2 * _q3 - _2q2 * ay;
        recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
        s0 *= recipNorm;
        s1 *= recipNorm;
        s2 *= recipNorm;
        s3 *= recipNorm;

        // Apply feedback step
        qDot1 -= _beta * s0;
        qDot2 -= _beta * s1;
        qDot3 -= _beta * s2;
        qDot4 -= _beta * s3;
    }


    // Integrate rate of change of quaternion to yield quaternion
    _q0 += qDot1 * (1.0f / _sampleFreq);
    _q1 += qDot2 * (1.0f / _sampleFreq);
    _q2 += qDot3 * (1.0f / _sampleFreq);
    _q3 += qDot4 * (1.0f / _sampleFreq);

    // Normalise quaternion
    recipNorm = invSqrt(_q0 * _q0 + _q1 * _q1 + _q2 * _q2 + _q3 * _q3);
    _q0 *= recipNorm;
    _q1 *= recipNorm;
    _q2 *= recipNorm;
    _q3 *= recipNorm;
}

//---------------------------------------------------------------------------------------------------
// Fast inverse square-root
// See: http://en.wikipedia.org/wiki/Fast_inverse_square_root

float Madgwick::invSqrt(float x) {
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long*)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}

float Madgwick::getYawRad() {
    return atan2(2 * _q1 * _q2 - 2 * _q0 * _q3, 2 * _q0 * _q0 + 2 * _q1 * _q1 - 1);
}

float Madgwick::getPitchRad() {
    return atan2(2 * _q2 * _q3 - 2 * _q0 * _q1, 2 * _q0 * _q0 + 2 * _q3 * _q3 - 1);
}

float Madgwick::getRollRad() {
    return -1 * atan2(2.0f * (_q0 * _q2 - _q1 * _q3), 1.0f - 2.0f * (_q2 * _q2 + _q1 *_q1 ));
}

float Madgwick::getYawDeg() {
    return getYawRad() * RAD_TO_DEG;
}

float Madgwick::getPitchDeg() {
    return getPitchRad() * RAD_TO_DEG;
}

float Madgwick::getRollDeg() {
    return getRollRad() * RAD_TO_DEG;
}