// Библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// Создаём объект для фильтра Madgwick
Madgwick filter;
// Создаём объект для работы с гироскопом
Gyroscope gyroscope;
// Создаём объект для работы с акселерометром
Accelerometer accelerometer;
// Создаём объект для работы с компасом
Compass compass;

// Переменные для данных с гироска, акселерометра и компаса
float gx, gy, gz, ax, ay, az, mx, my, mz;

// Переменные для хранения самолётных углов ориентации
float yaw, pitch, roll;

// Переменная для хранения частоты фильтра
float fps = 100;

// Калибровочные значения, полученные в калибровочной матрице
// из примера compassCalibration
const float compassCalibrationBias[3] = { 567.893, -825.35, 1061.436 };

const float compassCalibrationMatrix[3][3] = { { 1.909, 0.082, 0.004 },
                                               { 0.049, 1.942, -0.235 },
                                               { -0.003, 0.008, 1.944 } };

void setup() {
    // Открываем последовательный порт
    Serial.begin(9600);
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
    filter.setFrequency(fps);
    // Обновляем входные данные в фильтр
    filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);

    if (Serial.available() > 0) {
        int val = Serial.read();
        // Если пришёл символ 's'
        if (val == 's') {
            float q0, q1, q2, q3;
            filter.readQuaternions(q0, q1, q2, q3);
            // Выводим кватернионы в serial-порт
            Serial.print(q0);
            Serial.print(",");
            Serial.print(q1);
            Serial.print(",");
            Serial.print(q2);
            Serial.print(",");
            Serial.println(q3);
        }
    }
    // Вычисляем затраченное время на обработку данных
    unsigned long deltaMillis = millis() - startMillis;
    // Вычисляем частоту обработки фильтра
    fps = 1000 / deltaMillis;
}