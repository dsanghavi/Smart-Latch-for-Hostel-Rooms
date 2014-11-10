int sensorValue = 0;
int outputValue = 0;
int sensorInputPin = 0;
int outputPin = 12;
void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
}

void loop() {
  sensorValue = analogRead(sensorInputPin);
  outputValue = map(sensorValue, 0, 1023, 0, 255); 
  if(sensorValue<400)
  {
     digitalWrite(outputPin, HIGH);
  }
  else
  {
    digitalWrite(outputPin, LOW);
  }
  Serial.print("sensor = " );                       
  Serial.print(sensorValue);      
  Serial.print("\t output = ");      
  Serial.println(outputValue); 

  delay(50);  
}
