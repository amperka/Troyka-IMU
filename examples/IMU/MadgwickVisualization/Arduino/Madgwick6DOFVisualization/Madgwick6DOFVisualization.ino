// Библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// Создаём объект для фильтра Madgwick
Madgwick filter;
// Создаём объект для работы с гироскопом
Gyroscope gyroscope;
// Создаём объект для работы с акселерометром
Accelerometer accelerometer;

// Переменные для данных с гироска и акселерометра и компаса
float gx, gy, gz, ax, ay, az;

// Переменные для хранения самолётных углов ориентации
float yaw, pitch, roll;

// Переменная для хранения частоты выборок фильтра
float fps = 100;

void setup() {
    // Открываем последовательный порт
    Serial.begin(9600);
    // Инициализируем гироскоп
    gyroscope.begin();
    // Инициализируем акселерометр
    accelerometer.begin();
    // Инициализируем фильтр
    filter.begin();
}

void loop() {
    // Запоминаем текущее время
    unsigned long startMillis = millis();

    // Считываем данные с акселерометра в единицах G
    accelerometer.readAccelerationGXYZ(ax, ay, az);
    // Считываем данные с гироскопа в радианах в секунду
    gyroscope.readRotationRadXYZ(gx, gy, gz);

    // Устанавливаем частоту фильтра
    filter.setFrequency(fps);
    // Обновляем входные данные в фильтр
    filter.update(gx, gy, gz, ax, ay, az);

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