// библиотека для работы I²C
#include <Wire.h>
// библиотека для работы с модулями IMU
#include <troyka-imu.h>

// создаём объект для работы с гироскопом
Gyroscope gyro;
// создаём объект для работы с акселерометром
Accelerometer accel;
// создаём объект для работы с компасом
Compass compass;
// создаём объект для работы с барометром
Barometer barometer;

void setup()
{
  // открываем последовательный порт
  Serial.begin(9600);

  // выводим сообщение о начале инициализации
  Serial.println("Begin init...");
  
  // инициализация гироскопа
  gyro.begin();
  // инициализация акселерометра
  accel.begin();
  // инициализация компаса
  compass.begin();
  // инициализация барометра
  barometer.begin();
  // выводим сообщение об удачной инициализации
  Serial.println("Init completed");
  Serial.println("Gyroscope\t\t\tAccelerometer\t\t\tCompass\t\tBarometer");
}

void loop()
{
  // вывод угловой скорости относительно оси X
  Serial.print(gyro.readX_DegPerSec());
  Serial.print("\t");
  // вывод угловой скорости относительно оси Y
  Serial.print(gyro.readY_DegPerSec());
  Serial.print("\t");
  // вывод угловой скорости относительно оси Z
  Serial.print(gyro.readZ_DegPerSec());
  Serial.print("\t\t");
  
  // вывод направления и величины ускорения по оси X
  Serial.print(accel.readX_G());
  Serial.print("\t");
  // вывод направления и величины ускорения по оси Y
  Serial.print(accel.readY_G());
  Serial.print("\t");
  // вывод направления и величины ускорения по оси Z
  Serial.print(accel.readZ_G());
  Serial.print("\t\t");
  
  // калибровка компаса
  compass.readXYZ_Calib();
  // выводим азимут относительно оси X
  Serial.print(compass.read_Yaw());
  Serial.print(" Degrees\t");
  
  // вывод значения абсолютного давления
  Serial.print(barometer.readPressureMillibars());
  Serial.print("\t");
  // вывод значения температуры окружающей среды
  Serial.print(barometer.readTemperatureC());
  Serial.print("\t");
  
  Serial.println("");
  delay(300);
}
