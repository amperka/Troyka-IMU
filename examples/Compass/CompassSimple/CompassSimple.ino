// Библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// Создаём объект для работы с магнитометром/компасом
Compass compass;

void setup() {
    // Открываем последовательный порт
    Serial.begin(9600);
    // Выводим сообщение о начале инициализации
    Serial.println("Compass begin");
    // Инициализируем компас
    compass.begin();
    // Выводим сообщение об удачной инициализации
    Serial.println("Initialization completed");
}

void loop() {
    // Выводим напряженность магнитного поля в Гауссах по оси X
    Serial.print(compass.readMagneticGaussX());
    Serial.print("\t\t");
    // Выводим напряженность магнитного поля в Гауссах по оси Y
    Serial.print(compass.readMagneticGaussY());
    Serial.print("\t\t");
    // Выводим напряженность магнитного поля в Гауссах по оси Z
    Serial.print(compass.readMagneticGaussZ());
    Serial.println();
    delay(100);
}
