#include <ESP32Servo.h>

Servo servo1; // Пин 12

void setup() {
  Serial.begin(115200);

  servo1.attach(12);

  servo1.write(0);
  Serial.println("Система готова к удару!");
}

void loop()
{  
  delay(2000);
  servo1.write(180);
  delay(1000);
  servo1.write(0);
}