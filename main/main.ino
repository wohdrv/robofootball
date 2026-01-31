#define W 'W'
#define A 'A'
#define S 'S'
#define D 'D'
#define L 'L'
#define R 'R'
#define Q 'Q'
#define E 'E'
#define Z 'Z'
#define X 'X'
#define P 'P'
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const int IR = 15; //ИК приемник
const int D0 = 33; // Мотор 1 - направление A
const int D1 = 25; // Мотор 1 - направление B
const int D2 = 26; // Мотор 2 - направление A
const int D3 = 27; // Мотор 2 - направление B

const int D0b = 23; // Мотор 3 - направление A
const int D1b = 22; // Мотор 3 - направление B
const int D2b = 19; // Мотор 4 - направление A
const int D3b = 18; // Мотор 4 - направление B

const int PWM_FREQ = 1000;      // Частота PWM 1 кГц
const int PWM_RESOLUTION = 8;   // 8-bit разрешение (0-255)

void setup() {
  Serial.begin(115200);

  SerialBT.begin("WinLeaders_1");

  // Настройка PWM для каждого пина
  ledcAttach(D0, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(D1, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(D2, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(D3, PWM_FREQ, PWM_RESOLUTION);

  ledcAttach(D0b, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(D1b, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(D2b, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(D3b, PWM_FREQ, PWM_RESOLUTION);
  
  Serial.println("Моторы инициализированы");
}

void loop() {
  if (SerialBT.available()) {
    char cmd = SerialBT.read();
    
    switch(cmd) {
      case 'W': moveForward(255); break;
      case 'A': moveLeft(255); break;
      case 'S': moveBackward(255); break;
      case 'D': moveRight(255); break;
      case 'R': turnRight(128); break;
      case 'L': turnLeft(128); break;
      case 'Q':
        ledcWrite(D2, 255);
        ledcWrite(D3, 0);
        ledcWrite(D2b, 255);
        ledcWrite(D3b, 0);
        break;
      case 'E':
        ledcWrite(D0, 255);
        ledcWrite(D1, 0);
        ledcWrite(D0b, 255);
        ledcWrite(D1b, 0);
        break;
      case 'Z':
        ledcWrite(D2, 0);
        ledcWrite(D3, 255);
        ledcWrite(D2b, 0);
        ledcWrite(D3b, 255);
        break;
      case 'X':
        ledcWrite(D0, 0);
        ledcWrite(D1, 255);
        ledcWrite(D0b, 0);
        ledcWrite(D1b, 255);
        break;
      case 'P': stopMotors(); break;

      default: break;
    }
  }
}

// Движение вперёд
void moveForward(int speed) {
  // Мотор 1 вперёд
  ledcWrite(D0, speed);
  ledcWrite(D1, 0);
  
  // Мотор 2 вперёд
  ledcWrite(D2, speed);
  ledcWrite(D3, 0);

  // Мотор 3 вперёд
  ledcWrite(D0b, speed);
  ledcWrite(D1b, 0);
  
  // Мотор 4 вперёд
  ledcWrite(D2b, speed);
  ledcWrite(D3b, 0);
}

// Движение назад
void moveBackward(int speed) {
  // Мотор 1 назад
  ledcWrite(D0, 0);
  ledcWrite(D1, speed);
  
  // Мотор 2 назад
  ledcWrite(D2, 0); 
  ledcWrite(D3, speed);

  // Мотор 3 назад
  ledcWrite(D0b, 0);
  ledcWrite(D1b, speed);
  
  // Мотор 4 назад
  ledcWrite(D2b, 0); 
  ledcWrite(D3b, speed);
}

// Движение вправо
void moveRight(int speed) {
  // Мотор 1 вперед
  ledcWrite(D0, speed);
  ledcWrite(D1, 0);
  
  // Мотор 2 назад
  ledcWrite(D2, 0); 
  ledcWrite(D3, speed);

  // Мотор 3 вперед
  ledcWrite(D0b, speed);
  ledcWrite(D1b, 0);
  
  // Мотор 4 назад
  ledcWrite(D2b, 0); 
  ledcWrite(D3b, speed);
}

// Движение вправо
void moveLeft(int speed) {
  // Мотор 1 назад
  ledcWrite(D0, 0);
  ledcWrite(D1, speed);
  
  // Мотор 2 вперед
  ledcWrite(D2, speed); 
  ledcWrite(D3, 0);

  // Мотор 3 назад
  ledcWrite(D0b, 0);
  ledcWrite(D1b, speed);
  
  // Мотор 4 впереж
  ledcWrite(D2b, speed); 
  ledcWrite(D3b, 0);
}

// Движение вправо
void turnRight(int speed) {
  // Мотор 1 вперед
  ledcWrite(D0, speed);
  ledcWrite(D1, 0);
  
  // Мотор 2 вперед
  ledcWrite(D2, 0); 
  ledcWrite(D3, speed);

  // Мотор 3 назад
  ledcWrite(D0b, 0);
  ledcWrite(D1b, speed);
  
  // Мотор 4 назад
  ledcWrite(D2b, speed); 
  ledcWrite(D3b, 0);
}

void turnLeft(int speed) {
  // Мотор 1 назад
  ledcWrite(D0, 0);
  ledcWrite(D1, speed);
  
  // Мотор 2 вперед
  ledcWrite(D2, speed); 
  ledcWrite(D3, 0);

  // Мотор 3 вперед
  ledcWrite(D0b, speed);
  ledcWrite(D1b, 0);
  
  // Мотор 4 назад
  ledcWrite(D2b, 0); 
  ledcWrite(D3b, speed);
}

// Остановка моторов
void stopMotors() {
  ledcWrite(D0, 0);
  ledcWrite(D1, 0);
  ledcWrite(D2, 0);
  ledcWrite(D3, 0);
  ledcWrite(D0b, 0);
  ledcWrite(D1b, 0);
  ledcWrite(D2b, 0);
  ledcWrite(D3b, 0);
}