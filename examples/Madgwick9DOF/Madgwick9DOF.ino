// библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// множитель фильтра
#define BETA 0.22

// создаём объект для фильтра Madgwick
Madgwick filter;

// создаём объект для работы с акселерометром
Accelerometer accel(ACCEL_ADDRESS_V1);
// создаём объект для работы с гироскопом
Gyroscope gyro(GYRO_ADDRESS_V1);
// создаём объект для работы с компасом
Compass compass(COMPASS_ADDRESS_V1);

// если напаяны перемычки, устройства доступны по новым адресам
// Accelerometer accel(ACCEL_ADDRESS_V2);
// Gyroscope gyro(GYRO_ADDRESS_V2);
// Compass compass(COMPASS_ADDRESS_V2);

// переменные для данных с гироскопа, акселерометра и компаса
float gx, gy, gz, ax, ay, az, mx, my, mz;

// получаемые углы ориентации (Эйлера)
float yaw, pitch, roll;

// переменная для хранения частоты выборок фильтра
float fps = 100;

// калибровочные значения компаса
// полученные в калибровочной матрице из примера «compassCalibrateMatrixx»
const float compassCalibrationBias[3] = { 2269.685, -3415.288, 4698.337 };

const float compassCalibrationMatrix[3][3] = { { 2.464, 0.133, 0.009 },
                                               { 0.09, 3.081, 0.016 },
                                               { -0.003, -0.225, 2.922 } };
void setup() {
    // открываем последовательный порт
    Serial.begin(9600);
    Serial.println("Begin init...");
    // инициализация акселерометра
    accel.begin();
    // инициализация гироскопа
    gyro.begin();
    // инициализация компаса
    compass.begin();

    // калибровка компаса
    compass.setCalibrateMatrix(compassCalibrationMatrix,
                               compassCalibrationBias);
    // выводим сообщение об удачной инициализации
    Serial.println("Initialization completed");
}

void loop() {
    // запоминаем текущее время
    unsigned long startMillis = millis();

    // считываем данные с акселерометра в единицах G
    accel.readAccelerationGXYZ(ax, ay, az);
    // считываем данные с гироскопа в радианах в секунду
    gyro.readRotationRadXYZ(gx, gy, gz);
    // считываем данные с компаса в Гауссах
    compass.readCalibrateMagneticGaussXYZ(mx, my, mz);

    // устанавливаем коэффициенты фильтра
    filter.setKoeff(fps, BETA);
    // обновляем входные данные в фильтр
    filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);

    // получение углов yaw, pitch и roll из фильтра
    yaw = filter.getYawDeg();
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
