#include "LiquidCrystal.h"

// LCD Pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(8, 7, 6, 5, 4, 3);

// TMP36 Sensor Pin
int sensorPin = 0;

// Button Pin
int buttonPin = 2;

// Counter Variable
int counter=0;

// Variables to track button state
bool buttonState = false;
bool lastButtonState = false;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Initialize the LCD
  pinMode(buttonPin, INPUT_PULLUP); // Configure button pin with internal pull-up resistor
}

void loop() {
  // Read temperature sensor
  int reading = analogRead(sensorPin);

  // Calculate voltage
  float voltage = reading * 4.68; // Adjust for your measured 5V voltage
  voltage /= 1024.0;

  // Calculate temperature in Celsius
  float temperatureC = (voltage - 0.5) * 100;

  // Display temperature on Serial Monitor
  Serial.print(temperatureC);
  Serial.println(" degrees C");

  // Read button state
  buttonState = !digitalRead(buttonPin); // Inverted logic due to pull-up resistor
  // Detect button press (transition from LOW to HIGH)
  if (buttonState && !lastButtonState) {
    counter=counter+1; // Increment counter
  }
  
  lastButtonState = buttonState;

  // Display temperature on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temperature Value");
  lcd.setCursor(0, 1);
  lcd.print("degrees C ");
  lcd.setCursor(11, 1);
  lcd.print(temperatureC);

  // Display counter on the second row
  lcd.setCursor(0, 1);
  counter=counter+1;
  lcd.print("Counter: ");
  lcd.setCursor(9, 1);
  lcd.print(counter);

  delay(10000); // Debounce delay
}