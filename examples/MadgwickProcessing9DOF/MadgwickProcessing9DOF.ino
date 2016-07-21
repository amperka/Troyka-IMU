// скетч для вывода кватернионов в serial-порт
// для дальнейшего графического просмотра ориентации объекта
// в среде processing «MadgwickProcessingDraw9DOF.pde»
 
// библиотека для работы I²C
#include <Wire.h>
// библиотека для работы с модулями IMU
#include <TroykaIMU.h>
 
// множитель фильтра
#define BETA 0.22
 
// создаём объект для фильтра Madgwick
Madgwick filter;
 
// создаём объект для работы с акселерометром
Accelerometer accel;
// создаём объект для работы с гироскопом
Gyroscope gyro;
// создаём объект для работы с компасом
Compass compass;
 
// переменные для данных с гироскопа, акселерометра и компаса
float gx, gy, gz, ax, ay, az, mx, my, mz;
 
// получаемые углы ориентации (Эйлера)
float yaw, pitch, roll;
 
// переменная для хранения частоты выборок фильтра
float fps;
 
// переменная для подсчета времени, чтобы определять
// частоту обновления каждого фильтра
unsigned long prevMillis;
 
// калибровочные значения компаса
// полученные в калибровочной матрице из примера «compassCalibrateMatrixx»
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
  // инициализация акселерометра
  accel.begin();
  // инициализация гироскопа
  gyro.begin();
  // инициализация компаса
  compass.begin();
  // задаем начальное ненулевое значение в переменную
  prevMillis = millis();
  // калибровка компаса
  compass.calibrateMatrix(compassCalibrationMatrix, compassCalibrationBias);
}
 
void loop()
{
  // запоминаем текущее время
  unsigned long currMillis = millis();
  // вычисляем затраченное время на обработку данных
  // предыдущего запроса фильтра
  unsigned long deltaMillis = currMillis - prevMillis;
  // вычисляем частоту обработки фильтра
  fps = 1000 / deltaMillis;
 
  // считываем данные с акселерометра в единицах G
  accel.readGXYZ(&ax, &ay, &az);
  // считываем данные с гироскопа в радианах в секунду
  gyro.readRadPerSecXYZ(&gx, &gy, &gz);
  // считываем данные с компаса в Гауссах
  compass.readCalibrateGaussXYZ(&mx, &my, &mz);
 
  // устанавливаем коэффициенты фильтра
  filter.setKoeff(fps, BETA);
  // обновляем входные данные в фильтр
  filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);
 
  if (Serial.available() > 0) {
    int val = Serial.read();
    // если пришёл символ 's'
    if (val == 's') {
    // выводим кватернионы в serial-порт
    filter.printQuaternions();
    }
  }
  // сохраняем текущее время
  prevMillis = currMillis;
}
