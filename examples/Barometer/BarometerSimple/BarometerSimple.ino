// Библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// Создаём объект для работы с акселерометром
Barometer barometer;

void setup() {
    // Открываем Serial-порт
    Serial.begin(9600);
    // Выводим сообщение о начале инициализации
    Serial.println("Barometer begin");
    // Инициализируем барометр
    barometer.begin();
    // Выводим сообщение об удачной инициализации
    Serial.println("Initialization completed");
}

void loop() {
    // Создаём переменную для значения атмосферного давления в Паскалях
    float pressurePascals = barometer.readPressurePascals();
    // Создаём переменную для значения атмосферного давления в мм рт.ст.
    float pressureMillimetersHg = barometer.readPressureMillimetersHg();
    // Создаём переменную для значения высоты над уровнем море
    float altitude = barometer.readAltitude();
    // Создаём переменную для значения температуры окружающей среды
    float temperature = barometer.readTemperatureC();

    // Вывод данных в Serial-порт
    Serial.print("Pressure: ");
    Serial.print(pressurePascals);
    Serial.print(" Pa\t");
    Serial.print(pressureMillimetersHg);
    Serial.print(" mmHg\t");
    Serial.print("Height: ");
    Serial.print(altitude);
    Serial.print(" m \t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
    delay(100);
}
