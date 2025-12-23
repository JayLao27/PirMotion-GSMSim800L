// SMS Alert System with PIR Sensor using SIM800L 

#define TINY_GSM_MODEM_SIM800
#define SerialMon Serial
#define SMS_TARGET "+639165715798"

#include <SoftwareSerial.h>
SoftwareSerial SerialAT(11, 10);

#define TINY_GSM_DEBUG SerialMon
#include <TinyGsmClient.h>

TinyGsm modem(SerialAT);

const int ledPin = 13;
const int PIRPin = 2;   

volatile bool motionFlag = false;
bool smsSent = false;
bool simReady = false;

// ===== LED TIMING =====
unsigned long blinkStartTime = 0;
unsigned long lastBlinkTime = 0;

bool ledState = LOW;
bool blinking = false;

const unsigned long BLINK_INTERVAL = 50;    
const unsigned long BLINK_DURATION = 3000;  

void motionISR() {
  motionFlag = true;  
}

void setup() {
  SerialMon.begin(115200);
  delay(2000);

  SerialAT.begin(9600);
  delay(3000);

  pinMode(ledPin, OUTPUT);
  pinMode(PIRPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(PIRPin), motionISR, RISING);

  SerialMon.println("Initializing SIM800L...");
  modem.simUnlock("0000");

  SerialMon.println("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println("Failed to connect to network!");
    return;
  }

  SerialMon.println("Network connected!");
  simReady = true;
}

void loop() {
  if (!simReady) return;

  // ===== MOTION HANDLING =====
  if (motionFlag) {

    // LED ON immediately
    if (!blinking) {
      digitalWrite(ledPin, HIGH);
    }

    // Send SMS once per motion
    if (!smsSent) {
      SerialMon.println("Motion detected!");
      modem.sendSMS(SMS_TARGET, "May nakapasok!");
      SerialMon.println("SMS sent!");

      smsSent = true;
      blinking = true;
      blinkStartTime = millis();
      lastBlinkTime = millis();
    }

    // Fast blinking after SMS
    if (blinking) {
      if (millis() - lastBlinkTime >= BLINK_INTERVAL) {
        lastBlinkTime = millis();
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
      }

      if (millis() - blinkStartTime >= BLINK_DURATION) {
        blinking = false;
        digitalWrite(ledPin, HIGH); // solid ON
      }
    }

    if (digitalRead(PIRPin) == LOW) {
      motionFlag = false;
      smsSent = false;
      blinking = false;
      ledState = LOW;
      digitalWrite(ledPin, LOW);
    }
  }
}