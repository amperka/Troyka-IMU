// Библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// Создаём объект для работы с гироскопом
Gyroscope gyroscope;
// Создаём объект для работы с акселерометром
Accelerometer accelerometer;
// Создаём объект для работы с магнитометром/компасом
Compass compass;
// Создаём объект для работы с барометром
Barometer barometer;

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
    // Инициализируем барометр
    barometer.begin();
    // Выводим сообщение об удачной инициализации
    Serial.println("Initialization completed");
    Serial.println("Gyroscope\t\t\tAccelerometer\t\t\tCompass\t\tBarometer");
}

void loop() {
    // Выводим угловую скорость в градусах в секунду относительно оси X, Y и Z
    Serial.print(gyroscope.readRotationDegX());
    Serial.print("\t");
    Serial.print(gyroscope.readRotationDegY());
    Serial.print("\t");
    Serial.print(gyroscope.readRotationDegZ());
    Serial.print("\t\t");
    // Выводим направления и величины ускорения в м/с² относительно оси X, Y и Z
    Serial.print(accelerometer.readAccelerationAX());
    Serial.print("\t");
    Serial.print(accelerometer.readAccelerationAY());
    Serial.print("\t");
    Serial.print(accelerometer.readAccelerationAZ());
    Serial.print("\t\t");
    // Выводим напряженность магнитного поля в Гауссах относительно оси X, Y и Z
    Serial.print(compass.readMagneticGaussX());
    Serial.print("\t");
    Serial.print(compass.readMagneticGaussY());
    Serial.print("\t");
    Serial.print(compass.readMagneticGaussZ());
    Serial.print("\t\t");
    // Выводим значения атмосферного давления в мм рт.ст.
    Serial.print(barometer.readPressureMillimetersHg());
    Serial.print("\t");
    // Выводим значения высоты над уровнем море
    Serial.print(barometer.readAltitude());
    Serial.print("\t");
    // Выводим значения температуры окружающей среды
    Serial.print(barometer.readTemperatureC());
    Serial.println();
    delay(100);
}
