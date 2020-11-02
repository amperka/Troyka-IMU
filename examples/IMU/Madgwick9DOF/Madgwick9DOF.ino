// Библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// Создаём объект для фильтра Madgwick
Madgwick filter;
// Создаём объект для работы с гироскопом
Gyroscope gyroscope;
// Создаём объект для работы с акселерометром
Accelerometer accelerometer;
// Создаём объект для работы с магнитометром/компасом
Compass compass;

// Переменные для данных с гироскопа, акселерометра и компаса
float gx, gy, gz, ax, ay, az, mx, my, mz;

// Переменные для хранения самолётных углов ориентации
float yaw, pitch, roll;

// Переменная для хранения частоты выборок фильтра
float sampleRate = 100;

// Калибровочные данные для работы магнитометра в режиме компаса
// Подробности читайте в документации про калибровку модуля
// http://wiki.amperka.ru/articles:troyka-magnetometer-compass-calibrate 
const float compassCalibrationBias[3] = { 567.893, -825.35, 1061.436 };

const float compassCalibrationMatrix[3][3] = { { 1.909, 0.082, 0.004 },
                                               { 0.049, 1.942, -0.235 },
                                               { -0.003, 0.008, 1.944} };

void setup() {
    // Открываем последовательный порт
    Serial.begin(9600);
    // Выводим сообщение о начале инициализации
    Serial.println("IMU Begin");
    // Инициализируем гироскоп
    gyroscope.begin();
    // Инициализируем акселерометр
    accelerometer.begin();
    // Инициализируем компас
    compass.begin();
    // Инициализируем фильтр
    filter.begin();
    // Устанавливаем калибровочные данные
    compass.setCalibrateMatrix(compassCalibrationMatrix,
                               compassCalibrationBias);
    // Выводим сообщение об удачной инициализации
    Serial.println("Initialization completed");
}

void loop() {
    // Запоминаем текущее время
    unsigned long startMillis = millis();

    // Считываем данные с акселерометра в единицах G
    accelerometer.readAccelerationGXYZ(ax, ay, az);
    // Считываем данные с гироскопа в радианах в секунду
    gyroscope.readRotationRadXYZ(gx, gy, gz);
    // Считываем данные с компаса в Гауссах
    compass.readCalibrateMagneticGaussXYZ(mx, my, mz);
    // Устанавливаем частоту фильтра
    filter.setFrequency(sampleRate);
    // Обновляем входные данные в фильтр
    filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);

    // Получаем из фильтра углы: yaw, pitch и roll
    yaw = filter.getYawDeg();
    pitch = filter.getPitchDeg();
    roll = filter.getRollDeg();

    // Выводим полученные углы Эйлера в serial-порт
    Serial.print("yaw: ");
    Serial.print(yaw);
    Serial.print("\t\t");
    Serial.print("pitch: ");
    Serial.print(pitch);
    Serial.print("\t\t");
    Serial.print("roll: ");
    Serial.println(roll);

    // Вычисляем затраченное время на обработку данных
    unsigned long deltaMillis = millis() - startMillis;
    // Вычисляем частоту обработки фильтра
    sampleRate = 1000 / deltaMillis;
}
