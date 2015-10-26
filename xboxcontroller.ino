///button setup
int Start = 11;
int XboxButton = 4;
int Select = 12;
int A = 0;
int B= 1;
int X = 2;
int Y = 3;
int DigitalUp = 5;
int DigitalLeft = 7;
int DigitalRight = 8;
int DigitalDown = 6;
int LeftTrigger = A1 ;
int RightTrigger = A2 ;
int LeftBumper = 9;
int RightBumper = 10;
int ModeButton = A0;
int StatusLed = 13;
int buttonlist[16] = {
  Start, XboxButton, Select, A, B, X, Y, DigitalUp, DigitalLeft, DigitalRight, DigitalDown, LeftTrigger, RightTrigger, LeftBumper, RightBumper, ModeButton};
int ModeNum = 0;

int ledque[2] = {
  0,1};
unsigned long ledtime = 0;

///int RightTriggerValue = LOW;



void setup()
{
  settoinput();
  digitalWrite(StatusLed, HIGH);
}

void settoinput()
{
  pinMode (A, INPUT_PULLUP);
  pinMode (B,INPUT_PULLUP);
  pinMode (X,INPUT_PULLUP);
  pinMode (Y,INPUT);
  pinMode (DigitalUp,INPUT_PULLUP);
  pinMode (DigitalLeft,INPUT_PULLUP);
  pinMode (DigitalRight,INPUT_PULLUP);
  pinMode (DigitalDown,INPUT_PULLUP);
  pinMode (LeftTrigger,INPUT_PULLUP);
  pinMode (RightTrigger,INPUT_PULLUP);
  pinMode (ModeButton, INPUT_PULLUP);
  pinMode (StatusLed,OUTPUT); 
}

unsigned long mainmenutime[2] = {
  0,0};
void loop() 
{
  if(digitalRead(ModeButton) == HIGH && digitalRead(A) == LOW)
  {
    ledque[0] = ledque[0] + 1;
    modeswitch(); 
  }

  if(digitalRead(ModeButton) == HIGH && digitalRead(DigitalUp) == LOW)
  {
    if(millis() - mainmenutime[0] >= 2000)
    {
      mainmenutime[0] = millis();
      ModeNum++;
      ledque[0] = ledque[0] + 1;
    }
  }

  if(digitalRead(ModeButton) == HIGH && digitalRead(DigitalDown) == LOW)
  {
    if(millis() - mainmenutime[1] >= 2000)
    {
      mainmenutime[1] = millis();
      if(ModeNum > 0){
        ModeNum--;
        ledque[0] = ledque[0] + 1;
      }
    }
  }
  event_ledque();
}

void errorhandler()
{
  while(digitalRead(ModeButton != HIGH))
  {
    digitalWrite(StatusLed, LOW);

  } 
}

void event_ledque()
{
  if(ledque[0] > 0){
    if(millis() - ledtime >= 1000){
    switch(ledque[1]){
    case 0:  
        ledtime = millis(); 
        ledque[1] = 1; 
        digitalWrite(StatusLed, HIGH); 
        ledque[0] = ledque[0] - 1;
      break;
    case 1: 
        ledtime = millis(); 
        ledque[1] = 0; 
        digitalWrite(StatusLed, LOW);
      break;
    }
    }
  } 
}

void modeswitch()
{
  switch(ModeNum){
  case 0: 
    halomode(); 
    break;
  case 1: 
    break;
  default: 
    errorhandler; 
    break;
  } 
}

void halomode()
{
  ///used for yup you guessed it holds the time since powered on
  unsigned long time = 0;
  ///delay less led
  //current weapon info
  int weapon = 0; 
  unsigned long weapontime = 0;//when weapon was last fired
  int shotcount = 0;
  //onoff toggles
  unsigned long toggletime[4];
  int aAbility = 0;
  int BEnable = 0; 
  int RBEnable = 0;
  int RTEnable = 0;
  
  unsigned long BTime = 0;
  while(0 == 0)
  {
    ///deal with status messages
    event_ledque();
    //Deal with inputs and switches
    if(digitalRead(B) == LOW)
    {
      if(BEnable == 1)
      {
        BEnable = 2;
        BTime = millis();
      }
      if(digitalRead(ModeButton) == HIGH)
      {
        if(millis() - toggletime[0] >= 2000)
        {
          switch(BEnable){
          case 0: 
            BEnable = 1; 
            break;
          case 1: 
            BEnable = 0; 
            break;
            case 2: BEnable = 1; break;
          default: 
            errorhandler(); 
            break;
          }
          toggletime[0] = millis();
          ledque[0] = ledque[0] + 1;
        }
      }
    }
    if(digitalRead(Y) == LOW)
    {
      switch(weapon){
      case 0: 
        weapon = 1; 
        break;
      case 1: 
        weapon = 0; 
        break;
        ledque[0] = ledque[0] + 1;
      }
      if(digitalRead(ModeButton) == HIGH){
        weapon = 0;
      }
    }
    if(digitalRead(LeftBumper) == LOW)
    {
      if(aAbility == 1){
        time = millis();
      }
      if(digitalRead(ModeButton) == HIGH)
      {
        if(millis() - toggletime[1] >= 2000)
        {
          switch(aAbility){
          case 0: 
            aAbility = 1; 
            break;
          case 1: 
            aAbility = 0; 
            break;
          default: 
            errorhandler(); 
            break;
          }
          toggletime[1] = millis();
          ledque[0] = ledque[0] + 1;
        }
      }
    }

    if(digitalRead(RightBumper) == LOW)
    {
      if(RBEnable == 1){
        pinMode(A,OUTPUT);
        digitalWrite(A, LOW);
        delay(100);
        digitalWrite(A,HIGH);
        pinMode(A,INPUT_PULLUP);
      }
      if(digitalRead(ModeButton) == HIGH)
      {
        if(millis() - toggletime[2] >= 2000)
        {
          switch(RBEnable){
          case 0: 
            RBEnable = 1; 
            break;
          case 1: 
            RBEnable = 0; 
            break;
          default: 
            errorhandler(); 
            break;
          }
          toggletime[2] = millis();
          ledque[0] = ledque[0] + 1;
        }
      }
    }
    if(analogRead(RightTrigger) >= 225)
    {
      if(RTEnable == 1){
        RTEnable = 2;
        weapontime = millis();
      }
      if(digitalRead(ModeButton) == HIGH)
      {
        if(millis() - toggletime[3] >= 2000)
        {
          switch(RTEnable){
          case 0: 
            RTEnable = 1; 
            break;
          case 1: 
            RTEnable = 0; 
            break;
          case 2: 
            RTEnable = 0; 
            break;
          default: 
            errorhandler(); 
            break;
          }
          toggletime[3] = millis();
          ledque[0] = ledque[0] + 1;
        }
      }
    }

    //EVENTS
    if(digitalRead(ModeButton) == HIGH && digitalRead(Select) == LOW){
  time = 0;
  weapon = 0; 
  weapontime = 0;
  shotcount = 0;
  toggletime[0] = 0;
  toggletime[1] = 0;
  toggletime[2] = 0;
  toggletime[3] = 0;
  aAbility = 0;
  BEnable = 0; 
  RBEnable = 0;
  RTEnable = 0;
    break;}
    if(BEnable == 2)
    {
      if(millis() - BTime >= 700)
      {
      pinMode(X,OUTPUT);
        digitalWrite(X, LOW);
        delay(100);
        digitalWrite(X,HIGH);
        pinMode(X,INPUT);
        BEnable = 1;
        ledque[0] = ledque[0] + 1;
      }
    }
    if(RTEnable == 2)
    {
      if(weapon == 0)
      {
      if(analogRead(RightTrigger) < 200){
          pinMode(RightBumper,OUTPUT);
          digitalWrite(RightBumper, LOW);
          delay(100);
          digitalWrite(RightBumper,HIGH);
          pinMode(RightBumper,INPUT_PULLUP);
          RTEnable = 1;
          ledque[0] = ledque[0] + 1;
      }
      }
    }
    if(weapon == 1 && RTEnable >= 1){
        unsigned long RapidFireTime = 0;
        int rapidgo = 0;
        while(digitalRead(RightBumper == LOW)){
          if(millis() - RapidFireTime >= 100 && rapidgo == 0)
          {
            analogWrite(RightTrigger, 0);
            RapidFireTime = millis();
            rapidgo = 1; 
          }
          if(millis() - RapidFireTime >= 100 && rapidgo == 1)
          {
            analogWrite(RightTrigger, 255);
            RapidFireTime = millis();
            rapidgo = 0;
          }if(digitalRead(RightBumper) == HIGH){break;}
        }
          analogWrite(RightTrigger, 0);
          pinMode(RightTrigger, INPUT_PULLUP);
          if(analogRead(RightBumper) == HIGH){
          pinMode(RightBumper,OUTPUT);
          digitalWrite(RightBumper, LOW);
          delay(100);
          digitalWrite(RightBumper,HIGH);
          pinMode(RightBumper,INPUT_PULLUP);
          RTEnable = 1;
          ledque[0] = ledque[0] + 1;
          }
      }
    if(aAbility == 1){
      if(millis() - time >= 15000)
      {
        pinMode(LeftBumper,OUTPUT);
        digitalWrite(LeftBumper, LOW);
        delay(100);
        digitalWrite(LeftBumper,HIGH);
        pinMode(LeftBumper,INPUT_PULLUP);
        time = millis();
        ledque[0] = ledque[0] + 1;
      }
    }
  }
}





