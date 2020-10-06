// библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// создаём объект для работы с акселерометром
Accelerometer accel(ACCEL_ADDRESS_V1);

// если напаяна перемычка, устройство доступно по новому адресу
// Accelerometer accel(ACCEL_ADDRESS_V2);

void setup() {
    // открываем последовательный порт
    Serial.begin(9600);
    // выводим сообщение о начале инициализации
    Serial.println("Accelerometer init...");
    // инициализация акселерометра
    accel.begin();
    // устанавливаем чувствительность акселерометра
    // 2g — по умолчанию, 4g, 8g
    accel.setRange(RANGE_2G);
    // выводим сообщение об удачной инициализации
    Serial.println("Initialization completed");
}

void loop() {
    // вывод направления и величины ускорения в м/с² по оси X
    Serial.print(accel.readAccelerationAX());
    Serial.print("\t\t");
    // вывод направления и величины ускорения в м/с² по оси Y
    Serial.print(accel.readAccelerationAY());
    Serial.print("\t\t");
    // вывод направления и величины ускорения в м/с² по оси Z
    Serial.print(accel.readAccelerationAZ());
    Serial.print("\t\t");
    Serial.println("");
    delay(100);
}
