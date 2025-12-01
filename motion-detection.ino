#define SECOND 1000UL
#define MINUTE (60UL * SECOND)

int ledPin = 7;               
int pirPin = 6;                

int lastPirVal = LOW;          
int pirVal;                   

unsigned long myTime;        
char printBuffer[128];         
 
void setup() {
  pinMode(ledPin, OUTPUT);    
  pinMode(pirPin, INPUT);     
 
  Serial.begin(9600);
}
 
void loop() {
  pirVal = digitalRead(pirPin); 

  if (pirVal == HIGH) {   
    digitalWrite(ledPin, HIGH); 

    if (lastPirVal == LOW) { 
      myTime = millis();
      sprintf(printBuffer, "%lu min %lu sec: Motion detected!",
              myTime / MINUTE,
              (myTime % MINUTE) / SECOND);
      Serial.println(printBuffer);
      lastPirVal = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); 

    if (lastPirVal == HIGH) {
      myTime = millis();
      sprintf(printBuffer, "%lu min %lu sec: Motion ended!",
              myTime / MINUTE,
              (myTime % MINUTE) / SECOND);
      Serial.println(printBuffer);
      lastPirVal = LOW;
    }
  }
}
