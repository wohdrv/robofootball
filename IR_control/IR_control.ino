#include <IRremote.hpp>

const int IR = 15;

void setup() {
  Serial.begin(115200);
  delay(1000);
  IrReceiver.begin(IR, ENABLE_LED_FEEDBACK);
  Serial.println("IR controller enabled");
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long currentTime = millis();

    unsigned long seconds = currentTime / 1000;
    unsigned long minutes = seconds / 60;
    unsigned long hours = minutes / 60;
  
    Serial.println();
    Serial.print(hours % 24);
    Serial.print(":");
    Serial.print(minutes % 60);
    Serial.print(":");
    Serial.print(seconds % 60);
    Serial.println(" Signal recieved");
    Serial.print("Protocol: ");
    Serial.println(IrReceiver.decodedIRData.protocol);
    Serial.print("Command ID: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    IrReceiver.resume();
  }
}