int LDR_pin = A0;
int LDR_ADC = 0;

// 1. Sub functions
// 1.1 LDR functions
void SerialMonitorSetup() {
  Serial.begin(9600);
}

double fromADCToLux(int ADC_value) {
  double voltage = ADC_value * 5.0 / 1023.0;
  double LDR_R = 10000.0 * (5.0 / voltage - 1.0);
  double lux = 500 * pow((LDR_R / 1000.0), -1.4);
  return lux;
}

void LDRWorking() {
  LDR_ADC = analogRead(LDR_pin);

  Serial.print("Lux value: ");
  Serial.println(fromADCToLux(LDR_ADC));

  delay(500);
}

// 2. Main functions
void setup() {
  SerialMonitorSetup();
}

void loop() {
  LDRWorking();
}
