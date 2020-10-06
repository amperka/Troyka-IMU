// библиотека для работы с модулями IMU
#include <TroykaIMU.h>

// создаём объект для работы с компасом
Compass compass(COMPASS_ADDRESS_V1);

// если напаяна перемычка, устройство доступно по новому адресу
// Compass compass(COMPASS_ADDRESS_V2);

// калибровочные значения, полученные в калибровочной матрице
// из примера compass_cal_matrix
const float compassCalibrationBias[3] = { 2269.685, -3415.288, 4698.337 };

const float compassCalibrationMatrix[3][3] = { { 2.464, 0.133, 0.009 },
                                               { 0.09, 3.081, 0.016 },
                                               { -0.003, -0.225, 2.922 } };

void setup() {
    // открываем последовательный порт
    Serial.begin(9600);
    // пока не появились данные с USB
    // выводим сообщение о начале инициализации
    Serial.println("Begin init...");
    // инициализация компаса
    compass.begin();
    // устанавливаем чувствительность компаса
    // ±4 gauss — по умолчанию, ±8 gauss, ±12 gauss, ±16 gauss
    compass.setRange(RANGE_4_GAUSS);
    // калибровка компаса
    compass.setCalibrateMatrix(compassCalibrationMatrix, compassCalibrationBias);
    // выводим сообщение об удачной инициализации
    Serial.println("Initialization completed");
}

void loop() {
    // выводим азимут относительно оси Z
    Serial.print(compass.readAzimut());
    Serial.println(" Degrees");
    delay(100);
}
