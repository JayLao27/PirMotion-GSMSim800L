# Motion Detection Arduino Project

A simple motion detection system using a PIR sensor to control an LED.

## Hardware Setup

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
- **LED Pin**: Cathode must be connected to pin **13**

## LED States

<table>
  <tr>
    <td align="center">
      <img src="https://i.imgur.com/PmSL6r4.jpg" width="300"><br>
      <b>ON</b>
    </td>
    <td align="center">
      <img src="https://i.imgur.com/FzmRvTy.jpg" width="300"><br>
      <b>OFF</b>
    </td>
  </tr>
</table>

## Getting Started

1. Connect PIR sensor to pin 6
2. Connect LED cathode to pin 13
3. Upload `motion-detection.ino` to your Arduino board
4. Open Serial Monitor (9600 baud) to view motion events
