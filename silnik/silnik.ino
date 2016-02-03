#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

YunServer server; //"The use of YunServer is deprecated. Use BridgeServer instead!"
int MINIMUM_DISTANCE_TO_OPSTICLE = 20;
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

boolean useSerial = false;
struct Car {
  boolean direction_l = true;
  int speed_l = 0;
  boolean direction_r = true;
  int speed_r = 0;
} car;

struct distanceSensor {
  int trig;
  int echo;
  int distance = 0;
} front, back;


void setup() {
  //Engine
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);

  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);

  //Distance sensor
  front.trig = 2;
  front.echo = 3;
  back.trig = 12;
  back.echo = 13;
  pinMode(front.trig, OUTPUT);
  pinMode(back.trig, OUTPUT);
  pinMode(front.echo, INPUT);
  pinMode(back.echo, INPUT);

  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();

  //  Serial.begin(9600);
  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for native USB port only
  //  }
  //  Serial.println("Ready to go");
}
void loop() {
  if (useSerial) {
    //    processSerial();
  } else {
    processWeb();
  }
}
void processWeb() {
  YunClient client = server.accept(); //"The use of YunClient is deprecated. Use BridgeClient instead!"
  if (client) {
    //readBytesUntil() should be quicker and better
    car.direction_l = client.readStringUntil(',').toInt();
    car.speed_l = client.readStringUntil(',').toInt();
    car.direction_r = client.readStringUntil(',').toInt();
    car.speed_r = client.readStringUntil(',').toInt();

    updateMotorData();
    client.stop();
  }
  checkDistance();
  delay(50);
}

//void processSerial() {
//  while (Serial.available() > 0) {
//    int input = Serial.parseInt();
//    if (input == 6) {
//      Serial.println("About to change Direction to: " + input);
//      forward = true;
//    } else if (input == 7) {
//      Serial.println("About to change Direction to: " + input);
//      forward = false;
//    } else {
//      Serial.println("About to change speed to: " + input);
//      speed = input;
//    }
//    Serial.println("you typed: " + String(input));
//    Serial.println("Direction: " + String(forward) + " speed: " + String(speed));
//    startMotor(forward, speed);
//    //Ignore what you printed in next loop
//    Serial.parseInt();
//  }
//}

//void startMotor(boolean dir, int speed) {
//  car.
//  updateMotorData(dir, speed, dir, speed);
//}

void updateMotorData() {
  if (car.direction_l) {
    digitalWrite(L1, LOW);
    digitalWrite(L2, HIGH);
  } else {
    digitalWrite(L2, LOW);
    digitalWrite(L1, HIGH);
  }
  if (car.direction_r) {
    digitalWrite(R1, LOW);
    digitalWrite(R2, HIGH);
  } else {
    digitalWrite(R2, LOW);
    digitalWrite(R1, HIGH);
  }
  analogWrite(PWM1, car.speed_l);
  analogWrite(PWM2, car.speed_r);
}

void stopMotor() {
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  analogWrite(5, 0);
}

void checkDistance() {
  //To jest zjebane!!
  front = calculateDistance(front);
  back = calculateDistance(back);

  if (front.distance < MINIMUM_DISTANCE_TO_OPSTICLE ) {
    Serial.println("go to front");
    car.direction_l = false;
    car.direction_r = false;
    updateMotorData();
  }
  if (back.distance < MINIMUM_DISTANCE_TO_OPSTICLE ) {
    Serial.println("go to back");
    car.direction_l = true;
    car.direction_r = true;
    updateMotorData();
  }
}
distanceSensor calculateDistance (distanceSensor sensor)
{
  digitalWrite(sensor.trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor.trig, LOW);
  sensor.distance = pulseIn(sensor.echo, HIGH) / 58;
  return sensor;
}

