#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// 1. Sub functions
// 1.1 LDR functions
const int LDR_pin = A0;
int LDR_ADC = 0;
unsigned long long LDR_time = 0;
const int LDR_interval = 500;

void SerialMonitorSetup() {
  Serial.begin(9600);
}

double fromADCToLux(int ADC_value) {
  double voltage = ADC_value * 5.0 / 1023.0;
  if(voltage == 0) return 0;
  double LDR_R = 1000.0 * (5.0 / voltage - 1.0);
  double lux = 500 * pow((LDR_R / 1000.0), -1.4);
  return lux;
}

void LDRWorking() {
  unsigned long long current_time = millis();
  if(current_time - LDR_time <= LDR_interval) return;

  LDR_time = current_time;

  LDR_ADC = analogRead(LDR_pin);
  Serial.print("ADC: ");
  Serial.print(LDR_ADC);
  Serial.print(" Lux: ");
  Serial.println(fromADCToLux(LDR_ADC));
}

// 1.2 LM35 functions
const int LM35_pin = A1;
int LM35_ADC = 0;
unsigned long long LM35_time = 0;
const int LM35_interval = 500;

double fromADCToCelsius(int ADC_value) {
  double voltage = ADC_value * 5.0 / 1023.0;
  double temperature = voltage * 100.0;
  return temperature;
}

void LM35Working() {
  unsigned long long current_time = millis();
  if(current_time - LM35_time <= LM35_interval) return;

  LM35_time = current_time;

  LM35_ADC = analogRead(LM35_pin);
  Serial.print("ADC: ");
  Serial.print(LM35_ADC);
  Serial.print(" Celsius: ");
  Serial.println(fromADCToCelsius(LM35_ADC));
}

// 1.3 MQ135 functions
const int MQ135_pin = A2;
int MQ135_ADC = 0;
unsigned long long MQ135_time = 0;
const int MQ135_interval = 500;

void MQ135Working() {
  unsigned long long current_time = millis();
  if(current_time - MQ135_time <= MQ135_interval) return;

  MQ135_time = current_time;

  MQ135_ADC = analogRead(MQ135_pin);
  Serial.print("MQ135 ADC: ");
  Serial.println(MQ135_ADC);
}

// 2. Main functions
void setup() {
  SerialMonitorSetup();
}

void loop() {
  // LDRWorking();
  // LM35Working();
  MQ135Working();

  lcd.setCursor(0, 1);
  lcd.print("Hello");
}
