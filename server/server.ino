#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

YunServer server;

void setup() {
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ready to go");
}

void loop() {
  YunClient client = server.accept();
  if (client) {
    //readBytesUntil() should be quicker and better
    boolean direction_l = client.readStringUntil(',').toInt();
    int speed_l = client.readStringUntil(',').toInt();
    boolean direction_r = client.readStringUntil(',').toInt();
    int speed_r = client.readStringUntil(',').toInt();
    if(direction_l) {
      Serial.print("left forward, ");
      Serial.println(speed_l);
    }
    if(direction_r) {
      Serial.print("right forward, ");
      Serial.println(speed_r);
    }
    client.stop();
  }
  delay(50);
}
