// Библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// Создаём объект для работы с акселерометром
Accelerometer accelerometer;

void setup() {
    // Открываем последовательный порт
    Serial.begin(9600);
    // Выводим сообщение о начале инициализации
    Serial.println("Accelerometer begin");
    // Инициализируем акселерометр
    accelerometer.begin();
    // Выводим сообщение об удачной инициализации
    Serial.println("Initialization completed");
}

void loop() {
    // Выводим направления и величины ускорения в м/с² по оси X
    Serial.print(accelerometer.readAccelerationAX());
    Serial.print("\t\t");
    // Выводим направления и величины ускорения в м/с² по оси Y
    Serial.print(accelerometer.readAccelerationAY());
    Serial.print("\t\t");
    // Выводим направления и величины ускорения в м/с² по оси Z
    Serial.print(accelerometer.readAccelerationAZ());
    Serial.print("\t\t");
    Serial.println();
    delay(100);
}
