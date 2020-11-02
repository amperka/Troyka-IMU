// Пример выводит сырые значения магнитометра, которые
// используются для последующей калибровки сенсора
// Подробности читайте в документации про калибровку магнитометра
// http://wiki.amperka.ru/articles:troyka-magnetometer-compass-calibrate

// Библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// Создаём объект для работы с магнитометром/компасом
Compass compass;

void setup() {
    // Открываем последовательный порт
    Serial.begin(9600);
    // Инициализируем компас
    compass.begin();
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
