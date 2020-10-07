// Библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// Создаём объект для работы с гироскопом
Gyroscope gyro;
// Создаём объект для работы с акселерометром
Accelerometer accel;
// Создаём объект для работы с магнитометром/компасом
Compass compass;
// Создаём объект для работы с акселерометром
Barometer barometer;

// Калибровочные значения, полученные в калибровочной матрице
// из примера compassCalibration
const float compassCalibrationBias[3] = { 2269.685, -3415.288, 4698.337 };

const float compassCalibrationMatrix[3][3] = { { 2.464, 0.133, 0.009 },
                                               { 0.09, 3.081, 0.016 },
                                               { -0.003, -0.225, 2.922 } };

void setup() {
    // Открываем последовательный порт
    Serial.begin(9600);
    // Выводим сообщение о начале инициализации
    Serial.println("IMU Begin");
    // Инициализируем гироскоп
    gyro.begin();
    // Инициализируем акселерометр
    accel.begin();
    // Инициализируем компас
    compass.begin();
    // Инициализируем барометр
    barometer.begin();
    // Устанавливаем калибровочные данные
    compass.setCalibrateMatrix(compassCalibrationMatrix, compassCalibrationBias);
    // Выводим сообщение об удачной инициализации
    Serial.println("Initialization completed");
    Serial.println("Gyroscope\t\t\tAccelerometer\t\t\tCompass\t\tBarometer");
}

void loop() {
    // Выводим угловую скорость в градусах в секунду относительно оси X
    Serial.print(gyro.readRotationDegX());
    Serial.print("\t");
    // Выводим угловую скорость в градусах в секунду относительно оси Y
    Serial.print(gyro.readRotationDegY());
    Serial.print("\t");
    // Выводим угловую скорость в градусах в секунду относительно оси Z
    Serial.print(gyro.readRotationDegZ());
    Serial.print("\t\t");
    // Выводим направления и величины ускорения в м/с² по оси X
    Serial.print(accel.readAccelerationAX());
    Serial.print("\t");
    // Выводим направления и величины ускорения в м/с² по оси Y
    Serial.print(accel.readAccelerationAY());
    Serial.print("\t");
    // Выводим направления и величины ускорения в м/с² по оси Z
    Serial.print(accel.readAccelerationAZ());
    Serial.print("\t\t");
    // Выводим азимут относительно оси Z
    Serial.print(compass.readAzimut());
    Serial.print(" Degrees\t");
    // Выводим значения абсолютного давления
    Serial.print(barometer.readPressureMillibars());
    Serial.print("\t");
    // Выодим значения температуры окружающей среды
    Serial.print(barometer.readTemperatureC());
    Serial.print("\t");
    Serial.println("");
    delay(100);
}
