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
```

## 1.2 Đo nhiệt khí - MQ135
- Thuật toán:
    1. Đo giá trị ADC đọc từ MQ135 từ chân A2
    2. Sử dụng ADC làm giá trị đo, giá trị càng cao thì khí càng ô nhiễm

- Code:
```cpp
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
```

## 1.4 Hiển thị dữ liệu - LCD
- Thuật toán: 
    1. Sử dụng giao thức Parallel (cắm trực tiếp 12 chân) và có thêm một biến trở điều chỉnh độ tương phản, cụ thể các chân cắm như sau:
        - VSS - GND
        - VDD - 5V
        - V0 - Chân đọc của biến trở
        - RS - D7
        - RW - GND
        - E - D6
        - D4 - D5
        - D5 - D4
        - D6 - D3
        - D7 - D2
        - A - 5V
        - K - GND (qua điện trở $330 \Omega$)
- Code:
```cpp
// 1.4 LCD functions
void LCDSetup() {
  lcd.begin(16,2);
}

void LCDWorking() {
  lcd.setCursor(0,0);

  lcd.print("L:");
  lcd.print((int)fromADCToLux(LDR_ADC));
  lcd.print("(lx) ");

  lcd.print("T:");
  lcd.print((int)fromADCToCelsius(LM35_ADC));
  lcd.print("(C)");

  lcd.setCursor(0,1);

  lcd.print("Air:");
  lcd.print(MQ135_ADC);
  lcd.print("(ADC)   ");
}
```

# Vấn đề
- LM35 chưa đo đúng nhiệt độ (bị cao hơn nhiệt độ ước tính xung quanh)
- Chưa có sơ đồ mạch nguyên lý