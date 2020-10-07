// Библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// Создаём объект для работы с гироскопом
Gyroscope gyro;

void setup() {
    // Открываем последовательный порт
    Serial.begin(9600);
    // Выводим сообщение о начале инициализации
    Serial.println("Gyroscope begin");
    // Инициализируем гироскоп
    gyro.begin();
    // Устанавливаем чувствительность гироскопа
    // 250dps (по умолчанию), 500dps, 2000dps
    gyro.setRange(RANGE_250DPS);
    // Выводим сообщение об удачной инициализации
    Serial.println("Initialization completed");
}

void loop() {
    // Выводим угловую скорость в градусах в секунду относительно оси X
    Serial.print(gyro.readRotationDegX());
    Serial.print("\t\t");
    // Выводим угловую скорость в градусах в секунду относительно оси Y
    Serial.print(gyro.readRotationDegY());
    Serial.print("\t\t");
    // Выводим угловую скорость в градусах в секунду относительно оси Z
    Serial.print(gyro.readRotationDegZ());
    Serial.print("\t\t");
    Serial.println();
    delay(100);
}
