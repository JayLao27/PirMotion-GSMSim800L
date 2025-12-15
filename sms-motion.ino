// SMS Alert System with PIR Sensor using SIM800L (INTERRUPT VERSION)

#define TINY_GSM_MODEM_SIM800
#define SerialMon Serial
#define SMS_TARGET "+1234567890"

#include <SoftwareSerial.h>
SoftwareSerial SerialAT(11, 10);

#define TINY_GSM_DEBUG SerialMon
#include <TinyGsmClient.h>

TinyGsm modem(SerialAT);

const int ledPin = 13;
const int PIRPin = 2;   // MUST be interrupt-capable pin (Pin 2 on UNO)

volatile bool motionDetected = false;   // Set by interrupt
bool smsSent = false;                   // Prevent SMS spamming
bool simReady = false;

unsigned long lastBlink = 0;
bool ledState = LOW;

// ===== INTERRUPT FUNCTION =====
void IRAM_ATTR motionISR() {
  motionDetected = true;   // ONLY set flag (NO Serial, NO SMS here)
}

void setup() {
  SerialMon.begin(115200);
  delay(2000);

  SerialAT.begin(9600);
  delay(3000);

  pinMode(ledPin, OUTPUT);
  pinMode(PIRPin, INPUT);

  // Attach interrupt (RISING = motion detected)
  attachInterrupt(digitalPinToInterrupt(PIRPin), motionISR, RISING);

  SerialMon.println("Initializing SIM800L...");
  modem.simUnlock("0000");

  SerialMon.println("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println("Network failed!");
    return;
  }

  SerialMon.println("Network connected!");
  simReady = true;
}

void loop() {
  if (!simReady) return;

  // === MOTION HANDLING ===
  if (motionDetected) {

    // Send SMS ONLY ONCE per detection
    if (!smsSent) {
      SerialMon.println("Motion detected! Sending SMS...");
      modem.sendSMS(SMS_TARGET, "🚨 Motion Detected!");
      SerialMon.println("SMS sent!");
      smsSent = true;
    }

    // LED BLINK while motion is active
    blinkLED();

    // Check if motion stopped
    if (digitalRead(PIRPin) == LOW) {
      motionDetected = false;
      smsSent = false;
      digitalWrite(ledPin, LOW);
    }
  }
}

// ===== LED BLINK FUNCTION =====
void blinkLED() {
  if (millis() - lastBlink >= 300) {
    lastBlink = millis();
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}
