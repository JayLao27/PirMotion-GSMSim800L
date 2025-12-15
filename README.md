# Motion Detection Arduino Project

A simple motion detection system using a PIR sensor to control an LED.

## Hardware Setup to test your PIR sensor to detect motion.
**Testing**: PIR SENSOR.

| Component | Arduino Pin |
|-----------|------------|
| PIR Sensor | 6 |
| LED Cathode | 13 |

## How It Works

The PIR sensor detects motion and triggers the LED:
- **Motion Detected**: LED turns ON → Serial output shows timestamp
- **Motion Ended**: LED turns OFF → Serial output shows timestamp

## PIN Configuration

- **PIR Pin**: Must be connected to pin **6**
- **PIR Pin**:VCC Must be connected to pin **5V**
- **PIR Pin**:GND Must be connected to pin **GND**
- **LED Pin**: Cathode must be connected to pin **13**
- **LED Pin**: Anode must be connected to pin **GND**

## LED States when motion is detected.

<table>
  <tr>
    <td align="center">
      <img src="https://i.imgur.com/PmSL6r4.jpg" width="300"><br>
      <b>Motion Detected!</b>
    </td>
    <td align="center">
      <img src="https://i.imgur.com/FzmRvTy.jpg" width="300"><br>
      <b>Motion Ended!</b>
    </td>
  </tr>
</table>

## Getting Started

1. Connect PIR sensor to pin 6
2. Connect LED cathode to pin 13
3. Upload `motion-detection.ino` to your Arduino board
4. Open Serial Monitor (9600 baud) to view motion events

## SMS Motion Detection (`sms-motion.ino`)

After confirming your PIR sensor works, you can implement the SMS alert system:

### Hardware Setup
- PIR Sensor → Pin 2
- LED → Pin 13
- SIM800L RX → Pin 10
- SIM800L TX → Pin 11

### Implementation Steps

1. **Configure Phone Number**: Update `SMS_TARGET` in the code with your phone number (format: "+1234567890")
2. **Insert SIM Card**: Place an active SIM card into the SIM800L module
3. **Upload Code**: Upload `sms-motion.ino` to your Arduino board
4. **Wait for Network Connection**: 
   - Open Serial Monitor (115200 baud)
   - **You must wait until the SIM800L blinks every 3 seconds** - this indicates it has connected to the network
   - Watch for "Network connected!" message in Serial Monitor
5. **Test Motion Detection**: 
   - Once connected, move in front of the PIR sensor
   - When motion is detected, the system will automatically send an SMS to the number you specified in `SMS_TARGET`
   - You should receive a text message saying "Motion Detected!"
  - Serial Monitor will show "Motion detected!" and "SMS sent!" messages

   <img src="https://imgur.com/Up3RDqe.jpg" width="500" alt="Arduino IDE Serial Monitor displaying motion detection logs with timestamps, showing Motion detected! and SMS sent! messages confirming successful PIR sensor trigger and SMS transmission via SIM800L module">


### Important Notes
- The SIM800L must complete network registration before motion detection will trigger SMS alerts
- The blinking pattern (every 3 seconds) confirms successful network connection
- Make sure your SIM card has active service and SMS capability
