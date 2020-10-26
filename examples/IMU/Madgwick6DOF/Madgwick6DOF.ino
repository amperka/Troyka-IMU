// Библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// Множитель фильтра
constexpr float BETA = 0.22;

// Создаём объект для фильтра Madgwick
Madgwick filter;
// Создаём объект для работы с гироскопом
Gyroscope gyroscope;
// Создаём объект для работы с акселерометром
Accelerometer accelerometer;

// Переменные для данных с гироска и акселерометра
float gx, gy, gz, ax, ay, az;

// Переменные для хранения самолётных углов ориентации
float yaw, pitch, roll;

// Переменная для хранения частоты выборок фильтра
float fps = 100;

void setup() {
    // Открываем последовательный порт
    Serial.begin(9600);
    // Выводим сообщение о начале инициализации
    Serial.println("IMU Begin");
    // Инициализируем гироскоп
    gyroscope.begin();
    // Инициализируем акселерометр
    accelerometer.begin();
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
    // Устанавливаем коэффициенты фильтра
    filter.setKoeff(fps, BETA);
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
    fps = 1000 / deltaMillis;
}
