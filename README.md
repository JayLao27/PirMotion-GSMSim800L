# Motion Detection Arduino Project

A motion detection system using a PIR sensor with two testing stages:
1. **PIR Sensor Testing** - Verify the PIR sensor works independently
2. **GSM/SMS Integration** - Send text messages when motion is detected

## Hardware Setup

| Component | Arduino Pin |
|-----------|------------|
| PIR Sensor | 2 |
| LED | 13 |
| SIM800L TX | 10 (RX via SoftwareSerial) |
| SIM800L RX | 11 (TX via SoftwareSerial) |

## Testing Stages

### Stage 1: Test Your PIR Sensor (`pir-sensor-test.ino`)

**Test your PIR SENSOR pins if it detects motion.**

**Purpose**: Verify the PIR sensor is working correctly before testing the GSM module.

**Steps**:
1. Connect PIR sensor to pin 2
2. Connect LED to pin 13
3. Upload `pir-sensor-test.ino` to your Arduino board
4. Open Serial Monitor (9600 baud)
5. Move in front of the PIR sensor to trigger motion detection
6. Verify the LED lights up and "Motion detected!" appears in Serial Monitor

### Stage 2: Test SMS with PIR Sensor (`sms.ino`)

**Purpose**: Once PIR is confirmed working, test the GSM module to send SMS text messages when motion is detected.

**Steps**:
1. Ensure your PIR sensor is working (complete Stage 1 first)
2. Connect the SIM800L GSM module to pins 10 & 11
3. Update `SMS_TARGET` with your phone number (format: "+1234567890")
4. Insert an active SIM card into the SIM800L module
5. Upload `sms.ino` to your Arduino board
6. Open Serial Monitor (115200 baud)
7. Wait for "Network connected!" message
8. Move in front of the PIR sensor
9. You should receive an SMS text message saying "Motion Detected!" on your phone

## PIN Configuration

- **PIR Pin**: Pin 2 (INPUT)
- **LED Pin**: Pin 13 (OUTPUT)
- **SIM800L RX**: Pin 10 (SoftwareSerial TX)
- **SIM800L TX**: Pin 11 (SoftwareSerial RX)

## LED States

<table>
  <tr>
    <td align="center">
      <img src="https://i.imgur.com/PmSL6r4.jpg" width="300"><br>
      <b>Motion: ON</b>
    </td>
    <td align="center">
      <img src="https://i.imgur.com/FzmRvTy.jpg" width="300"><br>
      <b>No Motion: OFF</b>
    </td>
  </tr>
</table>

## Getting Started

1. **Always start with `motion-detection.ino`** to verify PIR sensor functionality
2. Once PIR sensor is confirmed working, upload `sms.ino`
3. Provide pictures of your setup in the future for better troubleshooting
