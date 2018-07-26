#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>

DFRobotDFPlayerMini myDFPlayer;
const int buttonStart = 2;
const int buttonStop = 3;

int buttonStartState = 0;
int buttonStopState = 0;

bool nowPlaying = 0;

void setup() {
  pinMode(buttonStart, INPUT);
  pinMode(buttonStop, INPUT);
  Serial.begin(9600);
  myDFPlayer.begin(Serial);
  delay(1000);
  myDFPlayer.volume(25);
  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  buttonStartState = digitalRead(buttonStart);
  if(buttonStartState == HIGH && !nowPlaying)
  {
    myDFPlayer.play(1);
    nowPlaying = true;
  }
  buttonStopState = digitalRead(buttonStop);  
  if(buttonStopState == HIGH && nowPlaying)
  {
    myDFPlayer.stop();
    nowPlaying = false;
  }
  delay(100);  
}
