
# Arduino Nano Filament Monitor with Temperature and Humidity Sensing

## Project Overview

This project combines the capabilities of an Arduino Nano with multiple sensors to create a filament monitor that also senses temperature and humidity. It utilizes a DHT22 sensor for measuring temperature and humidity, a VL53L0X sensor for monitoring filament length, and an SSD1306 OLED display for real-time data visualization.

### Key Features:

- **Filament Monitoring**: Measures the length of the filament using a VL53L0X sensor.
- **Temperature and Humidity Sensing**: Utilizes a DHT22 sensor for environmental monitoring.
- **Real-Time Data Display**: Shows the data on an SSD1306 OLED display.

## Circuit Connection Details

The following components are used in this project:

- Arduino Nano
- DHT22 Sensor
- VL53L0X Sensor
- SSD1306 OLED Display

### Wiring Instructions:

1. **DHT22 Sensor**:
   - VCC to 5V on Arduino Nano
   - GND to GND
   - DATA to D7

2. **VL53L0X Sensor**:
   - VCC to 5V
   - GND to GND
   - SDA to A4
   - SCL to A5

3. **SSD1306 OLED Display**:
   - VCC to 5V
   - GND to GND
   - SDA to A4
   - SCL to A5

## Code Explanation

### Filament Calculation:

The filament's remaining percentage is calculated based on the distance measured by the VL53L0X sensor. The calculation inverts the distance, where 10mm corresponds to 100% and 102mm to 0%. This is achieved using the `map` function in Arduino:

```cpp
int calculateFilamentPercentage(int distance) {
  int maxDistance = 10; // 100% filament
  int minDistance = 102; // 0% filament
  return map(constrain(distance, maxDistance, minDistance), maxDistance, minDistance, 100, 0);
}
```

This function maps the distance range (10mm to 102mm) inversely to the percentage range (100% to 0%).

## Creality K1 Printer Compatibility

![Creality K1 Printer](URL_TO_IMAGE)

This filament monitor is designed to be compatible with the Creality K1 printer. The design allows for easy integration and real-time monitoring of filament usage, along with environmental conditions, enhancing the 3D printing experience.

## Installation

To install this project:

1. Assemble the circuit as per the wiring instructions.
2. Upload the provided code to the Arduino Nano.
3. Attach the setup to your Creality K1 printer.

For detailed instructions and troubleshooting, refer to the project wiki.

## Contributions

Contributions to this project are welcome. Please fork the repository and submit a pull request with your proposed changes.

## License

This project is released under the MIT License.

---

Project maintained by [Your GitHub Username]
