// Библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// Создаём объект для фильтра Madgwick
Madgwick filter;
// Создаём объект для работы с гироскопом
Gyroscope gyroscope;
// Создаём объект для работы с акселерометром
Accelerometer accelerometer;

// Переменные для данных с гироскопа и акселерометра
float gx, gy, gz, ax, ay, az;

// Переменные для хранения самолётных углов ориентации
float yaw, pitch, roll;

// Переменная для хранения частоты выборок фильтра
float sampleRate = 100;

void setup() {
    // Открываем последовательный порт
    Serial.begin(9600);
    // Выводим сообщение о начале инициализации
    Serial.println("IMU Begin");
    // Инициализируем гироскоп
    gyroscope.begin();
    // Инициализируем акселерометр
    accelerometer.begin();
    // Инициализируем фильтр
    filter.begin();
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
    // Устанавливаем частоту фильтра
    filter.setFrequency(sampleRate);
    // Обновляем входные данные в фильтр
    filter.update(gx, gy, gz, ax, ay, az);

    // Получаем из фильтра углы: yaw, pitch и roll 
    yaw = filter.getYawDeg();
    pitch = filter.getPitchDeg();
    roll = filter.getRollDeg();

    // Выводим полученные углы Эйлера в Serial-порт
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
