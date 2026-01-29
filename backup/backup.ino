#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// Motors (current pins)
int enA = 16; // D0
int in1 = 5;  // D1
int in2 = 4;  // D2

int enB = 14; // D5
int in3 = 0;  // D3
int in4 = 2;  // D4

// IR receiver
const uint16_t kRecvPin = 13; // D7
IRrecv irrecv(kRecvPin);
decode_results results;

// Remote control codes
const uint32_t forwardCode  = 0xFF18E7;
const uint32_t backwardCode = 0xFF4AB5;
const uint32_t leftCode     = 0xFF10EF;
const uint32_t rightCode    = 0xFF5AA5;

uint32_t lastCode = 0;      // Last command
unsigned long lastTime = 0; // Time of the last signal
const unsigned long timeout = 200; // ms until stop

void setup() {
  Serial.begin(115200);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);

  irrecv.enableIRIn();
}

void driveMotor(uint32_t code) {
  // Forward
  if (code == forwardCode) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  // Backward
  else if (code == backwardCode) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  // Left
  else if (code == leftCode) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  // Right
  else if (code == rightCode) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  // Stop
  else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}

void loop() {
  if (irrecv.decode(&results)) {
    uint32_t value = results.value;

    // If repeat code
    if (value == 0xFFFFFFFF) {
      value = lastCode; // repeat the last command
    } else {
      lastCode = value; // save the new command
    }

    lastTime = millis(); // update the time of the last signal
    driveMotor(value);   // execute the command

    irrecv.resume();
  }

  // Timeout check: if no signal > timeout → stop
  if (millis() - lastTime > timeout) {
    driveMotor(0); // stop
    lastCode = 0;
  }
}
