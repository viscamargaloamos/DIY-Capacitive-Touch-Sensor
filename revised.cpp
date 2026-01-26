#define LED 13

const int sendPin = 9;     
const int measurePin = A0; 

void setup() {
  Serial.begin(115200);
  pinMode(sendPin, OUTPUT);
  pinMode(LED, OUTPUT);
}

int tick = 0;

void loop() {
  // PHASE 1: CHARGING 
  digitalWrite(sendPin, HIGH); 
  pinMode(measurePin, INPUT); 

  float maxVoltage = 0;
  for (int i = 0; i < 400; i++) {
    int rawValue = analogRead(measurePin);
    float voltage = (rawValue * 5.0) / 1023.0;

    if (voltage > maxVoltage) {
      maxVoltage = voltage;
    }
    
    // Serial.print("Limit:5.0,"); 
    // Serial.print("Voltage_V:");
    // Serial.println(voltage);
    
    delayMicroseconds(1000); 
  }
  Serial.print("MaxVoltage:");
  Serial.println(maxVoltage);


  tick += 1;
  if ((tick % 2) == 0) {
    digitalWrite(LED, LOW);
  } else {
    digitalWrite(LED, HIGH);
  }

  // PHASE 2: DISCHARGING 
  digitalWrite(sendPin, LOW);
  pinMode(measurePin, OUTPUT);
  digitalWrite(measurePin, LOW);

  for (int i = 0; i < 400; i++) {
    int rawValue = analogRead(measurePin);
    float voltage = (rawValue * 5.0) / 1023.0;
    
    // Serial.print("Limit:5.0,");
    // Serial.print("Voltage_V:");
    // Serial.println(voltage);
    
    delayMicroseconds(2000);
  }
}
