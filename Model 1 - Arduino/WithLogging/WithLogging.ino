int state = 0;
int timerVal = 0;
//bool timerOn = false;
int sensorInputPin = 0;
int resetPin = 9;
int sensorValue = 0;
int reset = 0;
int resetTimer = 0;
int wait = 0;

void setup() {
  pinMode(resetPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorInputPin);
  reset = digitalRead(resetPin);
  if(reset==HIGH) {
    Serial.println("Reset Pressed");
    wait=1;
    state=0;
    resetTimer=0;
  }
  if(wait==0) {
    if(state == 0) {    //Normal--------------------------------------
      if(sensorValue<450) {
        //Latch just closed
        Serial.println("Latch Closed");
        state = 1;
        timerVal = 0;
      }
    }
    else if(state == 1) {    //Intermediate----------------------------
      if(sensorValue>450) {
        //Latch Opened
        Serial.println("Latch Opened");
        state = 0;
      }
      else if(timerVal>19) {
        //>10 seconds
        Serial.println("Switching OFF");
        state = 2;
      }
      timerVal++;
    }
    else if(state == 2) {    //Off------------------------------------
      if(sensorValue>450) {
        //Latch Opened or reset button pressed
        Serial.println("Latch Opened, Switching to Normal");
        state = 0;
      }
    }
  } else {  //If the reset button was pressed.----------------------
    if(resetTimer>5) {//the number should be 720. 5 is for testing purpose
      Serial.println("Reset Over. Resuming system");
      wait=0;
    } else {
      resetTimer++;
      delay(500);
    }
  }
  delay(500);
}

