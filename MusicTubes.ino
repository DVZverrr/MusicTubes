#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>

#define ISSTOPPED  0
#define ISPLAYING  1
#define FIRST_BUTTON_PIN 2
#define BUTTON_COUNT 7

class PlayerStateManager
{
  private:
  byte _currentState = 0;
  byte _previousNonZeroState = 0;
  DFRobotDFPlayerMini* _player;
  byte _hopCounter = 0;
  
  public:
  PlayerStateManager(DFRobotDFPlayerMini *player);
  void Initialize();
  void ReadState();
  void ProcessState();
  void CheckStop();
};

SoftwareSerial softSerial(13,12);
DFRobotDFPlayerMini myDFPlayer;
PlayerStateManager manager(&myDFPlayer);

void setup() {
  manager.Initialize();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  manager.ReadState();
  manager.ProcessState();
  manager.CheckStop();
  delay(100);  
}

PlayerStateManager::PlayerStateManager(DFRobotDFPlayerMini *player)
{
  _player = player;
}

void PlayerStateManager::Initialize()
{
  for(byte button = FIRST_BUTTON_PIN; button < FIRST_BUTTON_PIN + BUTTON_COUNT; button++)
  {
    pinMode(button, INPUT);
  }
  softSerial.begin(9600);
  _player->begin(softSerial);
//  Serial.begin(115200); //For debug
  delay(100);
  _player->volume(20);
}

void PlayerStateManager::ReadState()
{
  int buttonState;
  _currentState = 0;
  for(byte button = FIRST_BUTTON_PIN; button < FIRST_BUTTON_PIN + BUTTON_COUNT; button++)
  {
    buttonState = digitalRead(button);
    byte bitNumber = button - FIRST_BUTTON_PIN;
    byte mask = buttonState << bitNumber;
    _currentState|=mask;  
  }
}

void PlayerStateManager::ProcessState()
{
  if(!_currentState || _currentState == _previousNonZeroState)
    return;  
  int pushedButtonNumber = 0;  
  int i = 0;
  while(i <= BUTTON_COUNT)
  {
    if(_currentState&(1 << i))
      pushedButtonNumber = i;
    i++;
  }
  if(pushedButtonNumber)
    _player->play(pushedButtonNumber);
  else
    _player->stop();  
  
  _previousNonZeroState = _currentState;  
}

void PlayerStateManager::CheckStop()
{
  //проверяем раз в 5 сек, иначе тормозит
  if(_hopCounter < 50)
  {
    _hopCounter++;
    return;
  }
  int state = _player->readState()&0xf;
  if(state == ISSTOPPED && _previousNonZeroState != 1) 
  {
   _previousNonZeroState = 1;
  }
  _hopCounter = 0;
}
