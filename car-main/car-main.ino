#include <AFMotor.h>


//Creating 4 motors:
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR12_1KHZ);
AF_DCMotor motor4(4, MOTOR12_1KHZ);

//IR
//int RECV_PIN = 1; //IR - remote control
//IRrecv irrecv(RECV_PIN);
//decode_results results;

//PINS IN USE:
//- A0 - remote control


//To be improved: - store this in python or different place
//struct Car {
//  AF_DCMotor motor1;
//  int speed1 = 0;
//  boolean direction1 = true;
//  AF_DCMotor motor2;
//  AF_DCMotor motor3;
//  AF_DCMotor motor4;
//  boolean direction_l = true;
//  int speed_l = 0;
//  boolean direction_r = true;
//  int speed_r = 0;
//} car2;

void setup() {
  //Rozwala silniki:
  //  irrecv.enableIRIn(); // Start the receiver

  //Test crap:
  Serial.begin(9600);           // set up Serial library at 9600 bps
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Motor test!");

  motor1.setSpeed(0);     // set the speed to 200/255
  motor1.run(FORWARD);

  motor2.setSpeed(0);     // set the speed to 200/255
  motor2.run(FORWARD);

  motor3.setSpeed(0);     // set the speed to 200/255
  motor3.run(FORWARD);

  motor4.setSpeed(0);     // set the speed to 200/255
  motor4.run(FORWARD);
}

void loop() {
  Serial.println(motor1.getSpeed());
  //  processIRRemote();
  //updateMotorData();
//  motor1.accelerate(50);
//  motor2.accelerate(50);
//  motor3.accelerate(50);
//  motor4.accelerate(50);
  delay(500);
}

//void processIRRemote() {
//
//  if (irrecv.decode(&results)) {
//    Serial.print("Recieved signal: ");
//    Serial.println(results.value);
//
//    if (results.value == 16754775) {//Plus
//      car.speed_l += 50;
//      car.speed_r += 50;
//    } else if (results.value == 16769055) {//Minus
//      car.speed_l -= 50;
//      car.speed_r -= 50;
//    } else if (results.value == 16761405) {//Play/Stop
//      if (car.speed_l > 0 || car.speed_r > 0) {
//        car.speed_l = 0;
//        car.speed_r = 0;
//      } else {
//        car.speed_l = 240;
//        car.speed_r = 240;
//      }
//    } else if (results.value == 16724175) {//1
//      car.speed_l -= 50;
//    } else if (results.value == 16718055) {//2
//      car.speed_l += 50;
//    } else if (results.value == 16716015) {//4
//      car.speed_r -= 50;
//    } else if (results.value == 16726215) {//5
//      car.speed_r += 50;
//    }
//
//    irrecv.resume(); // Receive the next value
//  }
//}
//
//
//void updateMotorData() {
//  motor1.setSpeed(car.speed_l);
//  motor2.setSpeed(car.speed_l);
//  motor3.setSpeed(car.speed_r);
//  motor4.setSpeed(car.speed_r);
//}

