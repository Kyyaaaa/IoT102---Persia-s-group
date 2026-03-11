// 1. Sub functions
// 1.1 LDR functions
const int LDR_pin = A0;
int LDR_ADC = 0;

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
  LDR_ADC = analogRead(LDR_pin);
  Serial.print("ADC: ");
  Serial.print(LDR_ADC);
  Serial.print(" Lux: ");
  Serial.println(fromADCToLux(LDR_ADC));
  delay(500);
}

// 1.2 LM35 functions
const int LM35_pin = A1;

double fromADCToCelsius(int ADC_value) {
  double voltage = ADC_value * 5.0 / 1023.0;
  double temperature = voltage * 100.0;
  return temperature;
}

void LM35Working() {
  int LM35_ADC = analogRead(LM35_pin);
  Serial.print("ADC: ");
  Serial.print(LM35_ADC);
  Serial.print(" Celsius: ");
  Serial.println(fromADCToCelsius(LM35_ADC));
  delay(500);
}

// 1.3 MQ135 functions
const int MQ135_pin = A2;

void MQ135Working() {
  int MQ135_ADC = analogRead(MQ135_pin);
  Serial.print("MQ135 ADC: ");
  Serial.println(MQ135_ADC);
  delay(500);
}

// 2. Main functions
void setup() {
  SerialMonitorSetup();
}

void loop() {
  // LDRWorking();
  // LM35Working();
  MQ135Working();
}
