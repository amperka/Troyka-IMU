// Библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// Создаём объект для работы с акселерометром
Accelerometer accel;

void setup() {
    // Открываем последовательный порт
    Serial.begin(9600);
    // Выводим сообщение о начале инициализации
    Serial.println("Accelerometer begin");
    // Инициализируем акселерометр
    accel.begin();
    // Устанавливаем чувствительность акселерометра
    // 2g (по умолчанию), 4g, 8g
    accel.setRange(RANGE_2G);
    // Выводим сообщение об удачной инициализации
    Serial.println("Initialization completed");
}

void loop() {
    // Выводим направления и величины ускорения в м/с² по оси X
    Serial.print(accel.readAccelerationAX());
    Serial.print("\t\t");
    // Выводим направления и величины ускорения в м/с² по оси Y
    Serial.print(accel.readAccelerationAY());
    Serial.print("\t\t");
    // Выводим направления и величины ускорения в м/с² по оси Z
    Serial.print(accel.readAccelerationAZ());
    Serial.print("\t\t");
    Serial.println("");
    delay(100);
}
