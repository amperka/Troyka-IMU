// Библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// Создаём объект для работы с иагнитометром/компасом
Compass compass;

// Калибровочные значения, полученные в калибровочной матрице
// из примера compassCalibration
const float compassCalibrationBias[3] = { 2269.685, -3415.288, 4698.337 };

const float compassCalibrationMatrix[3][3] = { { 2.464, 0.133, 0.009 },
                                               { 0.09, 3.081, 0.016 },
                                               { -0.003, -0.225, 2.922 } };

void setup() {
    // Открываем последовательный порт
    Serial.begin(9600);
    // Выводим сообщение о начале инициализации
    Serial.println("Compass begin");
    // Инициализируем компас
    compass.begin();
    // Устанавливаем чувствительность компаса
    // ±4 gauss (по умолчанию), ±8 gauss, ±12 gauss, ±16 gauss
    compass.setRange(RANGE_4_GAUSS);
    // Устанавливаем калибровочные данные
    compass.setCalibrateMatrix(compassCalibrationMatrix,
                               compassCalibrationBias);
    // Выводим сообщение об удачной инициализации
    Serial.println("Initialization completed");
}

void loop() {
    // Выводим азимут относительно оси Z
    Serial.print(compass.readAzimut());
    Serial.println(" Degrees");
    delay(100);
}
