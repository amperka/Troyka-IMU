// библиотека для работы с модулями IMU
#include <TroykaIMU.h>
 
// создаём объект для работы с акселерометром
Accelerometer accel(ACCEL_ADDRESS_V1);
 
// если напаяна перемычка, устройство доступно по новому адресу
// Accelerometer accel(ACCEL_ADDRESS_V2);

void setup()
{
  // открываем последовательный порт
  Serial.begin(115200);
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
 
void loop()
{
  // вывод направления и величины ускорения в м/с² по оси X
  Serial.print(accel.readAX());
  Serial.print("\t\t");
  // вывод направления и величины ускорения в м/с² по оси Y
  Serial.print(accel.readAY());
  Serial.print("\t\t");
  // вывод направления и величины ускорения в м/с² по оси Z
  Serial.print(accel.readAZ());
  Serial.print("\t\t");
  Serial.println("");
  delay(100);
  /*
  // вывод направления и величины ускорения в м/с² по X, Y и Z
  float x, y, z;
  accel.readAXYZ(&x, &y, &z);
  Serial.print(x);
  Serial.print("\t\t");
  Serial.print(y);
  Serial.print("\t\t");
  Serial.print(z);
  Serial.println("");
  delay(100);
  */
}
