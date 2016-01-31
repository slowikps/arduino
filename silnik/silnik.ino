int PWM1 = 5;
int PWM2 = 9;

int L1 = 6;
int L2 = L1 + 1;

int R1 = 10;
int R2 = R1 + 1;

String BACKWARD1 = String("B");
String BACKWARD2 = String("b");

boolean forward = true;
int speed = 130;
void setup() {
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);

  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ready to go");
}

void loop() {
  while (Serial.available() > 0) {
    int input = Serial.parseInt();
    if (input == 6) {
      Serial.println("About to change Direction to: " + input);
      forward = true;
    } else if (input == 7) {
      Serial.println("About to change Direction to: " + input);
      forward = false;
    } else {
      Serial.println("About to change speed to: " + input);
      speed = input;
    }
    Serial.println("you typed: " + String(input));
    Serial.println("Direction: " + String(forward) + " speed: " + String(speed));
    startMotor(forward, speed);
    //Ignore what you printed in next loop
    Serial.parseInt();
  }
}

void startMotor(boolean dir, int speed) {
  if (dir) {
    digitalWrite(L1, LOW);
    digitalWrite(L2, HIGH);
    digitalWrite(R1, LOW);
    digitalWrite(R2, HIGH);
  } else {
    digitalWrite(L2, LOW);
    digitalWrite(L1, HIGH);
    digitalWrite(R2, LOW);
    digitalWrite(R1, HIGH);
  }
  analogWrite(PWM1, speed);
  analogWrite(PWM2, speed);
}


void stopMotor() {
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  analogWrite(5, 0);
}

