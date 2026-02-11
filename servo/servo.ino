#include <ESP32Servo.h>

Servo servo1; // Пин 21

void setup() {
  Serial.begin(115200);

  // Настройка таймера для ESP32
  ESP32PWM::allocateTimer(0);
  
  servo1.setPeriodHertz(50);
  // Используем расширенный диапазон импульсов для максимальной силы
  servo1.attach(21, 500, 2400);

  // Исходное положение ноги (назад)
  servo1.write(0);
  delay(1000);
  Serial.println("Система готова к удару!");
}

void loop() {
  // Ждем 3 секунды для подготовки
  delay(3000);

  // МГНОВЕННЫЙ УДАР
  Serial.println("УДАР!");
  servo1.write(90); // Резкий переход в 90 градусов
  
  delay(500); // Ждем, пока нога долетит и совершит пинок

  // ОЧЕНЬ МЕДЛЕННЫЙ ВОЗВРАТ
  // Возвращаем медленно, чтобы не нагружать питание и механику
  Serial.println("Возврат...");
  for (int pos = 90; pos >= 0; pos--) {
    servo1.write(pos);
    delay(25); // Задержка для плавности
  }
}