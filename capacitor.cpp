const int sendPin = 9;     
const int measurePin = A0; 

void setup() {
// 115200 baud to ensure seamless, smooth serial plot
  Serial.begin(115200);
  pinMode(sendPin, OUTPUT);
}

void loop() {
  // PHASE 1: CHARGING
  digitalWrite(sendPin, HIGH); 
  pinMode(measurePin, INPUT); 

  // 400 points at 2ms each ~0.8 seconds of charging time
  for (int i = 0; i < 400; i++) {
    int rawValue = analogRead(measurePin);
    float voltage = (rawValue * 5.0) / 1023.0;
    
    Serial.print("Limit:5.0,"); 
    Serial.print("Voltage_V:");
    Serial.println(voltage);
    
    delayMicroseconds(2000); 
  }

  // PHASE 2: DISCHARGING 
  digitalWrite(sendPin, LOW);
  pinMode(measurePin, OUTPUT);
  digitalWrite(measurePin, LOW);

  // 400 points at 2ms each = ~0.8 seconds of discharging time
  for (int i = 0; i < 400; i++) {
    int rawValue = analogRead(measurePin);
    float voltage = (rawValue * 5.0) / 1023.0;
    
    Serial.print("Limit:5.0,");
    Serial.print("Voltage_V:");
    Serial.println(voltage);
    
    delayMicroseconds(2000);
  }
}
