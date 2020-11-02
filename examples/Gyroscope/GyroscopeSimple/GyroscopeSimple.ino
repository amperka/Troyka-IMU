// Библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// Создаём объект для работы с гироскопом
Gyroscope gyroscope;

void setup() {
    // Открываем последовательный порт
    Serial.begin(9600);
    // Выводим сообщение о начале инициализации
    Serial.println("Gyroscope begin");
    // Инициализируем гироскоп
    gyroscope.begin();
    // Выводим сообщение об удачной инициализации
    Serial.println("Initialization completed");
}

void loop() {
    // Выводим угловую скорость в градусах в секунду относительно оси X
    Serial.print(gyroscope.readRotationDegX());
    Serial.print("\t\t");
    // Выводим угловую скорость в градусах в секунду относительно оси Y
    Serial.print(gyroscope.readRotationDegY());
    Serial.print("\t\t");
    // Выводим угловую скорость в градусах в секунду относительно оси Z
    Serial.print(gyroscope.readRotationDegZ());
    Serial.print("\t\t");
    Serial.println();
    delay(100);
}
