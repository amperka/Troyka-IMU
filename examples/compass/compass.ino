// библиотека для работы I²C
#include <Wire.h>
// библиотека для работы с модулями IMU
#include <troyka-imu.h>

// создаём объект для работы с компасом
Compass compass;

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
  // инициализация компаса
  compass.begin();
  // выводим сообщение об удачной инициализации
  Serial.println("Init completed");
  // устанавливаем чувствительность
  compass.setRange(RANGE_4);
}

void loop()
{
  // калибровка компаса
  compass.readXYZ_Calib();
  // выводим азимут относительно оси X
  Serial.print(compass.read_Yaw());
  Serial.println(" Degrees");
  delay(300);
}
