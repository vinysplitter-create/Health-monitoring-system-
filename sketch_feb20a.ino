#include <LiquidCrystal.h>

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Analog inputs
int      // Temperature sensor
int heartPin = A1;    // Potentiometer (Heart rate simulation)

// Digital outputs
int greenLED = 8;
int yellowLED = 9;
int redLED = 10;
int buzzer = 11;

void setup() {
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Health Monitor");
  delay(2000);
  lcd.clear();

  // Set pin modes
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  /* -------- TEMPERATURE (LM35) -------- */
  int tempValue = analogRead(lm35Pin);
  float voltage = tempValue * (5.0 / 1023.0);
  float temperature = voltage * 100.0;   // LM35: 10mV/°C

  /* -------- HEART RATE (SIMULATED) -------- */
  int heartValue = analogRead(heartPin);
  int bpm = map(heartValue, 0, 1023, 60, 140);

  /* -------- DISPLAY -------- */
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print("C ");

  lcd.print("HR:");
  lcd.print(bpm);
  lcd.print("   ");

  // Reset outputs
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  noTone(buzzer);

  lcd.setCursor(0, 1);

  /* -------- HEALTH STATUS LOGIC -------- */
  if (temperature < 37.5 && bpm <= 100) {
    digitalWrite(greenLED, HIGH);
    lcd.print("Status: Normal ");
  }
  else if (temperature < 38.5 || bpm <= 120) {
    digitalWrite(yellowLED, HIGH);
    lcd.print("Status: Warning");
    tone(buzzer, 1000, 300);   // Intermittent beep
  }
  else {
    digitalWrite(redLED, HIGH);
    lcd.print("Status: Critical");
    tone(buzzer, 2000);        // Continuous alarm
  }

  delay(1000); // 1 second update
}