#include <Wire.h>
#include <VL53L0X.h>
#include <PID_v1.h>
#include "DHT.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// VL53L0X and PID setup
VL53L0X sensor;
double setpoint = 100.0;
double input, output;
double Kp = 1.0, Ki = 0.0, Kd = 0.0;
PID pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

// DHT22 setup
#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// OLED display setup
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Wire.begin();
  sensor.init();
  sensor.setTimeout(500);
  sensor.startContinuous();

  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000); // Pause for 2 seconds

  Serial.begin(9600);
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(0, 100);

  display.clearDisplay();
}

int calculateFilamentPercentage(int distance) {
  int maxDistance = 10; // 100% filament
  int minDistance = 102; // 0% filament
  return map(constrain(distance, maxDistance, minDistance), maxDistance, minDistance, 100, 0);
}

void drawBattery(int percentage) {
  // Draw the battery outline
  display.drawRect(0, 54, 104, 10, SSD1306_WHITE);

  // Fill the battery based on percentage
  int widthFill = map(percentage, 0, 100, 0, 102);
  display.fillRect(1, 55, widthFill, 8, SSD1306_WHITE);
}

void loop() {
  input = sensor.readRangeContinuousMillimeters() - 20;
  pid.Compute();
  int distance = input - 20;
  int delay_time = 100 - (int)output;
  delay_time = constrain(delay_time, 0, 100);
  delay(delay_time);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int filamentPercentage = calculateFilamentPercentage(distance);

  display.clearDisplay();
  display.setTextSize(1); 
  display.setTextColor(SSD1306_WHITE);

  // Display Humidity
  display.setCursor(0, 0);
  if (isnan(humidity)) {
    display.println(F("Humidity Error"));
  } else {
    display.print(F("Humidity: "));
    display.print(humidity);
    display.println(F("%"));
  }

  // Display Temperature
  display.setCursor(0, 10);
  if (isnan(temperature)) {
    display.println(F("Temp Error"));
  } else {
    display.print(F("Real Temp: "));
    display.print(temperature);
    display.println(F("C"));
  }

  // Display Distance
  display.setCursor(0, 20);
  display.print(F("Distance: "));
  display.print(distance);
  display.println(F("mm"));

  // Display Filament Percentage
  display.setCursor(0, 30);
  display.print(F("Filament: "));
  display.print(filamentPercentage);
  display.println(F("%"));

  // Draw Battery for Filament
  drawBattery(filamentPercentage);

  display.display();
}
