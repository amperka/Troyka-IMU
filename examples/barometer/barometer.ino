// библиотека для работы I²C
#include <Wire.h>
// библиотека для работы с модулями IMU
#include <troyka-imu.h>
// создаём объект для работы с барометром
Barometer barometer;

void setup()
{
  // открываем последовательный порт
  Serial.begin(9600);

  // выводим сообщение о начале инициализации
  Serial.println("Begin init...");
  // инициализация барометра
  barometer.begin();
  // выводим сообщение об удачной инициализации
  Serial.println("Init completed");
}

void loop()
{
  // создаём переменную и присваиваем ей значения абсолютного давления
  float pressure = barometer.readPressureMillibars();
  // создаём переменную и присваиваем ей значения высоты над уровнем море
  float altitude = barometer.pressureToAltitudeMeters(pressure);
  // создаём переменную и присваиваем ей температуру окружающей среды
  float temperature = barometer.readTemperatureC();

  // Вывод данных в Serial порт
  Serial.print("p: ");
  Serial.print(pressure);
  Serial.print(" mbar \t");
  Serial.print("h: ");
  Serial.print(altitude);
  Serial.print(" m \t");
  Serial.print("t: ");
  Serial.print(temperature);
  Serial.println(" C");
  delay(300);
}
