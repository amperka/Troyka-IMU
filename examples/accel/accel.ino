// библитоека для работы I²C
#include <Wire.h>
// библиотека для работы с модулями IMU
#include <troyka-imu.h>

// создаём объект для работы с акселерометром
Accelerometer accel;

void setup()
{
  // открываем последовательный порт
  Serial.begin(9600);
  // пока не появились данные с USB
  while (!Serial.available()) {
    // ждём
  }
  // выводим сообщение о начале инициализации
  Serial.println("Begin init...");
  // инициализация акселерометра
  accel.begin();
  // выводим сообщение об удачной инициализации
  Serial.println("Init completed");
  // устанавливаем чувствительность
  accel.setRange(RANGE_2);
}

void loop()
{
  // вывод направления и величины ускорения по оси X
  Serial.print(accel.readX_G());
  Serial.print("\t\t");
  // вывод направления и величины ускорения по оси Y
  Serial.print(accel.readY_G());
  Serial.print("\t\t");
  // вывод направления и величины ускорения по оси Z
  Serial.print(accel.readZ_G());
  Serial.print("\t\t");
  Serial.println("");
  delay(300);
}
