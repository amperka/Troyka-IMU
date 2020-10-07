// Библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// Создаём объект для работы с иагнитометром/компасом
Compass compass;

void setup() {
    // Открываем последовательный порт
    Serial.begin(9600);
    // Инициализируем компас
    compass.begin();
    // Устанавливаем чувствительность компаса
    // ±4 gauss (по умолчанию), ±8 gauss, ±12 gauss, ±16 gauss
    compass.setRange(RANGE_4_GAUSS);
}

void loop() {
    // Выводим «сырые» значения компаса по трём осям
    Serial.print(compass.readX());
    Serial.print(",");
    Serial.print(compass.readY());
    Serial.print(",");
    Serial.println(compass.readZ());
    delay(100);
}
