// библиотека для работы с модулями IMU
#include <TroykaIMU.h>
 
// создаём объект для работы с компасом
Compass compass(COMPASS_ADDRESS_V1);

// если напаяна перемычка, устройство доступно по новому адресу
// Compass compass(COMPASS_ADDRESS_V2);
 
// калибровочные значения, полученные в калибровочной матрице
// из примера compass_cal_matrix
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
  // пока не появились данные с USB
  // выводим сообщение о начале инициализации
  Serial.println("Begin init...");
  // инициализация компаса
  compass.begin();
  // устанавливаем чувствительность компаса
  // ±4 gauss — по умолчанию, ±8 gauss, ±12 gauss, ±16 gauss
  compass.setRange(RANGE_4_GAUSS);
  // калибровка компаса
  compass.calibrateMatrix(compassCalibrationMatrix, compassCalibrationBias);
  // выводим сообщение об удачной инициализации
  Serial.println("Initialization completed");
}
 
void loop()
{
  // выводим азимут относительно оси Z
  Serial.print(compass.readAzimut());
  Serial.println(" Degrees");
  delay(100);
}
