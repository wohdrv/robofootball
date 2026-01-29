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
  Serial.println("Вперёд на полной скорости");
  moveForward(255);
  delay(2000);
  
  Serial.println("Стоп");
  stopMotors();
  delay(1000);
  
  Serial.println("Назад на полной скорости");
  moveBackward(255);
  delay(2000);
  
  Serial.println("Стоп");
  stopMotors();
  delay(1000);

  Serial.println("Вправо на полной скорости");
  moveRight(255);
  delay(2000);
  
  Serial.println("Стоп");
  stopMotors();
  delay(1000);

  Serial.println("Влево на полной скорости");
  moveLeft(255);
  delay(2000);

  stopMotors();
  delay(3000);
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