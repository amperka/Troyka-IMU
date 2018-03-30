// библиотека для работы с модулями IMU
#include <TroykaIMU.h>
 
// создаём объект для работы с гироскопом
Gyroscope gyro(GYRO_ADDRESS_V1);
// создаём объект для работы с акселерометром
Accelerometer accel(ACCEL_ADDRESS_V1);
// создаём объект для работы с компасом
Compass compass(COMPASS_ADDRESS_V1);
// создаём объект для работы с барометром
Barometer barometer(BARO_ADDRESS_V1);

// если напаяны перемычки, устройства доступны по новому адресу
// Gyroscope gyro(GYRO_ADDRESS_V2);
// Accelerometer accel(ACCEL_ADDRESS_V2);
// Compass compass(COMPASS_ADDRESS_V2);
// Barometer barometer(BARO_ADDRESS_V2);

// калибровочные значения компаса
// полученные в калибровочной матрице из примера «compassCalibrateMatrix»
const double compassCalibrationBias[3] = {
  524.21,
  3352.214,
  -1402.236
};
 
const double compassCalibrationMatrix[3][3] = {
  {1.757, 0.04, -0.028},
  {0.008, 1.767, -0.016},
  {-0.018, 0.077, 1.782}
};
 
void setup()
{
  // открываем последовательный порт
  Serial.begin(115200);
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
  // калибровка компаса
  compass.calibrateMatrix(compassCalibrationMatrix, compassCalibrationBias);
  // выводим сообщение об удачной инициализации
  Serial.println("Initialization completed");
  Serial.println("Gyroscope\t\t\tAccelerometer\t\t\tCompass\t\tBarometer");
}
 
void loop()
{
  // вывод угловой скорости в градусах в секунду относительно оси X
  Serial.print(gyro.readDegPerSecX());
  Serial.print("\t");
  // вывод угловой скорости в градусах в секунду относительно оси Y
  Serial.print(gyro.readDegPerSecY());
  Serial.print("\t");
  // вывод угловой скорости в градусах в секунду относительно оси Z
  Serial.print(gyro.readDegPerSecZ());
  Serial.print("\t\t");
  // вывод направления и величины ускорения в м/с² по оси X
  Serial.print(accel.readAX());
  Serial.print("\t");
  // вывод направления и величины ускорения в м/с² по оси Y
  Serial.print(accel.readAY());
  Serial.print("\t");
  // вывод направления и величины ускорения в м/с² по оси Z
  Serial.print(accel.readAZ());
  Serial.print("\t\t");
  // выводим азимут относительно оси Z
  Serial.print(compass.readAzimut());
  Serial.print(" Degrees\t");
  // вывод значения абсолютного давления
  Serial.print(barometer.readPressureMillibars());
  Serial.print("\t");
  // вывод значения температуры окружающей среды
  Serial.print(barometer.readTemperatureC());
  Serial.print("\t");
  Serial.println("");
  delay(100);
}
