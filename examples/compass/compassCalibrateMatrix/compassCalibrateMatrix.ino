
// библиотека для работы с модулями IMU
#include <TroykaIMU.h>
 
// создаём объект для работы с компасом
Compass compass(COMPASS_ADDRESS_V1);

// если напаяна перемычка, устройство доступно по новому адресу
// Compass compass(COMPASS_ADDRESS_V2);

void setup()
{
  // открываем последовательный порт
  Serial.begin(9600);
  // инициализация компаса
  compass.begin();
  // устанавливаем чувствительность компаса
  // ±4 gauss — по умолчанию, ±8 gauss, ±12 gauss, ±16 gauss
  compass.setRange(RANGE_4_GAUSS);
}
 
void loop()
{
  // Выводим «сырые» значения компаса по трём осям
  Serial.print(compass.readX());
  Serial.print(",");
  Serial.print(compass.readY());
  Serial.print(",");
  Serial.println(compass.readZ());
  delay(100);
}
