// библитоека для работы I²C
#include <Wire.h>
// библиотека для работы с модулями IMU
#include <troyka-imu.h>

// создаём объект для работы с гироскопом
Gyroscope gyro;

void setup()
{
  // открываем последовательный порт
  Serial.begin(9600);

  // выводим сообщение о начале инициализации
  Serial.println("Begin init...");
  // инициализация гироскопа
  gyro.begin();
  // выводим сообщение об удачной инициализации
  Serial.println("Init completed");
  // устанавливаем чувствительность
  gyro.setRange(RANGE_250);
}

void loop()
{
  // вывод угловой скорости относительно оси X
  Serial.print(gyro.readX_DegPerSec());
  Serial.print("\t\t");
  // вывод угловой скорости относительно оси Y
  Serial.print(gyro.readY_DegPerSec());
  Serial.print("\t\t");
  // вывод угловой скорости относительно оси Z
  Serial.print(gyro.readZ_DegPerSec());
  Serial.print("\t\t");
  Serial.println("");
  delay(300);
}
