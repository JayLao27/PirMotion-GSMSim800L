#define TINY_GSM_MODEM_SIM800

#define SerialMon Serial             
#define SMS_TARGET "+639165715798"   

#include <SoftwareSerial.h>
SoftwareSerial SerialAT(11, 10);     

#define TINY_GSM_DEBUG SerialMon
#include <TinyGsmClient.h>

TinyGsm modem(SerialAT);

int ledPin = 13;
int PIRPin = 2;
int pirState = LOW;
int val = 0;
bool simReady = false;

void setup() {
 
  SerialMon.begin(115200);
  delay(2000);

 
  SerialAT.begin(9600);
  delay(3000);

  pinMode(ledPin, OUTPUT);
  pinMode(PIRPin, INPUT);

  SerialMon.println("Initializing SIM800L...");

  modem.simUnlock("0000");

  SerialMon.println("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println("Failed to connect to network!");
    return;
  }

  SerialMon.println("Network connected!");
  simReady = true;

  SerialMon.println("SIM800L Ready");
}

void loop() {
  if (!simReady) return;

  val = digitalRead(PIRPin);

  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);

    if (pirState == LOW) {
      SerialMon.println("Motion detected!");
      pirState = HIGH;

      modem.sendSMS(SMS_TARGET, "Motion Detected!");
      SerialMon.println("SMS sent!");
    }

  } else {
    digitalWrite(ledPin, LOW);
    pirState = LOW;
  }

  delay(100);
}
