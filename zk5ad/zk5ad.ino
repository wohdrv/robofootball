const int D0 = 23;
const int D1 = 22;
const int D2 = 19;
const int D3 = 18;

bool FW = true;
bool BW = false;

bool debug = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  M2(FW, 100);
  M1(FW, 100);
  delay(1000);
  brake(1);
  //brake(2);
}

void M1(bool direction, int speed) {
  int pwm=map(speed, 0, 100, 0, 255);
  if(direction == FW) {
    analogWrite(D0, pwm);
    analogWrite(D1, LOW);
  }
  else {
    analogWrite(D1, pwm);
    analogWrite(D0, LOW);
  }
  //debugPrint(1, direction, speed, false);
}

void M2(bool direction, int speed) {
  int pwm=map(speed, 0, 100, 0, 255);
  if(direction == FW) {
    analogWrite(D2, pwm);
    analogWrite(D3, LOW);
  }
  else {
    analogWrite(D3, pwm);
    analogWrite(D2, LOW);
  }
  //debugPrint(2, direction, speed, false);
}

void brake(int motor) {
  if(motor == 1) {
    digitalWrite(D0, LOW);
    digitalWrite(D1, LOW); 
  }
  if(motor == 2) {
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
  }
  //debugPrint(motor, true, 0, true);
}

void debugPrint(int motor, bool direction, int speed, bool stop) {
  if(debug) {
    Serial.print("Motor: ");
    Serial.print(motor);

    if(stop && motor>0) {
      Serial.println(" Stopped");
    }
    else {
      if(direction) {
        Serial.println(" FW");
      }
    }
  }
}
