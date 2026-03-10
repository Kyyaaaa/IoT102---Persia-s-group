# 1. Chức năng cơ bản
## 1.1 Đo ánh sáng - LDR
- Thuật toán:
    1. Đo giá trị ADC đọc từ LDR từ chân A0
    2. Chuyển giá trị ADC đo được qua đơn vị Lux (Ánh sáng trên bề mặt)

- Công thức:
$$
\begin{array}{}
V_{out} = ADC \times \frac{V_{in}}{1023} \\
R_{LDR} = R \times (\frac{V_{in}}{V_{out}} - 1) \\
Lux = 500 \times (\frac{R_{LDR}}{1000})^{-1.4}
\end{array}
$$

- Giải thích các giá trị:
    - $V_{in}$: Điện áp đầu vào, trong project là $5V$
    - $V_{out}$: Điện áp đầu ra sau khi đi qua LDR và điện trở
    - $ADC$: Giá trị ADC đo được tại LDR
    - $R$: Điện trở lắp cho LDR, trong project là $1000 \Omega$
    - $Lux$: Giá trị độ rọi ánh sáng (lux)

- Code:
```cpp
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

```

## 1.2 Đo nhiệt độ - LM35
- Thuật toán:
    1. Đo giá trị ADC đọc từ LM35 từ chân A1
    2. Chuyển giá trị ADC đo được qua đơn vị Celcius (Đơn vị đo nhiệt độ)

- Công thức:
$$
\begin{array}{}
V_{out} = ADC \times \frac{V_{in}}{1023} \\
10mV = 1^{\circ}\text{C} \\
T = V_{out} \times 100
\end{array}
$$

- Giải thích các giá trị:
    - $V_{in}$: Điện áp đầu vào, trong project là $5V$
    - $V_{out}$: Điện áp đầu ra sau khi đi qua LM35
    - $ADC$: Giá trị ADC đo được tại LM35
    - $T$: Nhiệt độ (Celcius)

- Code:
```cpp
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
```