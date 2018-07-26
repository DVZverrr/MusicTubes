#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>

DFRobotDFPlayerMini myDFPlayer;

void setup() {
  Serial.begin(9600);
  myDFPlayer.begin(Serial);
  delay(1000);
  myDFPlayer.volume(25);
  myDFPlayer.play(1);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  delay(30000);
  myDFPlayer.next();
}
