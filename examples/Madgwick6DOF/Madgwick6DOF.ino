// библиотека для работы с модулями IMU
#include <TroykaIMU.h>
 
// множитель фильтра
#define BETA 0.22f
 
// создаём объект для фильтра Madgwick
Madgwick filter;
 
// создаём объект для работы с акселерометром
Accelerometer accel(ACCEL_ADDRESS_V1);
// создаём объект для работы с гироскопом
Gyroscope gyro(GYRO_ADDRESS_V1);

// если напаяны перемычки, устройства доступны по новым адресам
// Accelerometer accel(ACCEL_ADDRESS_V2);
// Gyroscope gyro(GYRO_ADDRESS_V2);
 
// переменные для данных с гироскопов, акселерометров
float gx, gy, gz, ax, ay, az;
 
// получаемые углы ориентации
float yaw, pitch, roll;
 
// переменная для хранения частоты выборок фильтра
float fps = 100;
 
void setup()
{
  // открываем последовательный порт
  Serial.begin(115200);
  Serial.println("Begin init...");
  // инициализация акселерометра
  accel.begin();
  // инициализация гироскопа
  gyro.begin();
  // выводим сообщение об удачной инициализации
  Serial.println("Initialization completed");
}
 
void loop()
{
  // запоминаем текущее время
  unsigned long startMillis = millis();
 
  // считываем данные с акселерометра в единицах G
  accel.readGXYZ(&ax, &ay, &az);
  // считываем данные с акселерометра в радианах в секунду
  gyro.readRadPerSecXYZ(&gx, &gy, &gz);
  // устанавливаем коэффициенты фильтра
  filter.setKoeff(fps, BETA);
  // обновляем входные данные в фильтр
  filter.update(gx, gy, gz, ax, ay, az);
 
  // получение углов yaw, pitch и roll из фильтра
  yaw =  filter.getYawDeg();
  pitch = filter.getPitchDeg();
  roll = filter.getRollDeg();
 
  // выводим полученные углы в serial-порт
  Serial.print("yaw: ");
  Serial.print(yaw);
  Serial.print("\t\t");
  Serial.print("pitch: ");
  Serial.print(pitch);
  Serial.print("\t\t");
  Serial.print("roll: ");
  Serial.println(roll);
 
  // вычисляем затраченное время на обработку данных
  unsigned long deltaMillis = millis() - startMillis;
  // вычисляем частоту обработки фильтра
  fps = 1000 / deltaMillis;
}
