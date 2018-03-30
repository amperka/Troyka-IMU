// библиотека для работы I²C
#include <Wire.h>
// библиотека для работы с модулями IMU
#include <TroykaIMU.h>
 
// создаём объект для работы с гироскопом
Gyroscope gyro(GYRO_ADDRESS_V1);

// если напаяна перемычка, устройство доступно по новому адресу
// Gyroscope gyro(GYRO_ADDRESS_V2);
 
 
void setup()
{
  // открываем последовательный порт
  Serial.begin(115200);
  // выводим сообщение о начале инициализации
  Serial.println("Gyroscope init...");
  // инициализация гироскопа
  gyro.begin();
  // устанавливаем чувствительность гироскопа
  // 250dps — по умолчанию, 500dps, 2000dps
  gyro.setRange(RANGE_250DPS);
  // выводим сообщение об удачной инициализации
  Serial.println("Initialization completed");
}
 
void loop()
{
  // вывод угловой скорости в градусах в секунду относительно оси X
  Serial.print(gyro.readDegPerSecX());
  Serial.print("\t\t");
  // вывод угловой скорости в градусах в секунду относительно оси Y
  Serial.print(gyro.readDegPerSecY());
  Serial.print("\t\t");
  // вывод угловой скорости в градусах в секунду относительно оси Z
  Serial.print(gyro.readDegPerSecZ());
  Serial.print("\t\t");
  Serial.println("");
  delay(100);
/*
  // вывод угловой скорости в градусах в секунду относительно оси X, Y и Z
  float x, y, z;
  gyro.readDegPerSecXYZ(&x, &y, &z);
  Serial.print(x);
  Serial.print("\t\t");
  Serial.print(y);
  Serial.print("\t\t");
  Serial.print(z);
  Serial.println("");
  delay(100);
*/
}
