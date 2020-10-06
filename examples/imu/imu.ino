// библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// создаём объект для работы с гироскопом
Gyroscope gyro(GYRO_ADDRESS_V1);
// создаём объект для работы с акселерометром
Accelerometer accel(ACCEL_ADDRESS_V1);
// создаём объект для работы с компасом
Compass compass(COMPASS_ADDRESS_V1);
// создаём объект для работы с барометром
Barometer barometer(BARO_ADDRESS_V1);

// если напаяны перемычки, устройства доступны по новому адресу
// Gyroscope gyro(GYRO_ADDRESS_V2);
// Accelerometer accel(ACCEL_ADDRESS_V2);
// Compass compass(COMPASS_ADDRESS_V2);
// Barometer barometer(BARO_ADDRESS_V2);

// калибровочные значения компаса
// полученные в калибровочной матрице из примера «compassCalibrateMatrix»
const float compassCalibrationBias[3] = { 2269.685, -3415.288, 4698.337 };

const float compassCalibrationMatrix[3][3] = { { 2.464, 0.133, 0.009 },
                                               { 0.09, 3.081, 0.016 },
                                               { -0.003, -0.225, 2.922 } };

void setup() {
    // открываем последовательный порт
    Serial.begin(9600);
    // выводим сообщение о начале инициализации
    Serial.println("Begin init...");
    // инициализация гироскопа
    gyro.begin();
    // инициализация акселерометра
    accel.begin();
    // инициализация компаса
    compass.begin();
    // инициализация барометра
    barometer.begin();
    // калибровка компаса
    compass.setCalibrateMatrix(compassCalibrationMatrix, compassCalibrationBias);
    // выводим сообщение об удачной инициализации
    Serial.println("Initialization completed");
    Serial.println("Gyroscope\t\t\tAccelerometer\t\t\tCompass\t\tBarometer");
}

void loop() {
    // вывод угловой скорости в градусах в секунду относительно оси X
    Serial.print(gyro.readRotationDegX());
    Serial.print("\t");
    // вывод угловой скорости в градусах в секунду относительно оси Y
    Serial.print(gyro.readRotationDegY());
    Serial.print("\t");
    // вывод угловой скорости в градусах в секунду относительно оси Z
    Serial.print(gyro.readRotationDegZ());
    Serial.print("\t\t");
    // вывод направления и величины ускорения в м/с² по оси X
    Serial.print(accel.readAccelerationAX());
    Serial.print("\t");
    // вывод направления и величины ускорения в м/с² по оси Y
    Serial.print(accel.readAccelerationAY());
    Serial.print("\t");
    // вывод направления и величины ускорения в м/с² по оси Z
    Serial.print(accel.readAccelerationAZ());
    Serial.print("\t\t");
    // выводим азимут относительно оси Z
    Serial.print(compass.readAzimut());
    Serial.print(" Degrees\t");
    // вывод значения абсолютного давления
    Serial.print(barometer.readPressureMillibars());
    Serial.print("\t");
    // вывод значения температуры окружающей среды
    Serial.print(barometer.readTemperatureC());
    Serial.print("\t");
    Serial.println("");
    delay(100);
}
