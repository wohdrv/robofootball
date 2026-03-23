#include <BluetoothSerial.h>
#include <esp_system.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

BluetoothSerial SerialBT;

int data[4] = {0, 0, 0, 0};
int array_index = 0;

// ПИНЫ МОТОРОВ
const int D0 = 33; const int D1 = 25; // FL
const int D2 = 26; const int D3 = 27; // FR
const int D0b = 23; const int D1b = 22; // RL (BL)
const int D2b = 19; const int D3b = 18; // RR (BR)

const int PWM_FREQ = 1000;
const int PWM_RESOLUTION = 8;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  
  Serial.begin(115200);
  SerialBT.begin("sassafrass");

  ledcAttach(D0, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(D1, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(D2, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(D3, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(D0b, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(D1b, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(D2b, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(D3b, PWM_FREQ, PWM_RESOLUTION);
  
  Serial.println("Система готова");
}

void loop() {
  if (SerialBT.available()) {
    int in_byte = SerialBT.read();

    // Если пришел маркер начала пакета
    if (in_byte == 255) {
      array_index = 0;
    }
    
    // Записываем данные в массив (не больше 4 байт, чтобы не выйти за пределы)
    if (array_index < 4) {
      data[array_index] = in_byte;
      array_index++;
    }

    // Когда получили весь пакет (маркер + 3 значения джойстиков)
    if (array_index == 4) {
      // Расшифровка
      int x2_raw = data[1]; // Joy 1 X → поворот (swap!)
      int y1_raw = data[2]; // Joy 1 Y → вперёд/назад
      int x1_raw = data[3]; // Joy 2 X → стрейф  (swap!)

      // Преобразование в -100...100
      int x1 = x1_raw - 100;
      int y1 = 100 - y1_raw;
      int x2 = x2_raw - 100; // Поворот

      // Мертвая зона
      if (abs(x1) < 15) x1 = 0;
      if (abs(y1) < 15) y1 = 0;
      if (abs(x2) < 15) x2 = 0;

      // КИНЕМАТИКА MECANUM
      // x1 - стрейф (боком)
      // y1 - вперед/назад
      // x2 - вращение (используем Joy 2 X)
      
      float fl = (y1 + x1 + x2) * 2.5; 
      float fr = (y1 - x1 - x2) * 2.5; 
      float bl = (y1 - x1 + x2) * 2.5; 
      float br = (y1 + x1 - x2) * 2.5;

      // Подача на моторы
      setMotor(D0, D1, fl);   // Передний левый
      setMotor(D2, D3, fr);   // Передний правый
      setMotor(D0b, D1b, bl); // Задний левый
      setMotor(D2b, D3b, br); // Задний правый
    }
  }
}

void setMotor(int pinA, int pinB, int speed) {
  int s = constrain(abs((int)speed), 0, 255);

  if (speed > 0) {
    ledcWrite(pinA, s);
    ledcWrite(pinB, 0);
  } else if (speed < 0) {
    ledcWrite(pinA, 0);
    ledcWrite(pinB, s);
  } else {
    ledcWrite(pinA, 0);
    ledcWrite(pinB, 0);
  }
}